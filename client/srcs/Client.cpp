#include "Client.hpp"

#include <iostream>
#include <thread>

Client::Client(const char* host, const char* port) :
    io_context_(), endpoints_(boost::asio::ip::tcp::resolver(io_context_).resolve(host, port)), socket_(io_context_)
{
    connect();
}

void Client::run()
{
    std::thread t(
        [this]()
        {
            io_context_.run();
        });

    read_from_user();
    t.join();
    // t.detach();
}

void Client::read_from_user()
{
    char line[ChatMessage::maxBodyLength + 1];
    while (std::cin.getline(line, ChatMessage::maxBodyLength + 1))
    {
        ChatMessage msg;
        msg.setBodyLength(std::strlen(line));
        std::memcpy(msg.getBody(), line, msg.getBodyLength());
        msg.encodeHeader();
        write(msg);
    }
}

void Client::write(const ChatMessage& msg)
{
    boost::asio::post(io_context_,
                      [this, msg]()
                      {
                          bool write_in_progress = !write_msgs_.empty();
                          write_msgs_.push_back(msg);
                          if (!write_in_progress)
                          {
                              do_write();
                          }
                      });
}

void Client::do_write()
{
    boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().getData(), write_msgs_.front().getLength()),
                             [this](boost::system::error_code ec, std::size_t /*length*/)
                             {
                                 if (!ec)
                                 {
                                     write_msgs_.pop_front();
                                     if (!write_msgs_.empty())
                                     {
                                         do_write();
                                     }
                                 }
                                 else
                                 {
                                     socket_.close();
                                 }
                             });
}

void Client::connect()
{
    boost::asio::async_connect(socket_, endpoints_,
                               [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint)
                               {
                                   if (!ec)
                                   {
                                       read_header();
                                   }
                               });
}

void Client::read_header()
{
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.getData(), ChatMessage::headerLength),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
                            {
                                if (!ec && read_msg_.decodeHeader())
                                {
                                    read_body();
                                }
                                else
                                {
                                    socket_.close();
                                }
                            });
}

void Client::read_body()
{
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.getBody(), read_msg_.getBodyLength()),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
                            {
                                if (!ec)
                                {
                                    std::cout.write(read_msg_.getBody(), read_msg_.getBodyLength());
                                    std::cout << '\n';
                                    read_header();
                                }
                                else
                                {
                                    socket_.close();
                                }
                            });
}
