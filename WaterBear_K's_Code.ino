

//////////////////////////////////////////////////////////////
// SCL: blue
// SDA: yellow
// log: temperature sensor, pressure sensor, real time clock
//////////////////////////////////////////////////////////////
#include <Wire.h>
#include <RTClib.h>
#include <TSYS01.h>
#include <MS5837.h>
#include <KellerLD.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//NeoPixel Pin
#define PIN            8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// for datalogger in the flash chip
#define FLASH_SS SS1 // Flash chip SS pin
#define FLASH_SPI_PORT SPI1 // What SPI port is Flash on?

#define FLASH_TYPE SPIFLASHTYPE_W25Q16BV

#define VBATPIN A7

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>

// objects
MS5837 pressuresensor;
TSYS01 tempsensor;
RTC_DS3231 rtc;
KellerLD sensor;

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT); // Use hardware SPI
Adafruit_M0_Express_CircuitPython cirpy_fs(flash); // create Adafruit_M0_Express_CircuitPython object
                                                  // acts like an SD card library
// make daysofweek array
char daysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.

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
  pressuresensor.init(); //MS5837
  sensor.init(); //Keller LD
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
  pressuresensor.setFluidDensity(997); //kg/m^3 (997 freshwater, 1029 for seawater)

    if (sensor.isInitialized()) {
    Serial.println("Keller pressure sensor connected.");
  } else {
    Serial.println("Keller pressure sensor not connected.");
  }

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
  sensor.read();
  
  float temp = tempsensor.temperature();
  float pres = pressuresensor.pressure();
  float depth = pressuresensor.depth();
  float alt = pressuresensor.altitude();

  float pres2 = sensor.pressure();
  float depth2 = sensor.depth();
  float alt2 = sensor.altitude();

  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  
  File data = cirpy_fs.open("datalog.txt", FILE_WRITE);
  if (data) {
    Serial.println("Starting to write to the file...");
 
    // Write a new line to the file:
    // data.println("\n");
    // data.println("Start datalogging temperature, pressure, depth, and altitude");

    Serial.println("Start timestamp");

    DateTime now = rtc.now();
    // data.print(daysOfWeek[now.dayOfTheWeek()]);
    // data.print(" ");
    data.print(now.month(), DEC);
    data.print("/");
    data.print(now.day(), DEC);
    data.print("/");
    data.print(now.year(), DEC);
    data.print(" ");
    data.print(now.hour(), DEC);
    data.print(":");
    data.print(now.minute(), DEC);
    data.print(":");
    data.println(now.second(), DEC);

    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);

    Serial.print("VBat: " ); 
    Serial.println(measuredvbat);
 
    Serial.println("End timestamp");
    Serial.println("Start actual data");
    
    data.print("Temp: ");
    data.println(temp);
    //data.println(" deg C");

    Serial.print("Temp: ");
    Serial.println(temp);
    //Serial.println(" mbar");

    pressuresensor.init();
    
    data.print("Press: ");
    data.println(pres);
    //data.println(" mbar");

    Serial.print("Press: ");
    Serial.println(pres);
    //Serial.println(" mbar");

    data.print("Press2: ");
    data.println(pres2);
    //data.println(" mbar");

    Serial.print("Press2: ");
    Serial.println(pres2);
    //data.println(" mbar");

    // data.print("Depth: ");
    // data.print(depth2);
    // data.println(" m");
    
    // data.print("Altitude: ");
    // data.print(alt2);
    // data.println(" m above mean sea level");

   // data.print("VBat: " ); 
   // data.println(measuredvbat);

    data.flush();
    data.close();
 
    // See the other fatfs examples like fatfs_full_usage and fatfs_datalogging
    // for more examples of interacting with files.
    
    Serial.println("Recorded data in datalog.txt on the disk");
      
      for(int i=0;i<NUMPIXELS;i++){

      //pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(500); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
       }
       

  delay(9000); // 9 second delay
  }    
  
  else {
    Serial.println("Error, failed to open data file for writing!");
    for(int i=0;i<NUMPIXELS;i++){
     pixels.setPixelColor(i, pixels.Color(150,0,0)); // Moderately bright red color.
      pixels.show(); // This sends the updated pixel color to the hardware.
  }}  
  
  //Serial.println("Finished!");
  
  } // END LOOP
