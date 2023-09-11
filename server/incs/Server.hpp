#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>

#include "ChatRoom.hpp"

class Server
{
   private:
    boost::asio::io_context io_context_;
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;

    ChatRoom room_;

    void awaitStop();
    void accept();

   public:
    explicit Server(const char* port);
    void run();
};

#endif  // SERVER_HPP