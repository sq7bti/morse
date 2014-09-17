#include <Energia.h>
#include "morseclass.h"

volatile bool _in_char = false, out_state = false;

void morse::begin(uint8_t _outPin, unsigned int _cpm = 100, bool _verbose = false) {
  _head = _tail = 0;
  outPin = _outPin;
  dot = 6000UL / _cpm;
  verbose = _verbose;
  if(_outPin != 0) {
    pinMode(outPin, OUTPUT);
    digitalWrite(outPin, HIGH);
    delay(dot);
    digitalWrite(outPin, LOW);
    delay(dot);
    digitalWrite(outPin, HIGH);
    delay(3 * dot);
    digitalWrite(outPin, LOW);
    if(verbose) {
      Serial.print("output pin: ");
      Serial.println(outPin, DEC);
      Serial.print("dot length: ");
      Serial.print(dot, DEC);
      Serial.println("ms");
    }
  }
};

void morse::begin(void (*mark)(), void (*space)(), unsigned int _cpm = 100, bool _verbose = false) {
  _mark = mark;
  _space = space;
  begin(0, _cpm, _verbose);
};

void morse::append(const char *str) {
  uint8_t i = 0;
  while(i < strlen(str)) {
    _buffer[_head++] = str[i++];
    _head %= BUFFER_SIZE;
  };
};

void morse::send(char c) {
  switch(c) {
  case '=':
    append("-...-");
    break;
  case '_':
    append("..--.-");
    break;
  case '-':
    append("-....-");
    break;
  case ',':
    append("--..--");
    break;
  case ';':
    append("-.-.-.");
    break;
  case ':':
    append("---...");
    break;
  case '!':
    append("-.-.--");
    break;
  case '?':
    append("..--..");
    break;
  case '/':
    append("-..-.");
    break;
  case '.':
    append(".-.-.-");
    break;
    //case ''':append(".----."); break;
  case '"':
    append(".-..-.");
    break;
  case '(':
    append("-.--.");
    break;
  case ')':
    append("-.--.-");
    break;
  case '@':
    append(".--.-.");
    break;
  case '$':
    append("...-..-");
    break;
  case '&':
    append(".-...");
    break;
  case '+':
    append(".-.-.");
    break;
  case '0':
    append("-----");
    break;
  case '1':
    append(".----");
    break;
  case '2':
    append("..---");
    break;
  case '3':
    append("...--");
    break;
  case '4':
    append("....-");
    break;
  case '5':
    append(".....");
    break;
  case '6':
    append("-....");
    break;
  case '7':
    append("--...");
    break;
  case '8':
    append("---..");
    break;
  case '9':
    append("----.");
    break;
  case 'A':
  case 'a':
    append(".-");
    break;
  case 'B':
  case 'b':
    append("-...");
    break;
  case 'C':
  case 'c':
    append("-.-.");
    break;
  case 'D':
  case 'd':
    append("-..");
    break;
  case 'E':
  case 'e':
    append(".");
    break;
  case 'F':
  case 'f':
    append("..-.");
    break;
  case 'G':
  case 'g':
    append("--.");
    break;
  case 'H':
  case 'h':
    append("....");
    break;
  case 'I':
  case 'i':
    append("..");
    break;
  case 'J':
  case 'j':
    append(".---");
    break;
  case 'K':
  case 'k':
    append("-.-");
    break;
  case 'L':
  case 'l':
    append(".-..");
    break;
  case 'M':
  case 'm':
    append("--");
    break;
  case 'N':
  case 'n':
    append("-.");
    break;
  case 'O':
  case 'o':
    append("---");
    break;
  case 'P':
  case 'p':
    append(".--.");
    break;
  case 'Q':
  case 'q':
    append("--.-");
    break;
  case 'R':
  case 'r':
    append(".-.");
    break;
  case 'S':
  case 's':
    append("...");
    break;
  case 'T':
  case 't':
    append("-");
    break;
  case 'U':
  case 'u':
    append("..-");
    break;
  case 'V':
  case 'v':
    append("...-");
    break;
  case 'W':
  case 'w':
    append(".--");
    break;
  case 'X':
  case 'x':
    append("-..-");
    break;
  case 'Y':
  case 'y':
    append("-.--");
    break;
  case 'Z':
  case 'z':
    append("--..");
    break;
  default:
    append(" ");
    break;
  };
};

bool morse::process() {
  if(millis() < next_event)
    return true;
  // force dot space after every signal
  if(out_state == true) {
    if(outPin != 0)
      digitalWrite(outPin, LOW);
    else
      _space();
    out_state = false;
    next_event = millis() + dot;
  } else {
    if(_tail == _head) {
      return false;
    }
    if(verbose) Serial.write(_buffer[_tail]);
    switch(_buffer[_tail++])    {
    case ' ':
      next_event = millis() + 9 * dot;
      if(outPin != 0)
        digitalWrite(outPin, LOW);
      else
        _space();
      out_state = false;
      break;
    case '-':
      next_event = millis() + 3 * dot;
      if(outPin != 0)
        digitalWrite(outPin, HIGH);
      else
        _mark();
      out_state = true;
      break;
    case '.':
      next_event = millis() + dot;
      if(outPin != 0)
        digitalWrite(outPin, HIGH);
      else
        _mark();
      out_state = true;
      break;
    }
    _tail %= BUFFER_SIZE;
  }
  return true;
};
