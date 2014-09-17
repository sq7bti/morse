#include <Energia.h>
#include "morseclass.h"

uint8_t k = 0;
morse telegraph;
char c;

void setup()
{
  Serial.begin(115200);
  Serial.println("morse encoder.");
  // put your setup code here, to run once:
  telegraph.begin(RED_LED, 100, false);
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

