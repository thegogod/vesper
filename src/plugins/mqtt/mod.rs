pub mod connection;
pub mod packets;

use std::net::*;

use crate::plugin;

use connection::Connection;

#[derive(Clone, Copy, Debug)]
pub struct Plugin {}

impl Plugin {
    pub fn new() -> Self {
        return Self {};
    }
}

impl plugin::Plugin for Plugin {
    fn name(&self) -> String {
        return String::from("mqtt");
    }

    fn version(&self) -> String {
        return String::from("1.0.0");
    }
}

impl plugin::TransportPlugin for Plugin {
    fn connect(&self, stream: TcpStream) -> impl plugin::Connection {
        return Connection::new(stream);
    }
}
