#include "code.cpp"

class IPacket {
  public:
    virtual Code code() = 0;
    virtual std::string to_string() = 0;
};
