#ifndef IO_H
#define IO_H

#include "stdint.h"

namespace io {
  class Reader {
    public:
      virtual void read(char* buf) = 0;
  };

  class Writer {
    public:
      virtual void write(char* buf) = 0;
  };
};

#endif
