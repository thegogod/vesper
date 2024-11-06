#include <stdint.h>
#include <string>

using namespace std;

class ANSI {
  public:
    enum Code {
      Reset,

      Bold,
      BoldReset,
      Dim,
      DimReset,
      Italic,
      ItalicReset,
      Underline,
      UnderlineReset,
      Blink,
      BlinkReset,
      Reverse,
      ReverseReset,
      Hide,
      HideReset,
      Strike,
      StrikeReset,

      ForegroundReset,
      BackgroundReset,
      ForegroundBlack,
      BackgroundBlack,
      ForegroundRed,
      BackgroundRed,
      ForegroundGreen,
      BackgroundGreen,
      ForegroundYellow,
      BackgroundYellow,
      ForegroundBlue,
      BackgroundBlue,
      ForegroundMagenta,
      BackgroundMagenta,
      ForegroundCyan,
      BackgroundCyan,
      ForegroundWhite,
      BackgroundWhite,
      ForegroundGray,
      ForegroundDefault,
      BackgroundDefault,
    };

    ANSI() = default;
    constexpr ANSI(Code code) : value(code) { }
    constexpr operator Code() const { return value; }
    explicit operator bool() const = delete;
    constexpr bool operator==(ANSI a) const { return value == a.value; }
    constexpr bool operator!=(ANSI a) const { return value != a.value; }

    friend ostream& operator<<(ostream& os, ANSI& ansi) {
      os << ansi.to_string();
      return os;
    }

    friend ostream& operator<<(ostream& os, const Code& code) {
      os << ANSI(code).to_string();
      return os;
    }

    string to_string() {
      switch (value) {
      case Reset:
        return "\x1b[0m";
      case Bold:
        return "\x1b[1m";
      case BoldReset:
        return "\x1b[22m";
      case Dim:
        return "\x1b[2m";
      case DimReset:
        return "\x1b[22m";
      case Italic:
        return "\x1b[3m";
      case ItalicReset:
        return "\x1b[23m";
      case Underline:
        return "\x1b[4m";
      case UnderlineReset:
        return "\x1b[24m";
      case Blink:
        return "\x1b[5m";
      case BlinkReset:
        return "\x1b[25m";
      case Reverse:
        return "\x1b[7m";
      case ReverseReset:
        return "\x1b[27m";
      case Hide:
        return "\x1b[8m";
      case HideReset:
        return "\x1b[28m";
      case Strike:
        return "\x1b[9m";
      case StrikeReset:
        return "\x1b[29m";
      case ForegroundReset:
        return "\x1b[0m";
      case BackgroundReset:
        return "\x1b[0m";
      case ForegroundBlack:
        return "\x1b[30m";
      case BackgroundBlack:
        return "\x1b[40m";
      case ForegroundRed:
        return "\x1b[31m";
      case BackgroundRed:
        return "\x1b[41m";
      case ForegroundGreen:
        return "\x1b[32m";
      case BackgroundGreen:
        return "\x1b[42m";
      case ForegroundYellow:
        return "\x1b[33m";
      case BackgroundYellow:
        return "\x1b[43m";
      case ForegroundBlue:
        return "\x1b[34m";
      case BackgroundBlue:
        return "\x1b[44m";
      case ForegroundMagenta:
        return "\x1b[35m";
      case BackgroundMagenta:
        return "\x1b[45m";
      case ForegroundCyan:
        return "\x1b[36m";
      case BackgroundCyan:
        return "\x1b[46m";
      case ForegroundWhite:
        return "\x1b[37m";
      case BackgroundWhite:
        return "\x1b[47m";
      case ForegroundGray:
        return "\x1b[90m";
      case ForegroundDefault:
        return "\x1b[39m";
      case BackgroundDefault:
        return "\x1b[49m";
      }
    }

  private:
    Code value;
};
