/*
 * TLVMessage.h
 *
 *  Created on: Oct 15, 2021
 *      Author: ubuntu
 */

#ifndef SERVER_NODES_CLOUD_TRANSPORT_TCP_TLVMESSAGE_H_
#define SERVER_NODES_CLOUD_TRANSPORT_TCP_TLVMESSAGE_H_

#include <memory>
#include <string>
#include <string.h>
#include <netinet/in.h>
#include "Data.h"

namespace trs
{

class TLVMessage : public std::enable_shared_from_this<TLVMessage>
{

public:
    using byte = std::uint8_t;
    using bytes = byte*;
    struct Header
    {
        std::uint32_t topicId;
        std::uint16_t bodyLength;

        inline bool decode()
        {
            memcpy((std::uint8_t*)&topicId, buf, SIZE_OF_HEADER_TOPIC_ID);
            memcpy((std::uint8_t*)&bodyLength,
                    buf + TLVMessage::SIZE_OF_HEADER_TOPIC_ID, SIZE_OF_HEADER_BODY_LENGTH);

            topicId = ntohl(topicId);
            bodyLength = ntohs(bodyLength);

            return bodyLength > 0;
        }

        inline bool encode()
        {
            topicId = htonl(topicId);
            bodyLength = htons(bodyLength);

            memcpy(buf, (std::uint8_t*)&topicId, SIZE_OF_HEADER_TOPIC_ID);
            memcpy(buf + TLVMessage::SIZE_OF_HEADER_TOPIC_ID,
                    (std::uint8_t*)&bodyLength, SIZE_OF_HEADER_BODY_LENGTH);

            if (bodyLength <= 0)
            {
                return false;
            }
            return true;
        }

        inline std::uint8_t* raw()
        {
            return buf;
        }

    private:
        std::uint8_t buf[10];
    };

    static const size_t SIZE_OF_HEADER_TOPIC_ID = sizeof(std::uint32_t);
    static const size_t SIZE_OF_HEADER_BODY_LENGTH = sizeof(std::uint16_t);
    static const size_t SIZE_OF_HEADER = SIZE_OF_HEADER_TOPIC_ID + SIZE_OF_HEADER_BODY_LENGTH;

    Header header;

    byte* body;

    bool NeedReverse()
    {
        std::uint16_t test = 0x1234;
        std::uint16_t testR = htons(test);
        return test != testR;
    }

    std::uint64_t htonll(std::uint64_t data)
    {
        auto rBits = data;
        if (NeedReverse())
        {
            std::uint32_t lBits = (0x00000000FFFFFFFF & data);
            std::uint32_t rlBits = htonl(lBits);
            std::uint32_t hBits = (0xFFFFFFFF00000000 & data) >> 32;
            std::uint32_t rhBits = htonl(hBits);

            rBits = (((std::uint64_t)rlBits) << 32) | (std::uint64_t)rhBits;
        }
        return rBits;
    }

    std::uint64_t ntohll(std::uint64_t data)
    {
        auto rBits = data;
        if (NeedReverse())
        {
            std::uint32_t lBits = (0x00000000FFFFFFFF & data);
            std::uint32_t rlBits = ntohl(lBits);
            std::uint32_t hBits = (0xFFFFFFFF00000000 & data) >> 32;
            std::uint32_t rhBits = ntohl(hBits);

            rBits = (((std::uint64_t)rlBits) << 32) | (std::uint64_t)rhBits;
        }

        return rBits;
    }

public:

    TLVMessage()
    {
        header.bodyLength = 0;
        body = nullptr;
        release = true;
        offset = 0;
    }

    virtual ~TLVMessage()
    {
        if (release && body != nullptr)
        {
            delete[] body;
        }
    }

    static std::shared_ptr<TLVMessage> Generate(size_t size = 0)
    {
        auto msg = std::make_shared<TLVMessage>();
        if (size > 0)
        {
            msg->body = new byte[size];
        }
        msg->header.bodyLength = size;
        return msg;
    }

    static std::shared_ptr<TLVMessage> Generate(std::shared_ptr<Header> header, byte* data = nullptr)
    {
        auto msg = std::make_shared<TLVMessage>();

        msg->header.topicId = header->topicId;
        msg->header.bodyLength = header->bodyLength;

        if (data == nullptr)
        {
            if (header->bodyLength > 0)
            {
                msg->body = new byte[header->bodyLength];
            }
        }
        else
        {
            msg->body = data;
            msg->release = false;
        }

        return msg;
    }

    void Reset()
    {
        offset = 0;
    }

    byte* GetDataPointerWithOffset()
    {
        return body + offset;
    }

