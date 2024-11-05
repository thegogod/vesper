use std::io;

use byteorder::{BigEndian, ByteOrder};

pub fn read(reader: &mut dyn io::Read) -> Result<Vec<u8>, Box<dyn std::error::Error>> {
    let length = match read_u16(reader) {
        Ok(v) => v,
        Err(err) => return Err(err),
    };

    let mut bytes: Vec<u8> = vec![0; length as usize];

    return match reader.read_to_end(&mut bytes) {
        Ok(_) => Ok(bytes),
        Err(err) => Err(Box::new(err)),
    };
}

pub fn write(writer: &mut dyn io::Write, value: &[u8]) {
    let mut length: [u8; 2] = [0, 0];
    BigEndian::write_u16(&mut length, value.len() as u16);
    let _ = writer.write_all(&length);
    let _ = writer.write_all(value);
}

pub fn read_string(reader: &mut dyn io::Read) -> Result<String, Box<dyn std::error::Error>> {
    let bytes = match read(reader) {
        Ok(v) => v,
        Err(err) => return Err(err),
    };

    return match String::from_utf8(bytes) {
        Ok(v) => Ok(v),
        Err(err) => Err(Box::new(err)),
    };
}

pub fn write_string(writer: &mut dyn io::Write, value: String) {
    return write(writer, value.as_bytes());
}

pub fn read_u8(reader: &mut dyn io::Read) -> Result<u8, Box<dyn std::error::Error>> {
    let mut buf: [u8; 1] = [0];

    return match reader.read(&mut buf) {
        Ok(_) => Ok(buf[0]),
        Err(err) => Err(Box::new(err)),
    };
}

pub fn write_u8(writer: &mut dyn io::Write, value: u8) {
    let buf: [u8; 1] = [value];
    let _ = writer.write(&buf);
}

pub fn read_u16(reader: &mut dyn io::Read) -> Result<u16, Box<dyn std::error::Error>> {
    let mut buf: [u8; 2] = [0, 0];

    return match reader.read(&mut buf) {
        Ok(_) => Ok(BigEndian::read_u16(&buf)),
        Err(err) => Err(Box::new(err)),
    };
}

pub fn write_u16(writer: &mut dyn io::Write, value: u16) -> [u8; 2] {
    let mut buf: [u8; 2] = [0, 0];
    BigEndian::write_u16(&mut buf, value);
    let _ = writer.write(&buf);
    return buf;
}

pub fn from_bool(value: bool) -> u8 {
    return match value {
        true => 1,
        false => 0,
    };
}

pub fn read_length(reader: &mut dyn io::Read) -> Result<u32, Box<dyn std::error::Error>> {
    let mut length: u32 = 0;
    let mut multiplier: u32 = 0;
    let mut buf: [u8; 1] = [0];

    while multiplier < 27 {
        _ = match reader.read(&mut buf) {
            Ok(size) => size,
            Err(err) => return Err(Box::new(err)),
        };

        let digit = buf[0];
        length |= u32::from(digit & 127) << multiplier;

        if (digit & 128) == 0 {
            break;
        }

        multiplier += 7;
    }

    return Ok(length);
}

pub fn write_length(
    writer: &mut dyn io::Write,
    mut length: u32,
) -> Result<(), Box<dyn std::error::Error>> {
    let mut buf: Vec<u8> = vec![];

    loop {
        let mut digit = (length % 128) as u8;
        length = length / 128;

        if length > 0 {
            digit |= 0x80;
        }

        buf.push(digit);

        if length == 0 {
            break;
        }
    }

    return match writer.write(&buf) {
        Ok(_) => Ok(()),
        Err(err) => Err(Box::new(err)),
    };
}
