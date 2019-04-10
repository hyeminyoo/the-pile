// THIS IS SUCCESSFUL VERSION1 OF OLED USER INTERFACE
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

  #define buttonA  9
  #define buttonB  6
  #define buttonC  5

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
  display.print("Welcome to WATERSAMPLER");
  display.setCursor(0,0);
  display.display();
  delay(2000);
  display.clearDisplay();
 
  display.println("Enter Input: ");
  display.println("Press A for hours");
  display.println("Press B for minutes");
  display.print("Press C if finished");
  display.setTextSize(1);
  display.display();
  
}


//int whichbutton = 0;
 
void loop() {
  if ((buttonPushCounterA == 0) && (buttonPushCounterB == 0) && (buttonPushCounterC == 0)) {
    display.clearDisplay();
  }
  // read the pushbutton input pin:
  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
  buttonStateC = digitalRead(buttonC);
  //display.clearDisplay();
  // compare the buttonState to its previous state
  if (buttonStateA != lastButtonStateA) {
    // if the state has changed, increment the counter
    if (buttonStateA == LOW) {
      // if the current state is LOW then the button was pressed
      // delete line by drawing black pixels over it
      for (int a=0; a <127; a++) {
        for (int b=0; b<=6; b++) {
          display.drawPixel(a,b,BLACK);
        }
      }
      Serial.println("black");
      //display.print(buttonPushCounterA);
      //display.print(" hours");
      // done deleting
      buttonPushCounterA++;
      Serial.print(buttonPushCounterA);
      Serial.println(" hours");
      display.setTextColor(WHITE); // set it back to white to write
      display.setCursor(0,0);
      //display.clearDisplay();
      display.print(buttonPushCounterA);
      display.print(" hours");
      display.display();
      
      
    }
  }

  if (buttonStateB != lastButtonStateB) {
    if (buttonStateB == LOW) {
      // delete line by drawing black pixel over it
      for (int c=0; c <127; c++) {
        for (int d=0; d<=10; d++) {
          display.drawPixel(c,(d+7),BLACK);
        }
      }
      Serial.println("black");
      //display.print(buttonPushCounterA);
      //display.print(" hours");
      // done deleting
      buttonPushCounterB++;
      Serial.print(buttonPushCounterB);
      Serial.println(" minutes");
      display.setTextColor(WHITE); // set text back to white to write
      display.setCursor(0,10);
      //display.clearDisplay();
      display.print(buttonPushCounterB);
      display.print(" minutes");
      display.display();
      
    }
  }

  if (buttonStateC != lastButtonStateC) {
    if (buttonStateC == LOW) {
      buttonPushCounterC++;
      Serial.print("C button: ");
      Serial.println(buttonPushCounterC);
      display.setCursor(0,0);
      //display.clearDisplay();
      display.print("C button: ");
      display.println(buttonPushCounterC);
      display.display();
      
    }
  }
 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateA = buttonStateA;
  lastButtonStateB = buttonStateB;
  lastButtonStateC = buttonStateC;
  
}

