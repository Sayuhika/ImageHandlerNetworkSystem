#include <vector>
#include <string>
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
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://" + addr);

    while (true) 
    {
        MSG message_img;
        zmq::message_t message_zmq;
        
        /// TO DO BEGIN

        // Getting 1 image
        // parsing to 3 uint RGB channels from mat
        // filling msg

        /// TO DO END

        if (CH::Serialize(message_img, message_zmq))
        {
            socket.send(message_zmq);
        }
        else
        {
            std::cerr << "Serialize failed" << std::endl;
        }
       
    }

    return 0;
}
