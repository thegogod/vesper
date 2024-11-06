#include "tcp.hpp"

namespace tcp {
  Socket::~Socket() {
    close();
  }

  void Socket::close() {
    cclose(_id);
  }
}
