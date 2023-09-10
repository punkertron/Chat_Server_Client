#include "ChatRoom.hpp"

void ChatRoom::join(ChatPaticipantPtr participant)
{
    participants_.insert(participant);
    for (const auto& msg : recent_msgs_)
        participant->deliver(msg);
}

void ChatRoom::deliver(const ChatMessage& msg)
{
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > maxRecentMsgs)
        recent_msgs_.pop_front();

    for (const auto& participant : participants_)
        participant->deliver(msg);
}

void ChatRoom::leave(ChatPaticipantPtr participant)
{
    participants_.erase(participant);
}
