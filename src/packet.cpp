#include "code.cpp"

class IPacket {
  public:
    virtual Code code() = 0;
    virtual string to_string() = 0;
};
