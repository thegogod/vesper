#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

#include "tcp/tcp.hpp"
#include "connection.hpp"

class IPlugin {
  public:
    virtual std::string name() = 0;
    virtual std::string version() = 0;
};

class ITransportPlugin : public IPlugin {
  public:
    virtual IConnection connect(tcp::Socket* socket) = 0;
};

#endif PLUGIN_H
