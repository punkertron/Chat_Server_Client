#ifndef CHAT_SESSION_HPP
#define CHAT_SESSION_HPP

#include <boost/asio.hpp>
#include <deque>
#include <memory>

#include "ChatMessage.hpp"
#include "ChatParticipant.hpp"
#include "ChatRoom.hpp"

class ChatSession : public ChatParticipant, public std::enable_shared_from_this<ChatSession>
{
   private:
    boost::asio::ip::tcp::socket socket_;
    ChatRoom room_;
    ChatMessage readMsg_;
    std::deque<ChatMessage> writeMsgs_;

    void readHeader();
    void readBody();
    void write();

   public:
    ChatSession(boost::asio::ip::tcp::socket socket, ChatRoom& room);
    ~ChatSession() = default;

    void start();
    void deliver(const ChatMessage& msg);
};

#endif  // CHAT_SESSION_HPP