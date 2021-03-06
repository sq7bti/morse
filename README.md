Morse
=====

- [ ] Rationality.

The Morse code transmitter library that can be used without the need to lock CPU during execution. It must be accepting characters (strings) to be transmitted, kept in the FIFO buffer and transmitted with configurable CPM setting.

- [ ] Implementation.

Provided transmission speed is interpreted as the length of dot. Ring buffer of size 256 characters provides FIFO buffering and allows to execution without the need to explicitly produce transmitted signals with timing dependency in the main code. The required is execution of process method that takes care of fitting gaps between characters and words according to the telegraphy rules.

- [ ] Usage.

Define two helper functions:
- mark
- space
Each should produce appropriate states on the output pins, corresponding to the active and non-active state of Morse transmitted. Do not confuse it with dot and dash.
For example:

```arduino
void mark() {
  digitalWrite(OUTPUT_PIN, 1);
}
```
```arduino
void space() {
  digitalWrite(OUTPUT_PIN, 0);
}
```
Configure Morse object with pointers to mark's and space's helper functions. Each is called at the beginning of each dot and dash accordingly to raise and lower the output state. It might also produce square wave if the analogWrite (PWMWrite) is called instead of digitalWrite.
