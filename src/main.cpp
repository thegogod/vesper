#include <thread>

#include "logger.hpp"
#include "tcp/tcp.hpp"
#include "plugin.hpp"
#include "connection.hpp"

#include "plugins/mqtt/plugin.cpp"

const ITransportPlugin mqtt = plugins::mqtt::Plugin();

void on_connect(tcp::Socket &socket) {
  auto conn = mqtt.connect(&socket);

  if (!conn.handshake("", "")) {
    return;
  }

  while (true) {
  }
}

int main(int argc, char *argv[]) {
  auto log = Logger("main");
  auto listener = tcp::Listener(1883);

  try {
    listener.listen();
    log.info("listening...");

    while (true) {
      auto socket = listener.accept();

      if (socket == nullptr) {
        continue;
      }

      std::thread t(on_connect, std::ref(*socket));
      t.detach();
    }
  } catch (std::exception e) {
    log.error(e.what());
  }

  return 0;
}
