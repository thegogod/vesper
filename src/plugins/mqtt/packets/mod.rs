use std::io;

use byteorder::ReadBytesExt;
use connect::Connect;
use header::Header;

use crate::{
    error::Error,
    packet::{Code, Packet},
};

mod bytes;
pub mod connect;
pub mod header;

pub fn read(reader: &mut dyn io::Read) -> Result<impl Packet, Error> {
    let byte = match reader.read_u8() {
        Ok(v) => v,
        Err(err) => return Err(Error::new(err.to_string())),
    };

    let header = match Header::read(byte, reader) {
        Ok(v) => v,
        Err(err) => return Err(Error::new(err.to_string())),
    };

    let mut packet = match from_header(header) {
        Ok(v) => v,
        Err(err) => return Err(Error::new(err.to_string())),
    };

    let mut payload: Vec<u8> = vec![0; header.length as usize];
    let len = match reader.read_to_end(&mut payload) {
        Ok(v) => v,
        Err(err) => return Err(Error::new(err.to_string())),
    };

    if len != header.length as usize {
        return Err(Error::from_str("failed to read expected data"));
    }

    return match packet.read(reader) {
        Ok(_) => Ok(packet),
        Err(err) => Err(err),
    };
}

pub fn from_header(header: Header) -> Result<impl Packet, Box<dyn std::error::Error>> {
    return match header.code {
        Code::Connect => Ok(Connect::from_header(header)),
        _ => Err(Box::new(Error::from_str(format!("unsupported packet type: {}", header.code.to_string()).as_str()))),
    };
}
