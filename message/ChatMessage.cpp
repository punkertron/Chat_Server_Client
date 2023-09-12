#include "ChatMessage.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

bool ChatMessage::decodeHeader()
{
    char header[headerLength + 1] = {};
    std::strncat(header, data_, headerLength);
    bodyLength_ = std::atoi(header);
    if (bodyLength_ > maxBodyLength)
    {
        bodyLength_ = 0;
        return false;
    }
    return true;
}

void ChatMessage::encodeHeader()
{
    char header[headerLength + 1] = {};
    std::sprintf(header, "%4d", static_cast<int>(bodyLength_));
    std::memcpy(data_, header, headerLength);
}
