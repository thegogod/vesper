#include <string>
#include <exception>

class Error : public std::exception {
  public:
    Error(std::string message) : message(message) { }

    const char* what() {
      return message.c_str();
    }

  private:
    std::string message;
};
