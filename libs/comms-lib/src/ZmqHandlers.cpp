#include "ZmqHandlers.hpp"
#include <bitsery/adapter/buffer.h>
#include <string>

namespace ZH
{
bool Serialize(const MSG &msg, zmq::message_t &zmq_msg)
{
    std::string buffer;
    auto rSize = bitsery::quickSerialization<OutputAdapter>(buffer, msg);
    zmq_msg = zmq::message_t(buffer);

    return rSize == zmq_msg.size();
}

bool Deserialize(MSG &msg, const zmq::message_t &zmq_msg)
{
    std::string buffer(static_cast<const char*>(zmq_msg.data()), zmq_msg.size());
    auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, msg);
    
    return state.first == bitsery::ReaderError::NoError && state.second;
}


} // namespace ZH