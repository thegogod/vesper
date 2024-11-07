#ifndef PACKET_H
#define PACKET_H

#include "code.hpp"

class IPacket {
  public:
    virtual Code code() = 0;
    virtual std::string to_string() = 0;
};

#endif
