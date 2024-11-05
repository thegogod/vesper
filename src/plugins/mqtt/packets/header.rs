use serde::{Deserialize, Serialize};
use std::io;

use crate::error::Error;
use crate::packet::Code;

use super::bytes;

#[derive(Copy, Clone, Debug, Serialize, Deserialize)]
pub struct Header {
    pub code: Code,
    pub dup: bool,
    pub qos: u8,
    pub retain: bool,
    pub length: u32,
}

impl Header {
    pub fn read(
        type_and_flags: u8,
        reader: &mut dyn io::Read,
    ) -> Result<Self, Box<dyn std::error::Error>> {
        let code = match Code::try_from(type_and_flags >> 4) {
            Ok(code) => code,
            Err(err) => return Err(Box::new(Error::new(err.to_string()))),
        };

        let length = match bytes::read_length(reader) {
            Ok(len) => len,
            Err(err) => return Err(err),
        };

        return Ok(Self {
            code,
            length,
            dup: (type_and_flags >> 3) & 0x01 > 0,
            qos: (type_and_flags >> 1) & 0x03,
            retain: type_and_flags & 0x01 > 0,
        });
    }

    pub fn write(&self, writer: &mut dyn io::Write) -> Result<(), Box<dyn std::error::Error>> {
        let buf: [u8; 1] = [(self.code as u8) << 4
            | bytes::from_bool(self.dup) << 3
            | self.qos << 1
            | bytes::from_bool(self.retain)];

        let _ = writer.write(&buf);

        return match bytes::write_length(writer, self.length) {
            Ok(_) => Ok(()),
            Err(err) => Err(err),
        };
    }
}

impl Default for Header {
    fn default() -> Self {
        return Self {
            code: Code::Connect,
            dup: false,
            qos: 0,
            retain: false,
            length: 0,
        };
    }
}
