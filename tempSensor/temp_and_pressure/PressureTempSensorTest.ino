#include <Wire.h>
#include "TSYS01.h"
#include "MS5837.h"

MS5837 pressuresensor;
TSYS01 tempsensor;

void setup() {

  Serial.begin(9600);
  
  Serial.println("Starting");
  
  Wire.begin();

  tempsensor.init();
  pressuresensor.init();
  pressuresensor.setFluidDensity(997); //kg/m^3 (997 freshwater, 1029 for seawater)

}

void loop() {

  tempsensor.read();
 
  Serial.print("Temperature1: ");
  Serial.print(tempsensor.temperature()); 
  Serial.println(" deg C");
   
  Serial.println("---");

  delay(1000);

  pressuresensor.read();

  Serial.print("Pressure: "); 
  Serial.print(pressuresensor.pressure()); 
  Serial.println(" mbar");
  
  Serial.print("Temperature2: "); 
  Serial.print(pressuresensor.temperature()); 
  Serial.println(" deg C");
  
  Serial.print("Depth: "); 
  Serial.print(pressuresensor.depth()); 
  Serial.println(" m");
  
  Serial.print("Altitude: "); 
  Serial.print(pressuresensor.altitude()); 
  Serial.println(" m above mean sea level");
}

