#include <Energia.h>
#include "morseclass.h"

uint8_t k = 0;
morse telegraph;
char c;

void mark(void) {
  analogWrite(RED_LED, 10);
}

void space(void) {
  analogWrite(RED_LED, 0);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("morse encoder.");
  // put your setup code here, to run once:
  telegraph.begin(mark, space, 150, false);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    c = Serial.read();
    telegraph.send(c);
    Serial.write(c);
  }
  telegraph.process();
}
