#include <zmq.hpp>
#include "Message.h"

namespace ZH
{

bool Serialize(const MSG &msg, zmq::message_t &zmq_msg);
bool Deserialize(MSG &msg, const zmq::message_t &zmq_msg);

} // namespace ZH