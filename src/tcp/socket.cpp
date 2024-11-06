#include "tcp.hpp"

namespace tcp {
  void Socket::close() {
    cclose(_id);
  }
}
