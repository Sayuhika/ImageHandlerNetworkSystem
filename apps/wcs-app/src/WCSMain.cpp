#include <zmq.hpp>
#include <vector>
#include <string>
#include <Message.h>
#include <ZmqHandlers>

int main() 
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://*:5555");

    while (true) 
    {
        MSG message_img;
        zmq::message_t message;
        
        if (ZH::Serialize(message_img, message))
        {
            socket.send(message);
        }
        else
        {
            std::cout << "[ERROR]" << std::endl;
        }
        
    }

    return 0;
}
