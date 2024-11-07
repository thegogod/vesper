#include "logger.cpp"
#include "tcp/tcp.hpp"
#include "connection.cpp"

int main(int argc, char *argv[]) {
  auto log = Logger("main");
  auto listener = new tcp::Listener(1883);

  try {
    listener->listen();
    log.info("listening...");

    while (true) {
      auto socket = listener->accept();

      if (socket == nullptr) {
        continue;
      }

      log.info("new connection!");
      auto conn = new Connection(socket);
    }
  } catch (std::exception e) {
    log.error(e.what());
  }

  delete listener;
  return 0;
}
