#include "../../tcp/tcp.hpp"
#include "../../logger.hpp"
#include "../../connection.hpp"

namespace plugins::mqtt {
  class Connection : IConnection {
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
};
