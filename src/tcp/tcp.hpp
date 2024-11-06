#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../error.cpp"

namespace tcp {
  constexpr auto clisten = listen;
  constexpr auto csocket = socket;
  constexpr auto caccept = accept;
  constexpr auto cclose = close;

  class Socket {
    public:
      Socket() = delete;
      Socket(int id, sockaddr_in addr) : _id(id), _addr(addr) { }
      ~Socket();

      int id() { return _id; }
      sockaddr_in addr() { return _addr; }
      void close();

    private:
      int _id;
      sockaddr_in _addr;
  };

  class Listener {
    public:
      Listener() = delete;
      Listener(int port) : _port(port) { }
      ~Listener();

      void listen();
      Socket* accept();
      void close();

    private:
      int _port;
      Socket* _socket;
      std::vector<Socket*> _conns;
  };
};
