#include <stdint.h>
#include <string>

class Code {
  public:
    enum Value : uint8_t {
      Connect = 1,
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
    };

    Code() = default;
    constexpr Code(Value code) : value(code) { }
    constexpr operator Value() const { return value; }
    explicit operator bool() const = delete;
    constexpr bool operator==(Code a) const { return value == a.value; }
    constexpr bool operator!=(Code a) const { return value != a.value; }

    std::string to_string() {
      switch (value) {
      case Connect:
        return "connect";
      case ConnectAck:
        return "connect_ack";
      case Publish:
        return "publish";
      case PublishAck:
        return "publish_ack";
      case PublishRec:
        return "publish_rec";
      case PublishRel:
        return "publish_rel";
      case PublishComp:
        return "publish_comp";
      case Subscribe:
        return "subscribe";
      case SubscribeAck:
        return "subscribe_ack";
      case UnSubscribe:
        return "unsubscribe";
      case UnSubscribeAck:
        return "unsubscribe_ack";
      case Ping:
        return "ping";
      case PingAck:
        return "ping_ack";
      case Disconnect:
        return "disconnect";
      }
    }

  private:
    Value value;
};
