use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Error {
    message: String,
}

impl Error {
    pub fn new(message: String) -> Error {
        return Error { message };
    }

    pub fn from_str(message: &str) -> Error {
        return Error {
            message: String::from(message),
        };
    }
}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.message)
    }
}

impl std::error::Error for Error {
    fn description(&self) -> &str {
        return self.message.as_str();
    }
}
