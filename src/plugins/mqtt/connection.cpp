#include "../../tcp/tcp.hpp"
#include "../../logger.hpp"
#include "../../connection.hpp"

namespace plugins::mqtt {
  class Connection : public IConnection {
    public:
      Connection() = delete;
      Connection(tcp::Socket* socket);
      ~Connection() { delete _socket; }

      int id() { return _socket->id(); }
      Logger log() { return _log; }
      void close() { _socket->close(); }

    private:
      tcp::Socket* _socket;
      Logger _log;
  };

  Connection::Connection(tcp::Socket* socket) :
    _socket(socket),
    _log(Logger("conn/" + std::to_string(socket->id())))
  {
    _log.debug("connected...");
  }
};
