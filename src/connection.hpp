#ifndef CONNECTION_H
#define CONNECTION_H

#include "tcp/tcp.hpp"
#include "io/io.hpp"

#include "logger.hpp"
#include "packet.hpp"

class IConnection {
  public:
    virtual int id() = 0;
    virtual bool handshake(std::string username, std::string password) = 0;
    virtual IPacket read() = 0;
    virtual void write(IPacket packet) = 0;
    virtual void close() = 0;
};

#endif
