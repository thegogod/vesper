#include "tcp.hpp"

namespace tcp {
  Socket::~Socket() {
    close();
  }

  void Socket::read(uint8_t buf[]) {
    cread(_id, buf, sizeof(buf));
  }

  void Socket::write(uint8_t buf[]) {
    cwrite(_id, buf, sizeof(buf));
  }

  void Socket::close() {
    cclose(_id);
  }
}
