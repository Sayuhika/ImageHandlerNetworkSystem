#include <zmq.hpp>
#include <vector>
#include <string>

int main() 
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://*:5555");

    while (true) 
    {
        std::string Image;
        zmq::message_t message(sizeof(Image));
        memcpy(message.data(), &image, sizeof(Image));
        socket.send(message);
    }

    return 0;
}
