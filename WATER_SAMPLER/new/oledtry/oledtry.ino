#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#define OLED_RESET 3
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
// this constant won't change:
const int buttonPin = 9;
// Variables will change: int buttonPushCounter = 0; int buttonState = 0;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
void setup() { 
  Serial.begin(9600);
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT_PULLUP);
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
 
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
 
  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Connected");
  display.display();
  delay(2000);
  display.clearDisplay();
 
  
}


int whichbutton = 0;
 
void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
 
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      // if the current state is LOW then the button was pressed
      buttonPushCounter++;
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    }
  }
 
 
  //A button position - display today's high temperature
  if ((buttonPushCounter % 3 == 0) && (buttonPushCounter !=0)) {
     // display.clearDisplay();
      display.setCursor(0,16);
      display.println("A");
      display.display();
  }
 
  //A button position - David Bowie quote
  if (buttonPushCounter % 3 == 1) {
    //display.clearDisplay();
    display.setCursor(0,0);
    display.println("B");
    display.display();
  }
 
  //C button position - nametag
  if (buttonPushCounter % 3 == 2) {
    //display.clearDisplay();
    display.setCursor(0,0);
    display.println("C");
    display.display();
  }
 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}


//}
