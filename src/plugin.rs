use std::net::TcpStream;

use super::error::Error;
use super::packet::Packet;

pub trait Plugin {
    fn name(&self) -> String;
    fn version(&self) -> String;
}

pub trait TransportPlugin: Plugin {
    fn connect(&self, stream: TcpStream) -> impl Connection;
}

pub trait Connection {
    fn id(&self) -> String;
    fn handshake(&mut self, username: String, password: String) -> Result<(), Error>;
    fn read(&mut self) -> Result<impl Packet, Error>;
    fn write(&mut self, packet: &mut impl Packet) -> Result<(), Error>;
    fn close(&self) -> Result<(), Error>;
}
