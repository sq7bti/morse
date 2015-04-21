#ifndef __MORSE_H__
#define __MORSE_H__

#define BUFFER_SIZE 256

class morse {
public:
  void begin(uint8_t _outPin, unsigned int _cpm, bool ver);
  void begin(void (*mark)(void), void (*space)(void), unsigned int _cpm, bool ver);
  void send(const char* s);
  bool process();
private:
  uint8_t outPin;
  void (*_mark)();
  void (*_space)();
  unsigned long dot;
  char _buffer[BUFFER_SIZE];
  int _head, _tail;
  bool verbose;
  unsigned long next_event;
  void append(const char *str);
};
#endif //ndef __MORSE_H__
