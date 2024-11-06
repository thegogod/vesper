#include "logger.cpp"
#include "tcp/tcp.hpp"

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
    }
  } catch (std::exception e) {
    log.error(e.what());
  }

  delete listener;
  return 0;
}
