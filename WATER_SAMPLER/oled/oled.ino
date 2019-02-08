//#include <Bounce2.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <oled-wing-adafruit.h>

//SYSTEM_THREAD(ENABLED);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
//OledWingAdafruit display2;

// pin 9: A
// pin 6: B
// pin 5: C
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

int i=0;
int j=0;
int k=0;

void setup() {
Serial.begin(9600);
Serial.println("OLED FeatherWing test");
display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

Serial.println("OLED begun");
display.display();
delay(1000);

display.clearDisplay();
display.display();

Serial.println("IO test");
pinMode(BUTTON_A, INPUT_PULLUP);
pinMode(BUTTON_B, INPUT_PULLUP);
pinMode(BUTTON_C, INPUT_PULLUP);

display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Welcome to WATERSAMPLER");
display.setCursor(0,0);
display.display();
delay(5000);
display.clearDisplay();

display.print("Enter Input: ");
display.display();
//delay(5000);
//display.setCursor(0,0);
//display.display();
//display.clearDisplay();

/*
if(!digitalRead(BUTTON_A)) {
  display.print("You've pressed button A");
  delay(10);
  yield();
  display.display();
}

if(!digitalRead(BUTTON_B)) {
  display.print("You've pressed button B");
  display.display();
  delay(3000);
}
if(!digitalRead(BUTTON_C)) {
  display.print("You've pressed button C");
  display.display();
  delay(3000);
}
*/

} // end of setup()

void loop() {
  /*
if (display2.pressedA()) {
  display.print("pressed A");
  display.display();
  delay(1000);
  yield();
  i++;
  display.print("i is ");
  display.print(i);
}
if (display2.pressedB()) {
  display.print("pressed B");
  display.display();
  delay(1000);
  yield();
  j++;
  display.print("j is ");
  display.print(j);
}
if (display2.pressedC()) {
  display.print("pressed C");
  display.display();
  delay(1000);
  yield();
  k++;
  display.print("k is ");
  display.print(k);
}
*/
if(!digitalRead(BUTTON_A)) display.print("pressed A");
if(!digitalRead(BUTTON_B)) display.print("pressed B");
if(!digitalRead(BUTTON_C)) display.print("pressed C");
delay(10);
yield();
display.display();

}
