#ifndef PLUGINS_MQTT_PACKETS_CONNECT_H
#define PLUGINS_MQTT_PACKETS_CONNECT_H

#include <string>

#include "../../../code.hpp"
#include "../../../packet.hpp"

#include "header.hpp"

namespace plugins::mqtt::packets {
  class Connect : public IConnect {
    public:
      Header header = Header(Code::Connect);

      Code code();
      std::string to_string();
  };
};

#endif
