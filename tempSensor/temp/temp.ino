// arduino code 5/8/18
// trying to get this to print
#include <Wire.h>
#include "TSYS01.h"

TSYS01 sensor;

void setup() {
  while (!Serial)
  Serial.begin(9600);
  Serial.println("Starting");
  Wire.begin();
  sensor.init();
 
}

void loop() {
  sensor.read();

  Serial.print("Temperature: ");
  Serial.print(sensor.temperature());
  Serial.println(" deg C");

  Serial.println("---");

  delay(1000);
}

