#ifndef PACKET_H
#define PACKET_H

#include <string>

#include "code.hpp"

class IPacket {
  public:
    virtual Code code() = 0;
};

class IConnect : public IPacket {
  public:
    virtual std::string client_id() = 0;
    virtual std::string username() = 0;
    virtual std::string password() = 0;
};

#endif
