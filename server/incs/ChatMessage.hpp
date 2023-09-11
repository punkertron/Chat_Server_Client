#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstddef>

class ChatMessage
{
   public:
    static constexpr std::size_t headerLength  = 4;
    static constexpr std::size_t maxBodyLength = 1024;

   private:  // TODO: public?
    char data_[headerLength + maxBodyLength];
    std::size_t bodyLength_ = 0;

   public:
    ChatMessage()  = default;
    ~ChatMessage() = default;

    const char* getData() const
    {
        return data_;
    }

    char* getData()
    {
        return data_;
    }

    std::size_t getLength() const
    {
        return headerLength + bodyLength_;
    }

    const char* getBody() const
    {
        return data_ + headerLength;
    }

    char* getBody()
    {
        return data_ + headerLength;
    }

    std::size_t getBodyLength() const
    {
        return bodyLength_;
    }

    bool decodeHeader();
    void encodeHeader();
};

#endif  // CHAT_MESSAGE_HPP