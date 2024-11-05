use std::io;

use serde::{Deserialize, Serialize};

use crate::error::Error;
use crate::packet;

use super::{bytes, header::Header};

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
pub struct Connect {
    pub header: Header,
    pub protocol_name: String,
    pub protocol_version: u8,
    pub clean_session: bool,
    pub will_flag: bool,
    pub will_qos: u8,
    pub will_retain: bool,
    pub username_flag: bool,
    pub password_flag: bool,
    pub reserved_bit: u8,
    pub keep_alive: u16,
    pub client_id: String,
    pub will_topic: String,
    pub will_message: Vec<u8>,
    pub username: String,
    pub password: String,
}

impl Connect {
    pub fn from_header(header: Header) -> Self {
        let mut v = Self::default();
        v.header = header;
        return v;
    }
}

impl ToString for Connect {
    fn to_string(&self) -> String {
        return match serde_json::to_string(self) {
            Ok(v) => v,
            Err(err) => panic!("{}", err),
        };
    }
}

impl packet::Packet for Connect {
    fn code(&self) -> packet::Code {
        return self.header.code;
    }

    fn read(&mut self, reader: &mut dyn io::Read) -> Result<(), Error> {
        self.protocol_name = match bytes::read_string(reader) {
            Ok(v) => v,
            Err(err) => return Err(Error::new(err.to_string())),
        };

        self.protocol_version = match bytes::read_u8(reader) {
            Ok(v) => v,
            Err(err) => return Err(Error::new(err.to_string())),
        };

        let options = match bytes::read_u8(reader) {
            Ok(v) => v,
            Err(err) => return Err(Error::new(err.to_string())),
        };

        self.reserved_bit = 1 & options;
        self.clean_session = 1 & (options >> 1) > 0;
        self.will_flag = 1 & (options >> 2) > 0;
        self.will_qos = 3 & (options >> 3);
        self.will_retain = 1 & (options >> 5) > 0;
        self.password_flag = 1 & (options >> 6) > 0;
        self.username_flag = 1 & (options >> 7) > 0;
        self.keep_alive = match bytes::read_u16(reader) {
            Ok(v) => v,
            Err(err) => return Err(Error::new(err.to_string())),
        };

        self.client_id = match bytes::read_string(reader) {
            Ok(v) => v,
            Err(err) => return Err(Error::new(err.to_string())),
        };

        if self.will_flag {
            self.will_topic = match bytes::read_string(reader) {
                Ok(v) => v,
                Err(err) => return Err(Error::new(err.to_string())),
            };

            self.will_message = match bytes::read(reader) {
                Ok(v) => v,
                Err(err) => return Err(Error::new(err.to_string())),
            };
        }

        if self.username_flag {
            self.username = match bytes::read_string(reader) {
                Ok(v) => v,
                Err(err) => return Err(Error::new(err.to_string())),
            };
        }

        if self.password_flag {
            self.password = match bytes::read_string(reader) {
                Ok(v) => v,
                Err(err) => return Err(Error::new(err.to_string())),
            };
        }

        return Ok(());
    }

    fn write(&mut self, writer: &mut dyn io::Write) -> Result<(), Error> {
        let mut buf: Vec<u8> = vec![];

        bytes::write_string(&mut buf, self.protocol_name.to_owned());
        bytes::write_u8(&mut buf, self.protocol_version);
        bytes::write_u8(
            &mut buf,
            bytes::from_bool(self.clean_session) << 1
                | bytes::from_bool(self.will_flag) << 2
                | self.will_qos << 3
                | bytes::from_bool(self.will_retain) << 5
                | bytes::from_bool(self.password_flag) << 6
                | bytes::from_bool(self.username_flag) << 7,
        );

        bytes::write_u16(&mut buf, self.keep_alive);
        bytes::write_string(&mut buf, self.client_id.to_owned());

        if self.will_flag {
            bytes::write_string(&mut buf, self.will_topic.to_owned());
            bytes::write(&mut buf, self.will_message.as_slice());
        }

        if self.username_flag {
            bytes::write_string(&mut buf, self.username.clone());
        }

        if self.password_flag {
            bytes::write_string(&mut buf, self.password.clone());
        }

        self.header.length = buf.len() as u32;

        match self.header.write(writer) {
            Ok(_) => (),
            Err(err) => return Err(Error::new(err.to_string())),
        };

        bytes::write(writer, buf.as_slice());
        return Ok(());
    }

    fn from_connect(&mut self, packet: impl packet::Connect) -> Option<&impl packet::Connect> {
        self.header.code = packet::Code::Connect;
        self.client_id = packet.client_id();
        self.username = packet.username();
        self.password = packet.password();
        return Some(self);
    }

    fn to_connect(&self) -> Option<&impl packet::Connect> {
        return Some(self);
    }
}

impl packet::Connect for Connect {
    fn client_id(&self) -> String {
        return self.client_id.clone();
    }

    fn username(&self) -> String {
        return self.username.clone();
    }

    fn password(&self) -> String {
        return self.password.clone();
    }
}
