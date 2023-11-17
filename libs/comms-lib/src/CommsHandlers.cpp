#include "CommsHandlers.hpp"
#include <bitsery/adapter/buffer.h>
#include <string>

namespace CH
{
bool Serialize(const AoiMsg &msg, zmq::message_t &zmq_msg)
{
    std::string buffer;
    auto rSize = bitsery::quickSerialization<OutputAdapter>(buffer, msg);
    zmq_msg = zmq::message_t(buffer);

    return rSize == zmq_msg.size();
}

bool Deserialize(AoiMsg &msg, const zmq::message_t &zmq_msg)
{
    std::string buffer(static_cast<const char*>(zmq_msg.data()), zmq_msg.size());
    auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, msg);
    
    return state.first == bitsery::ReaderError::NoError && state.second;
}

Image MatToImage(const cv::Mat &mat)
{
    std::vector<uint8_t> color_channel_r, color_channel_g, color_channel_b;

    for (int i = 0; i < mat.cols; i++)
    {
        for (int j = 0; j < mat.rows; j++)
        {
            color_channel_r.push_back(mat.at<cv::Vec3b>(j, i)[0]);
            color_channel_g.push_back(mat.at<cv::Vec3b>(j, i)[1]);
            color_channel_b.push_back(mat.at<cv::Vec3b>(j, i)[2]);
        }
    }

    // Запись в структуру Image
    CH::Image img{ 
        static_cast<uint32_t>(mat.cols), 
        static_cast<uint32_t>(mat.rows), 
        color_channel_r, 
        color_channel_g, 
        color_channel_b };

    return img;
}

cv::Mat ImageToMat(const Image &img)
{
    cv::Mat mat(cv::Size(img.width, img.height), CV_8UC3);

    int c = 0;
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            mat.at<cv::Vec3b>(j, i)[0] = img.color_channel_r.at(c);
            mat.at<cv::Vec3b>(j, i)[1] = img.color_channel_g.at(c);
            mat.at<cv::Vec3b>(j, i)[2] = img.color_channel_b.at(c);
            c++;
        }
    }

    return mat;
}

} // namespace CH