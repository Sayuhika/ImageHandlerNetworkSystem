#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>
#include "imageFiltration.h"

bool core(const CH::Image &img_in, CH::Image &img_out)
{	
	try
	{
		imageFilter(
			img_out.color_channel_r, 
			img_out.color_channel_g, 
			img_out.color_channel_b, 
			img_in.color_channel_r, 
			img_in.color_channel_g, 
			img_in.color_channel_b, 
			img_in.height, 
			img_in.width);
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;

		return false;
	}

	img_out.width  = img_in.width;
	img_out.height = img_in.height;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return true;
}

int main(int argc, char* argv[]) 
{
    /// ========== /// ========== /// Connection /// ========== /// ========== ///

    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <server1_ip> <server2_ip> like <ip1:port1> <ip2:port2>" << std::endl;
        return 1;
    }
    std::string server1Ip = argv[1];
    std::string server2Ip = argv[2];

    zmq::context_t context(1);
    zmq::socket_t wc_server(context, ZMQ_PULL);
	zmq::socket_t ic_server(context, ZMQ_PUSH);
    
    wc_server.setsockopt(ZMQ_CONFLATE, 1);
    ic_server.setsockopt(ZMQ_CONFLATE, 1);

	wc_server.connect("tcp://" + server1Ip); // to Web Cam Server
	ic_server.connect("tcp://" + server2Ip); // to Image Collector Server

    /// ========== /// ========== /// Main core /// ========== /// ========== ///

    while (true) 
    {
        zmq::message_t zmq_msg;
        CH::AoiMsg message_img;

        wc_server.recv(zmq_msg, zmq::recv_flags::none); // from Web Cam Server
        
        if (CH::Deserialize(message_img, zmq_msg))
        {
            std::cout << message_img.time << std::endl;
			CH::Image img_orig = message_img.aoi[0]; // original
			CH::Image img_prsd; // processed (in future)

            if (core(img_orig, img_prsd))
            {
				message_img.aoi.push_back(img_prsd);

                if (CH::Serialize(message_img, zmq_msg))
                {
                    ic_server.send(zmq_msg, zmq::send_flags::none); // to Image Collector Server
                }
                else
                {
                    std::cerr << "Serialize failed" << std::endl;
                }
            }
            else
            {
                std::cerr << "Core failed" << std::endl;
            }
        }
        else
        {
            std::cerr << "Deserialize failed" << std::endl;
        }
    }

    return 0;
}