#include <string>

#include "../../tcp/tcp.hpp"
#include "../../plugin.hpp"
#include "../../logger.hpp"
#include "../../connection.hpp"

#include "connection.cpp"

namespace plugins::mqtt {
  class Plugin : public ITransportPlugin {
    public:
      std::string name() { return "mqtt"; }
      std::string version() { return "1.0.0"; }

      IConnection connect(tcp::Socket* socket) {
        return Connection(socket);
      }

    private:
      Logger _log = Logger("mqtt");
  };
};
