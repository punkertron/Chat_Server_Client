#ifndef CHAT_PARTICIPANT_HPP
#define CHAT_PARTICIPANT_HPP

#include <memory>

#include "ChatMessage.hpp"

class ChatParticipant
{
   public:
    virtual ~ChatParticipant(){};
    virtual void deliver(const ChatMessage& msg) = 0;
};

using ChatPaticipantPtr = std::shared_ptr<ChatParticipant>;

#endif  // CHAT_PARTICIPANT_HPP