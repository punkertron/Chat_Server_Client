#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <deque>

#include "ChatMessage.hpp"

class Client
{
   private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::resolver::results_type endpoints_;
    boost::asio::ip::tcp::socket socket_;

    ChatMessage read_msg_;
    std::deque<ChatMessage> write_msgs_;

    void connect();
    void read_header();
    void read_body();
    void read_from_user();
    void write(const ChatMessage& msg);
    void do_write();

   public:
    explicit Client(const char* host, const char* port);
    void run();
};

#endif  // CLIENT_HPP