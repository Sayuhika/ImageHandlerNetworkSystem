#include <iostream>
#include <vector>
#include <iostream>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>

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

    std::vector<MSG> messages;

    while (true) 
    {
        zmq::message_t zmq_msg;
        MSG message_img;
        socket.recv(zmq_msg, zmq::recv_flags::none);

        if (CH::Deserialize(message_img, zmq_msg))
        {
            messages.push_back(message_img);

            /// TO DO BEGIN

            // parsing to mat from 3 uint RGB channels
            // to do somthing with msg

            /// TO DO END
        }
        else
        {
            std::cerr << "Deserialize failed" << std::endl;
        }

    }

    return 0;
}