    bool IsAvailiable()
    {
        return offset < header.bodyLength;
    }

    void AppendT(std::uint32_t t)
    {
        t = htonl(t);
        AppendData((byte*)&t, sizeof(t));
    }

    template <typename T>
    void AppendLV(T& data)
    {
        std::uint16_t l = data.size();
        l = htons(l);
        AppendData((byte*)&l, sizeof(l));
        AppendData(data.data());
    }

    template <typename T>
    void AppendSubTLV(T& data, std::uint32_t msgId)
    {
        if (data)
        {
            AppendT(msgId);
            AppendLV(data);
        }
    }
//
//    template <typename ONE, typename ...T>
//    bool AppendData(ONE data1, T... data)
//    {
//        if (sizeof...(data) > 0)
//        {
//            return AppendData(data1) && AppendData(data...);
//        }
//        else
//        {
//            return AppendData(data1);
//        }
//    }

    template <typename T>
    bool AppendData(T data)
    {
        uint16_t size = sizeof(T);
        if (offset + size <= header.bodyLength)
        {
            memcpy(body + offset, &data, size);
            offset += size;
            return true;
        }
        return false;
    }

    bool AppendData(uint64_t data)
    {
        uint16_t size = sizeof(data);
        if (offset + size <= header.bodyLength)
        {
            auto dataToAppend = htonll(data);
            memcpy(body + offset, &dataToAppend, size);
            offset += size;
            return true;
        }
        return false;
    }

    bool AppendData(uint32_t data)
    {
        uint16_t size = sizeof(data);
        if (offset + size <= header.bodyLength)
        {
            auto dataToAppend = htonl(data);
            memcpy(body + offset, &dataToAppend, size);
            offset += size;
            return true;
        }
        return false;
    }

    bool AppendData(uint16_t data)
    {
        uint16_t size = sizeof(data);
        if (offset + size <= header.bodyLength)
        {
            auto dataToAppend = htons(data);
            memcpy(body + offset, &dataToAppend, size);
            offset += size;
            return true;
        }
        return false;
    }

    bool AppendData(std::string data)
    {
        uint16_t size = data.size();
        if (offset + size + sizeof(size) <= header.bodyLength)
        {
            memcpy(body + offset, data.c_str(), size);
            offset += data.size();
            return true;
        }
        return false;
    }

    bool AppendData(const byte* data, std::uint16_t size)
    {
        if (offset + size <= header.bodyLength)
        {
            memcpy(body + offset, data, size);
            offset += size;
            return true;
        }
        return false;
    }

    void NextT(std::uint32_t& data)
    {
        NextLV((byte*)&data, sizeof(data));
        data = ntohl(data);
    }

    void NextL(std::uint16_t& data)
    {
        NextLV((byte*)&data, sizeof(data));
        data = ntohs(data);
    }

    template <typename T>
    void NextLV(Data<T> &v)
    {
        T data;
        NextLV(data);
        v = data;
    }

    template <typename T>
    void NextLV(T& data)
    {
        uint16_t size;
        NextL(size);
        memcpy(&data, body + offset, size);
        offset += size;
    }

    void NextLV(std::uint16_t& data)
    {
        uint16_t size;
        NextL(size);
        memcpy(&data, body + offset, size);
        data = ntohs(data);
        offset += size;
    }

    void NextLV(std::uint32_t& data)
    {
        uint16_t size;
        NextL(size);
        memcpy(&data, body + offset, size);
        data = ntohl(data);
        offset += size;
    }

    void NextLV(std::uint64_t& data)
    {
        uint16_t size;
        NextL(size);
        memcpy(&data, body + offset, size);
        data = ntohll(data);
        offset += size;
    }

    void NextLV(std::string& data)
    {
        uint16_t size;
        NextL(size);
        auto temp = new char[size + 1];
        memcpy(temp, body + offset, size);
        offset += size;
        temp[size] = '\0';

        std::string str(temp);
        delete[] temp;
        data = str;
    }

    void NextLV(byte* data, std::uint16_t size)
    {
        memcpy(data, body + offset, size);
        offset += size;
    }

    void IgnoreBytes(size_t size)
    {
        offset += size;
    }

    void IgnoreLV()
    {
        uint16_t size;
        NextL(size);
        offset += size;
    }

    bool Finish()
    {
        if (offset <= header.bodyLength && offset != 0)
        {
            header.bodyLength = offset;
            return true;
        }

        return false;
    }

private:
    size_t offset;
    bool release;
};

}



#endif /* SERVER_NODES_CLOUD_TRANSPORT_TCP_TLVMESSAGE_H_ */
