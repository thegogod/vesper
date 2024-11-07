#include "tcp/tcp.hpp"
#include "io/io.hpp"

class Connection {
  public:
    Connection() = delete;
    Connection(tcp::Socket* socket) : _socket(socket) { }
    ~Connection() { delete _socket; }

  private:
    tcp::Socket* _socket;
};
