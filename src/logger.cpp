#include <ctime>
#include <chrono>
#include <string>
#include <iostream>

#include "date_time.cpp"
#include "ansi.cpp"

using namespace std;

class ILogger {
  public:
    enum Level {
      Debug,
      Info,
      Warn,
      Error,
    };

    virtual void debug(const string& message) = 0;
    virtual void info(const string& message) = 0;
    virtual void warn(const string& message) = 0;
    virtual void error(const string& message) = 0;
    virtual void log(Level level, const string& message) = 0;

  protected:
    string level_to_string(Level level) {
      switch (level) {
      case Debug:
        return "debug";
      case Info:
        return "info";
      case Warn:
        return "warn";
      case Error:
        return "error";
      }
    }

    ANSI level_to_color(Level level) {
      switch (level) {
      case Debug:
        return ANSI::ForegroundGray;
      case Info:
        return ANSI::ForegroundCyan;
      case Warn:
        return ANSI::ForegroundYellow;
      case Error:
        return ANSI::ForegroundRed;
      }
    }
};

class Logger : public ILogger {
  public:
    Logger(string name) : name(name) { };
    ~Logger() = default;

    void debug(const string& message) {
      this->log(Debug, message);
    }

    void info(const string& message) {
      this->log(Info, message);
    }

    void warn(const string& message) {
      this->log(Warn, message);
    }

    void error(const string& message) {
      this->log(Error, message);
    }

    void log(Level level, const string& message) {
      auto now = new DateTime();

      cout << this->level_to_color(level)
           << "- " << *now << " " << ANSI::Bold
           << ANSI::Underline << name << ANSI::UnderlineReset << " "
           << "[" << this->level_to_string(level) << "] " << ANSI::Reset
           << message << endl;
    }

  private:
    string name;
};
