#ifndef CONNECTION_H
#define CONNECTION_H

#include "tcp/tcp.hpp"
#include "io/io.hpp"
#include "logger.hpp"

class Connection {
  public:
    Connection() = delete;
    Connection(tcp::Socket* socket);

    ~Connection() { delete _socket; }

    int id() { return _socket->id(); }

  private:
    tcp::Socket* _socket;
    Logger _log;
};

#endif
