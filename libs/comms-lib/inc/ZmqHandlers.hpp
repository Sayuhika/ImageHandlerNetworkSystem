#include <zmq.hpp>
#include "message.pb.h"

namespace ZH
{

bool serialize_proto_msg(const google::protobuf::Message &msg, zmq::message_t& zmq_msg);
bool deserialize_proto_msg(google::protobuf::Message &msg, const zmq::message_t& zmq_msg);

} // namespace ZH