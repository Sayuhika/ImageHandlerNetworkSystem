#pragma once

#include <zmq.hpp>
#include "Message.h"

namespace CH
{

bool Serialize(const MSG &msg, zmq::message_t &zmq_msg);
bool Deserialize(MSG &msg, const zmq::message_t &zmq_msg);

} // namespace CH