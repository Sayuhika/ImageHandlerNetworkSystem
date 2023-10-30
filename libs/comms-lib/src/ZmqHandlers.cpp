#include "ZmqHandlers.hpp"
#include <string>

namespace ZH
{

bool serialize_proto_msg(const google::protobuf::Message &msg, zmq::message_t& zmq_msg) 
{
    std::string serialized;
    if (!msg.SerializeToString(&serialized)) 
    {
        return false;
    }
    zmq_msg.rebuild(serialized.size());
    memcpy(zmq_msg.data(), serialized.data(), serialized.size());
    
    return true;
}

bool deserialize_proto_msg(google::protobuf::Message &msg, const zmq::message_t& zmq_msg) 
{
    return msg.ParseFromArray(zmq_msg.data(), zmq_msg.size());
}

} // namespace ZH