#include <string>
#include <iostream>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <server1_ip> <server2_ip> like <ip1:port1> <ip2:port2>" << std::endl;
        return 1;
    }
    std::string server1Ip = argv[1];
    std::string server2Ip = argv[2];

    zmq::context_t context(1);

    zmq::socket_t wc_server(context, ZMQ_PULL);
    wc_server.connect("tcp://" + server1Ip);

    zmq::socket_t ic_server(context, ZMQ_PUSH);
    ic_server.bind("tcp://" + server2Ip);

    while (true) 
    {
        zmq::message_t zmq_msg;
        MSG message_img;
        wc_server.recv(zmq_msg, zmq::recv_flags::none);
        
        if (CH::Deserialize(message_img, zmq_msg))
        {
            /// TO DO BEGIN

            // parsing to mat from 3 uint RGB channels
            // image handling
            // parsing to 3 uint RGB channels from mat
            // filling msg

            /// TO DO END
        }
        else
        {
            std::cerr << "Deserialize failed" << std::endl;
        }

        if (CH::Serialize(message_img, zmq_msg))
        {
            ic_server.send(zmq_msg, zmq::send_flags::none);
        }
        else
        {
            std::cerr << "Serialize failed" << std::endl;
        }
    }

    return 0;
}