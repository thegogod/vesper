#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
using namespace chrono;

class DateTime {
  public:
    DateTime() : value(system_clock::now()) { }

    friend ostream& operator<<(ostream& os, DateTime& date) {
      os << date.to_string();
      return os;
    }

    string to_string() {
      stringstream ss;
      auto time = system_clock::to_time_t(value);
      auto info = localtime(&time);

      ss << put_time(info, "%Y-%m-%d %H:%M:%S");
      return ss.str();
    }

  private:
    system_clock::time_point value;
};
