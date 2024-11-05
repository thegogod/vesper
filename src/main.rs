mod error;
mod packet;
mod plugin;
mod plugins;

use std::{net::TcpListener, thread};

use log::*;

use packet::Packet;
use plugin::{Connection, TransportPlugin};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let env = env_logger::Env::default()
        .filter_or("FMQ_LOG_LEVEL", "trace")
        .write_style_or("FMQ_LOG_STYLE", "always");

    env_logger::init_from_env(env);

    let transport = plugins::mqtt::Plugin::new();
    let listener = TcpListener::bind("127.0.0.1:1883")?;
    info!(target: "main", "listening on 1883...");

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        thread::spawn(move || {
            let mut conn = transport.connect(stream);
            let id = conn.id();
            info!(target: "main", "{}", conn.id());

            loop {
                let packet = match conn.read() {
                    Ok(v) => v,
                    Err(err) => {
                        error!(target: id.as_str(), "{}", err.to_string());
                        return;
                    }
                };

                info!(target: id.as_str(), "{}", packet.code().to_string());
            }
        });
    }

    return Ok(());
}
