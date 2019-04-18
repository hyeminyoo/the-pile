// THIS IS VERSION3 OLED
// version1 -> version2 -> version3
// This version just adds print function
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

  #define buttonA  16
  #define buttonB  17
  #define buttonC  18

// variables for counters
int countA = 0;
int countB = 0;
int countC = 0;
int firstA = 0; // countA will be stored in here so countA can be used again
int firstB = 0; // countB will be stored in here so countB can be used again

int buttonStateA = 0;
int buttonStateB = 0;
int buttonStateC = 0;
int lastButtonStateA = 0;
int lastButtonStateB = 0;
int lastButtonStateC = 0;

void printTime(int hr, int mins) {
  if (hr >= 0) { // can't be 0 because it passes 0 if there is none for now
    display.print(hr);
    if ((hr == 1) || (hr == 0)) {
        display.print(" hr ");
      }
    else 
        display.print(" hrs ");
  }
  
  if (mins >= 0) { // can't be 0 because it passes 0 if there is none for now
    display.print(mins);
    if ((mins == 1) || (mins == 0)) {
        display.println(" min");
      }
    else 
        display.println(" mins");
  }
}

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
 
  display.println("Enter duration: ");
  display.println("Press A for hours");
  display.println("Press B for minutes");
  display.print("Press C if finished");
  display.setTextSize(0.8);
  display.display();
  
}
 
void loop() {
  if ((countA == 0) && (countB == 0)) {
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

     
      // done deleting
      countA++;
      // this is when you want to go back to 0 for- ex) when you input wrong number
      if (countA == 25) {
        countA = 0;
      }
      Serial.print(countA);
      Serial.println(" hours");
      display.setTextColor(WHITE); // set it back to white to write
      display.setCursor(0,0);
      //display.clearDisplay();

      printTime(countA, -1);
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
      countB++;
      // this is when you want to go back to 0 for- ex) when you input wrong number
      if (countB == 60) {
        countB = 0;
      }
      Serial.print(countB);
      Serial.println(" minutes");
      display.setTextColor(WHITE); // set text back to white to write
      display.setCursor(0,10);
      //display.clearDisplay();
      printTime(-1, countB);
      display.display();
      
    }
  }

  // this is when the user is finished
  // program delay!!
  if (buttonStateC != lastButtonStateC) {
    if (buttonStateC == LOW) {
       if (countC != 0) {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("All ready to go!");
      display.print("duration: ");
      printTime(firstA, firstB);
      display.print("delay: ");
      printTime(countA, countB);
      display.display();
      
    }
      else {
      // display for user
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("working for ");
      printTime(countA, countB);
      display.display();
      delay(3500);
      
      firstA = countA;
      firstB = countB;
      // refresh countA and countB
      countA = 0;
      countB = 0;

      // buffer interface
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Enter initial delay: ");
      display.println("Press A for hours");
      display.println("Press B for minutes");
      display.print("Press C if finished");
      display.setTextSize(1);
      display.display();
      }

      countC++;
      
    }
  }
 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateA = buttonStateA;
  lastButtonStateB = buttonStateB;
  lastButtonStateC = buttonStateC;
  
}
