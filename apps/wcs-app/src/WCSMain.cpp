#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>

extern const int &FRAME_WIDTH;
extern const int &FRAME_HEIGHT;

bool core(cv::VideoCapture &inputVideo, CH::AoiMsg &message_img, int a)
{   
    cv::Mat mat;
    inputVideo >> mat;
    if (mat.empty())
    { 
        return false;
    }

    // Перевод из Mat в формат rgb для записи в структуру Image
    CH::Image img_orig = CH::MatToImage(mat);

    // adding original image
    message_img.aoi.push_back(img_orig);

    // adding time
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S.000", ptm);

    // message_img.time = std::string(buffer);
    message_img.time = std::to_string(a);

    std::cout << message_img.time << std::endl;

    return true;
}

int main(int argc, char* argv[]) 
{   
    /// ========== /// ========== /// Connection /// ========== /// ========== ///

    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <address> like <ip:port>" << std::endl;
        return 1;
    }
    std::string addr = argv[1];

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://" + addr);

    /// ========== /// ========== /// Camera prework processes /// ========== /// ========== ///

    // Открытие потока с камеры
    // VideoCapture cap("http://guest:guest@192.168.9.37/video1.mjpg");  // Так в 528 надо сделать
    cv::VideoCapture inputVideo(0);

    if (!inputVideo.isOpened())
    {
        std::cout << "Could not open the input video: " << std::endl;
        return -1;
    }                
    const std::string NAME = "Test.mp4";   

    const int &FRAME_WIDTH  = (int)inputVideo.get(cv::CAP_PROP_FRAME_WIDTH);   //src.cols
    const int &FRAME_HEIGHT = (int)inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT);	//src.rows

    /// ========== /// ========== /// Main core /// ========== /// ========== ///

    int a = 0;

    while (true) 
    {
        CH::AoiMsg message_img;
        zmq::message_t message_zmq;
        // std::this_thread::sleep_for(std::chrono::milliseconds(300));

        if (core(inputVideo, message_img, a))
        {
            if (CH::Serialize(message_img, message_zmq))
            {
                socket.send(message_zmq);
                a++;
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

    return 0;
}
