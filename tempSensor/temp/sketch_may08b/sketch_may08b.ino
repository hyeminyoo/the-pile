#include <Wire.h>
#include "TSYS01.h"

TSYS01 sensor;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  Wire.begin();
  sensor.init();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
