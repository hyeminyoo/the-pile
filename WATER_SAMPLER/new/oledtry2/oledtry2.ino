#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#define OLED_RESET 3
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
// this constant won't change:
  #define buttonA  9
  #define buttonB  6
  #define buttonC  5

// Variables will change: int buttonPushCounter = 0; int buttonState = 0;
int buttonPushCounterA = 0;
int buttonPushCounterB = 0;
int buttonPushCounterC = 0;
int buttonStateA = 0;
int buttonStateB = 0;
int buttonStateC = 0;
int lastButtonStateA = 0;
int lastButtonStateB = 0;
int lastButtonStateC = 0;

void setup() { 
  Serial.begin(9600);
  // initialize the button pin as a input:
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
 
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
  display.print("Enter");
  display.display();
  //delay(2000);
  display.clearDisplay();
 
  
}


int whichbutton = 0;
 
void loop() {
  // read the pushbutton input pin:
  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
  buttonStateC = digitalRead(buttonC);
 
  // compare the buttonState to its previous state
  if (buttonStateA != lastButtonStateA) {
    // if the state has changed, increment the counter
    if (buttonStateA == LOW) {
      // if the current state is LOW then the button was pressed
      buttonPushCounterA++;
      Serial.print("number of A button pushes:  ");
      Serial.println(buttonPushCounterA);
    }
  }

  if (buttonStateB != lastButtonStateB) {
    if (buttonStateB == LOW) {
      buttonPushCounterB++;
      Serial.print("number of B button pushes: ");
      Serial.println(buttonPushCounterB);
    }
  }

  if (buttonStateC != lastButtonStateC) {
    if (buttonStateC == LOW) {
      buttonPushCounterC++;
      Serial.print("number of C button pushes: ");
      Serial.println(buttonPushCounterC);
    }
  }
 
  //A button position - display today's high temperature
  if ((buttonPushCounterA % 3 == 0) && (buttonPushCounterA !=0)) {
     // display.clearDisplay();
      display.setCursor(0,16);
      display.println("A");
      display.display();
  }
 
  //A button position - David Bowie quote
  if (buttonPushCounterB % 3 == 1) {
    //display.clearDisplay();
    display.setCursor(0,0);
    display.println("B");
    display.display();
  }
 
  //C button position - nametag
  if (buttonPushCounterC % 3 == 2) {
    //display.clearDisplay();
    display.setCursor(0,0);
    display.println("C");
    display.display();
  }
 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateA = buttonStateA;
  lastButtonStateB = buttonStateB;
  lastButtonStateC = buttonStateC;

}


//}
