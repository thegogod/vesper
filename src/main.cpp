#include "logger.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  auto log = Logger("main");
  log.info("hello world");
  return 0;
}
