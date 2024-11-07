#include "tcp.hpp"

namespace tcp {
  Listener::~Listener() {
    close();
    delete _socket;
  }

  void Listener::listen() {
    auto id = csocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (id == -1) {
      throw Error("failed to create socket");
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    addr.sin_port = htons(_port);

    if (bind(id, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      throw Error("failed to bind socket");
    }

    if (clisten(id, 5) < 0) {
      std::stringstream ss;
      ss << "failed to listen on socket: " << strerror(errno);
      throw Error(ss.str());
    }

    _socket = new Socket(id, addr);
  }

  Socket* Listener::accept() {
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int id = caccept(_socket->id(), (struct sockaddr *)&addr, &addr_len);

    if (id < 0) {
      return nullptr;
    }

    return new Socket(id, addr);
  }

  void Listener::close() {
    cclose(_socket->id());
  }
};
