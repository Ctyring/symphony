/**
 * @file socket_stream.h
 * @brief Socket流式接口封装
 * @author cty
 * @email 173479693@qq.com
 * @date 2019-06-06
 * @copyright Copyright (c) cty All rights reserved
 */
#ifndef __SYMPHONY_SOCKET_STREAM_H__
#define __SYMPHONY_SOCKET_STREAM_H__

#include "symphony/iomanager.h"
#include "symphony/mutex.h"
#include "symphony/socket.h"
#include "symphony/stream.h"

namespace symphony {

/**
 * @brief Socket流
 */
class SocketStream : public Stream {
   public:
    typedef std::shared_ptr<SocketStream> ptr;

    /**
     * @brief 构造函数
     * @param[in] sock Socket类
     * @param[in] owner 是否完全控制
     */
    SocketStream(Socket::ptr sock, bool owner = true);

    /**
     * @brief 析构函数
     * @details 如果m_owner=true,则close
     */
    ~SocketStream();

    /**
     * @brief 读取数据
     * @param[out] buffer 待接收数据的内存
     * @param[in] length 待接收数据的内存长度
     * @return
     *      @retval >0 返回实际接收到的数据长度
     *      @retval =0 socket被远端关闭
     *      @retval <0 socket错误
     */
    virtual int read(void* buffer, size_t length) override;

    /**
     * @brief 读取数据
     * @param[out] ba 接收数据的ByteArray
     * @param[in] length 待接收数据的内存长度
     * @return
     *      @retval >0 返回实际接收到的数据长度
     *      @retval =0 socket被远端关闭
     *      @retval <0 socket错误
     */
    virtual int read(ByteArray::ptr ba, size_t length) override;

    /**
     * @brief 写入数据
     * @param[in] buffer 待发送数据的内存
     * @param[in] length 待发送数据的内存长度
     * @return
     *      @retval >0 返回实际接收到的数据长度
     *      @retval =0 socket被远端关闭
     *      @retval <0 socket错误
     */
    virtual int write(const void* buffer, size_t length) override;

    /**
     * @brief 写入数据
     * @param[in] ba 待发送数据的ByteArray
     * @param[in] length 待发送数据的内存长度
     * @return
     *      @retval >0 返回实际接收到的数据长度
     *      @retval =0 socket被远端关闭
     *      @retval <0 socket错误
     */
    virtual int write(ByteArray::ptr ba, size_t length) override;

    /**
     * @brief 关闭socket
     */
    virtual void close() override;

    /**
     * @brief 返回Socket类
     */
    Socket::ptr getSocket() const { return m_socket; }

    /**
     * @brief 返回是否连接
     */
    bool isConnected() const;

    Address::ptr getRemoteAddress();
    Address::ptr getLocalAddress();
    std::string getRemoteAddressString();
    std::string getLocalAddressString();

   protected:
    /// Socket类
    Socket::ptr m_socket;
    /// 是否主控
    bool m_owner;
};

}  // namespace symphony

#endif