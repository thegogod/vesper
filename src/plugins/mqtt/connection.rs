use std::net::TcpStream;

use crate::error::Error;
use crate::packet::{Code, Connect, Packet};
use crate::plugin;

use super::packets;

#[derive(Debug)]
pub struct Connection {
    stream: TcpStream,
}

impl Connection {
    pub fn new(stream: TcpStream) -> Connection {
        return Self { stream };
    }
}

impl plugin::Connection for Connection {
    fn id(&self) -> String {
        return self.stream.local_addr().unwrap().to_string();
    }

    fn handshake(&mut self, username: String, password: String) -> Result<(), Error> {
        let mut packet = match packets::read(&mut self.stream) {
            Ok(v) => v,
            Err(err) => return Err(err),
        };

        if packet.code() != Code::Connect {
            return Err(Error::from_str("expected connect packet"));
        }

        let connect = match packet.to_connect() {
            Some(v) => v,
            None => return Err(Error::from_str("expected connect packet")),
        };

        if username != connect.username() || password != connect.password() {
            return Err(Error::from_str("unauthorized"));
        }

        return match packet.write(&mut self.stream) {
            Ok(_) => Ok(()),
            Err(err) => Err(err),
        };
    }

    fn read(&mut self) -> Result<impl Packet, Error> {
        return packets::read(&mut self.stream);
    }

    fn write(&mut self, packet: &mut impl Packet) -> Result<(), Error> {
        return match packet.write(&mut self.stream) {
            Ok(_) => Ok(()),
            Err(err) => Err(err),
        };
    }

    fn close(&self) -> Result<(), Error> {
        return match self.stream.shutdown(std::net::Shutdown::Both) {
            Ok(_) => Ok(()),
            Err(err) => Err(Error::new(err.to_string())),
        };
    }
}
