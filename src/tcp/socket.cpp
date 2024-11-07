#include "tcp.hpp"

namespace tcp {
  Socket::~Socket() {
    close();
  }

  void Socket::read(char* buf) {
    cread(_id, buf, sizeof(buf));
  }

  void Socket::write(char* buf) {
    cwrite(_id, buf, sizeof(buf));
  }

  void Socket::close() {
    cclose(_id);
  }
}
