#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <exception>

class Error : public std::exception {
  public:
    Error(std::string message) : message(message) { }

    const char* what() {
      return message.c_str();
    }

  private:
    const std::string message;
};

#endif
