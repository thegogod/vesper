use std::io;

use serde::{Deserialize, Serialize};

use crate::error::Error;

#[derive(Copy, Clone, Debug, PartialEq, Serialize, Deserialize)]
#[repr(u8)]
pub enum Code {
    Connect,
    ConnectAck,
    Publish,
    PublishAck,
    PublishRec,
    PublishRel,
    PublishComp,
    Subscribe,
    SubscribeAck,
    UnSubscribe,
    UnSubscribeAck,
    Ping,
    PingAck,
    Disconnect,
}

impl ToString for Code {
    fn to_string(&self) -> String {
        return match *self {
            Code::Connect => String::from("connect"),
            Code::ConnectAck => String::from("connect_ack"),
            Code::Disconnect => String::from("disconnect"),
            Code::Publish => String::from("publish"),
            Code::PublishAck => String::from("publish_ack"),
            Code::PublishRec => String::from("publish_rec"),
            Code::PublishRel => String::from("publish_rel"),
            Code::PublishComp => String::from("publish_comp"),
            Code::Subscribe => String::from("subscribe"),
            Code::SubscribeAck => String::from("subscribe_ack"),
            Code::UnSubscribe => String::from("unsubscribe"),
            Code::UnSubscribeAck => String::from("unsubscribe_ack"),
            Code::Ping => String::from("ping"),
            Code::PingAck => String::from("ping_ack"),
        };
    }
}

impl std::convert::TryFrom<u8> for Code {
    type Error = Error;

    fn try_from(value: u8) -> Result<Self, Self::Error> {
        return match value {
            0 => Ok(Code::Connect),
            1 => Ok(Code::ConnectAck),
            2 => Ok(Code::Publish),
            3 => Ok(Code::PublishAck),
            4 => Ok(Code::PublishRec),
            5 => Ok(Code::PublishRel),
            6 => Ok(Code::PublishComp),
            7 => Ok(Code::Subscribe),
            8 => Ok(Code::SubscribeAck),
            9 => Ok(Code::UnSubscribe),
            10 => Ok(Code::UnSubscribeAck),
            11 => Ok(Code::Ping),
            12 => Ok(Code::PingAck),
            13 => Ok(Code::Disconnect),
            _ => Err(Error::from_str("invalid packet code")),
        };
    }
}

pub trait Packet: ToString {
    fn code(&self) -> Code;
    fn read(&mut self, reader: &mut dyn io::Read) -> Result<(), Error>;
    fn write(&mut self, writer: &mut dyn io::Write) -> Result<(), Error>;

    fn from_connect(&mut self, packet: impl Connect) -> Option<&impl Connect>;
    fn to_connect(&self) -> Option<&impl Connect>;
}

pub trait Connect: Packet {
    fn client_id(&self) -> String;
    fn username(&self) -> String;
    fn password(&self) -> String;
}

pub trait ConnectAck: Packet {
    fn return_code(&self) -> u8;
}

pub trait Publish: Packet {
    fn id(&self) -> u16;
    fn qos(&self) -> u8;
    fn topic(&self) -> String;
    fn payload(&self) -> [u8];
}

pub trait PublishAck: Packet {
    fn id(&self) -> u16;
}

pub trait Subscribe: Packet {
    fn id(&self) -> u16;
    fn topics(&self) -> [String];
}

pub trait SubscribeAck: Packet {
    fn id(&self) -> u16;
    fn return_codes(&self) -> [u8];
}

pub trait UnSubscribe: Packet {
    fn id(&self) -> u16;
    fn topics(&self) -> [String];
}

pub trait UnSubscribeAck: Packet {
    fn id(&self) -> u16;
}
