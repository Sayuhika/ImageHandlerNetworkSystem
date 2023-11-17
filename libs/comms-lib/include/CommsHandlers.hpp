#pragma once

#include <zmq.hpp>
#include <opencv2/opencv.hpp>
#include "Message.h"

namespace CH
{

bool Serialize(const AoiMsg &msg, zmq::message_t &zmq_msg);
bool Deserialize(AoiMsg &msg, const zmq::message_t &zmq_msg);

Image MatToImage(const cv::Mat &mat);
cv::Mat ImageToMat(const Image &img);

} // namespace CH