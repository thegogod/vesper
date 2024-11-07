#include "stdint.h"

namespace io {
  class Reader {
    public:
      virtual void read(uint8_t buf[]) = 0;
  };

  class Writer {
    public:
      virtual void write(uint8_t buf[]) = 0;
  };
};
