#pragma once

#include <zmq.hpp>
#include "Message.h"

namespace CH
{

bool Serialize(const AoiMsg &msg, zmq::message_t &zmq_msg);
bool Deserialize(AoiMsg &msg, const zmq::message_t &zmq_msg);

} // namespace CH