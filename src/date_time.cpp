#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

class DateTime {
  public:
    DateTime() : value(std::chrono::system_clock::now()) { }

    friend std::ostream& operator<<(std::ostream& os, DateTime& date) {
      os << date.to_string();
      return os;
    }

    std::string to_string() {
      std::stringstream ss;
      auto time = std::chrono::system_clock::to_time_t(value);
      auto info = localtime(&time);

      ss << std::put_time(info, "%Y-%m-%d %H:%M:%S");
      return ss.str();
    }

  private:
    std::chrono::system_clock::time_point value;
};
