#include "connection.hpp"

Connection::Connection(tcp::Socket* socket) : _socket(socket), _log(Logger("conn/" + std::to_string(socket->id()))) {
  _log.debug("connected...");
}
