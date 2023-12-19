#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>

bool compareByTime(const CH::AoiMsg& a, const CH::AoiMsg& b)
{
    return std::stoi(a.time) < std::stoi(b.time);
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <address> like <ip:port>" << std::endl;
        return 1;
    }
    std::string addr = argv[1];

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.bind("tcp://" + addr);

    std::vector<CH::AoiMsg> messages;
    cv::Mat orig, proc;

    int last_frame_index = 0;

    while(true)
    {
        zmq::message_t zmq_msg;
        CH::AoiMsg message_img;
        socket.recv(zmq_msg, zmq::recv_flags::none);

        if (CH::Deserialize(message_img, zmq_msg))
        {
            int index = std::stoi(message_img.time);
            if (index < last_frame_index) 
            {
                continue;
            }
            last_frame_index = index;

            std::cout << message_img.time << std::endl;
            orig = CH::ImageToMat(message_img.aoi[1]);
            cv::imshow("Result", orig);
            if (cv::waitKey(1) == 27) 
            {
                break;
            } 
        }
        else
        {
            std::cerr << "Deserialize failed" << std::endl;
        }

    }

    return 0;
}