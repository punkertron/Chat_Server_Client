#ifndef CHAT_ROOM_HPP
#define CHAT_ROOM_HPP

#include <deque>
#include <memory>
#include <set>

#include "ChatMessage.hpp"
#include "ChatParticipant.hpp"

class ChatRoom
{
   private:
    std::set<ChatPaticipantPtr> participants_;
    enum
    {
        maxRecentMsgs = 100
    };
    std::deque<ChatMessage> recent_msgs_;

   public:
    void join(ChatPaticipantPtr participant);
    void leave(ChatPaticipantPtr participant);
    void deliver(const ChatMessage& participant);
};

#endif  // CHAT_ROOM_HPP