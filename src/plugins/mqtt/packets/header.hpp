#ifndef PLUGINS_MQTT_PACKETS_HEADER_H
#define PLUGINS_MQTT_PACKETS_HEADER_H

#include "../../../io/io.hpp"
#include "../../../code.hpp"

namespace plugins::mqtt::packets {
  struct Header {
    Code code;
    bool dup = false;
    uint8_t qos = 0;
    bool retain = false;
    int length = 0;

    Header() = delete;
    Header(Code code) : code(code) { }

    void read(char type_and_flags, io::Reader& reader);
    void write(io::Writer& write);
  };
};

#endif
