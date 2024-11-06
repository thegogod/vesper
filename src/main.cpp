#include "logger.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  Logger *log = new Logger("main");
  log->info("hello world");
  return 0;
}
