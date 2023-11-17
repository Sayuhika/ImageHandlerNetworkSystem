#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <zmq.hpp>
#include <Message.h>
#include <CommsHandlers.hpp>

extern const int &FRAME_WIDTH;
extern const int &FRAME_HEIGHT;

bool core(cv::VideoCapture &inputVideo, CH::AoiMsg &message_img)
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
    message_img.time = std::time(nullptr);

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

    while (true) 
    {
        CH::AoiMsg message_img;
        zmq::message_t message_zmq;

        if (core(inputVideo, message_img))
        {
            if (CH::Serialize(message_img, message_zmq))
            {
                socket.send(message_zmq);
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
