//////////////////////////////////////////////////////////////
// SCL: blue
// SDA: yellow
// log: temperature sensor, pressure sensor, real time clock
//////////////////////////////////////////////////////////////
#include <Wire.h>
#include "RTClib.h"
#include "TSYS01.h"
#include "MS5837.h"

// for datalogger in the flash chip
#define FLASH_SS SS1 // Flash chip SS pin
#define FLASH_SPI_PORT SPI1 // What SPI port is Flash on?

#define FLASH_TYPE SPIFLASHTYPE_W25Q16BV

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>

// objects
MS5837 pressuresensor;
TSYS01 tempsensor;
RTC_DS3231 rtc;

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT); // Use hardware SPI
Adafruit_M0_Express_CircuitPython cirpy_fs(flash); // create Adafruit_M0_Express_CircuitPython object
                                                  // acts like an SD card library
// make daysofweek array
char daysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {

  #ifndef ESP8266 // this is for the rtc
  #endif

  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting");
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // setting explicit time
    // ex) January 21, 2014 at 3am would be rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  tempsensor.init();
  pressuresensor.init();
  pressuresensor.setFluidDensity(997); //kg/m^3 (997 freshwater, 1029 for seawater)

  // Initialize flash library and check its chip ID.
  if (!flash.begin(FLASH_TYPE)) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }
  Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.GetJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!cirpy_fs.begin()) {
    Serial.println("Failed to mount filesystem!");
    Serial.println("Was CircuitPython loaded on the board first to create the filesystem?");
    while(1);
  }
  Serial.println("Mounted filesystem!");

  Serial.println("Logging data ... " );  
  // Create or append to a datalog.txt file and add a new line
  // to the end of it.  CircuitPython code can later open and
  // see this file too!
}

void loop() {
  tempsensor.read();
  pressuresensor.read();
  
  float temp = tempsensor.temperature();
  float pres = pressuresensor.pressure();
  float depth = pressuresensor.depth();
  float alt = pressuresensor.altitude();
  
  File data = cirpy_fs.open("datalog.txt", FILE_WRITE);
  if (data) {
    Serial.println("Starting to write to the file...");
 
    // Write a new line to the file:
    data.println("\n");
    data.println("Start datalogging temperature, pressure, depth, and altitude");

    Serial.println("Start timestamp");

    DateTime now = rtc.now();
    data.print(daysOfWeek[now.dayOfTheWeek()]);
    data.print(" ");
    data.print(now.month(), DEC);
    data.print("/");
    data.print(now.day(), DEC);
    data.print("/");
    data.print(now.year(), DEC);
    data.print("\n");
    data.print(now.hour(), DEC);
    data.print(":");
    data.print(now.minute(), DEC);
    data.print(":");
    data.println(now.second(), DEC);
 
    Serial.println("End timestamp");
    Serial.println("Start actual data");
    
    data.print("Temperature: ");
    data.print(temp);
    data.println(" deg C");

    data.print("Pressure: ");
    data.print(pres);
    data.println(" mbar");

    data.print("Depth: ");
    data.print(depth);
    data.println(" m");
    
    data.print("Altitude: ");
    data.print(alt);
    data.println(" m above mean sea level");

    data.flush();
    data.close();
 
    // See the other fatfs examples like fatfs_full_usage and fatfs_datalogging
    // for more examples of interacting with files.
    Serial.println("Recorded data in datalog.txt on the disk");
  }
  else {
    Serial.println("Error, failed to open data file for writing!");
  }

  Serial.println("Finished!");

  delay(5000); // 5 seconds delay
} // END LOOP

