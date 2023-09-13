#include "ChatSession.hpp"

ChatSession::ChatSession(boost::asio::ip::tcp::socket socket, ChatRoom& room) : socket_(std::move(socket)), room_(room)
{
}

void ChatSession::start()
{
    room_.join(shared_from_this());
    readHeader();
}

void ChatSession::deliver(const ChatMessage& msg)
{
    bool writeInProgress = !writeMsgs_.empty();
    writeMsgs_.push_back(msg);
    if (!writeInProgress)
    {
        write();
    }
}

void ChatSession::readHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(readMsg_.getData(), ChatMessage::headerLength),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/)
                            {
                                if (!ec && readMsg_.decodeHeader())
                                {
                                    readBody();
                                }
                                else
                                {
                                    room_.leave(shared_from_this());
                                }
                            });
}

void ChatSession::readBody()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(readMsg_.getBody(), readMsg_.getBodyLength()),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/)
                            {
                                if (!ec)
                                {
                                    room_.deliver(readMsg_, self);
                                    readHeader();
                                }
                                else
                                {
                                    room_.leave(shared_from_this());
                                }
                            });
}

void ChatSession::write()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(writeMsgs_.front().getData(), writeMsgs_.front().getLength()),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/)
                             {
                                 if (!ec)
                                 {
                                     writeMsgs_.pop_front();
                                     if (!writeMsgs_.empty())
                                     {
                                         write();
                                     }
                                 }
                                 else
                                 {
                                     room_.leave(shared_from_this());
                                 }
                             });
}