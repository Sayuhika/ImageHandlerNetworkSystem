#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

    for (int i = 0;;i++)
    {
        zmq::message_t zmq_msg;
        CH::AoiMsg message_img;
        socket.recv(zmq_msg, zmq::recv_flags::none);

        if (CH::Deserialize(message_img, zmq_msg))
        {
            messages.push_back(message_img);

            // TO DO BEGIN
            if (i > 60)
            {
                std::sort(messages.begin(), messages.end(), compareByTime);
                std::string time = messages[0].time;
                orig = CH::ImageToMat(messages[0].aoi[0]); // получение оригинала
                proc = CH::ImageToMat(messages[0].aoi[1]); // получение обработанной картинки
                messages.erase(messages.cbegin(), messages.cbegin() + 1);
                
                // Отображение картинки
                cv::imshow(time, proc);
                char c = cv::waitKey(33); // 33 мск оптимально для 30 кдаров в секунду
                if (c == 's') // остановка цикла
                    break;
            }
            /// TO DO END
        }
        else
        {
            std::cerr << "Deserialize failed" << std::endl;
        }

    }

    return 0;
}