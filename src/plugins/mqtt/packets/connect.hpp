#ifndef PLUGINS_MQTT_PACKETS_CONNECT_H
#define PLUGINS_MQTT_PACKETS_CONNECT_H

#include <string>

#include "../../../code.hpp"
#include "../../../packet.hpp"

#include "header.hpp"

namespace plugins::mqtt::packets {
  class Connect : public IConnect {
    public:
      const Header header = Header(Code::Connect);

      Code code() { return header.code; }
      std::string client_id() { return _client_id; }
      std::string username() { return _username; }
      std::string password() { return _password; }

    private:
      std::string _client_id;
      std::string _username;
      std::string _password;
  };
};

#endif
