#include <zmq.hpp>
#include <vector>
#include <string>
#include <Message.h>
#include <ZmqHandlers.hpp>
#include <iostream>

int main() 
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://*:5555");

    while (true) 
    {
        MSG message_img;
        zmq::message_t message_zmq;
        
        if (ZH::Serialize(message_img, message_zmq))
        {
            socket.send(message_zmq);
        }
        else
        {
            std::cout << "[ERROR]" << std::endl;
        }
        
    }

    return 0;
}
