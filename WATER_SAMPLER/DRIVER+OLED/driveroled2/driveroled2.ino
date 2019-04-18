// Minnie Yoo, 4/9/19
// driveroled.ino
// This is the integration of OLED (oledworks3.ino) and Stepperdriver (simple.ino) files
//////////////////////////////////////////TODO///////////////////////////////////////////
// 
// 2. while it is waiting (during the delay time), make green LED go off
// 3. fully integrate OLED
/////////////////////////////////////////////////////////////////////////////////////////
// Steppermotor that runs for 12 hours
// delay(1+774)=delay(775) milliseconds * 56000 iterations = 12 hours
// In order to run for:
// 	12 hours: delay(774);
// 	24 hours: delay(1547);
// pin 5: Direction (Low is in, High is out)
// 	- Direction relative to the front of motor (Low is counter-clockwise, High is clockwise)
// pin 9: Step (Low is don't step, High is step)
// ----------------------------------------------------------
// TRQ	TR1 	current
// High	High	25%
// Low	High	50%
// High	Low	75%
// Low	Low	100%
// ----------------------------------------------------------
// pin 6: TRQ
// pin 12: TR1
// Adalogger pin #8 green LED
// Adalogger pin #13 red LED
////////////////////////////////////////////////////////////////////////////////////////
// pinouts:
// pin 5: direction pin
// pin 6: TRQ
// pin 8: green LED pin
// pin 9: step pin
// pin 12: TR1
// pin 13: red LED pin
// pin 15: M1
// pin 16: buttonA
// pin 17: buttonB
// pin 18: buttonC
// pin 19: M0
// pin 20: SDA
// pin 21: SCL
///////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

  #define buttonA 16
  #define buttonB 17
  #define buttonC 18

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

int convert(int hr, int mins) {
  int milli = 60000*(hr*60+mins);
  return milli;
}

// blink out an error code with red LED
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

void setup() {
  Serial.begin(9600);
  // initialize the button pin as an input
  //////////// OLED /////////////
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // Address 0x3c for 128x32
  display.display(); // buffer splash screen
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
/*
  ////////// NOW FOR STEPPERMOTOR //////////
  //int init_delay = 1800000; // 1800000 milliseconds = 30 minutes
  int init_delay = 1000;
  int i;
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  digitalWrite(15, LOW);
  digitalWrite(19, LOW);

  for (i=0; i<init_delay/1000; i++) {
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8,LOW);
  delay(500);
  }
  digitalWrite(5, LOW);
  //digitalWrite(5, HIGH);

  for (i=0; i<30000; i++) {
    // make current 100%
    digitalWrite(6, LOW);
    digitalWrite(12, LOW);
    // step once
    digitalWrite(9, HIGH);
    delay(1);
    digitalWrite(9, LOW);
    // make current 25%
    digitalWrite(6, HIGH);
    digitalWrite(12, HIGH);
    // delay
    delay(774);
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
}

// Second for loop is needed if more than ~ 36000 iterations (maxes out the arduino's memory)
*/
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
      display.setTextSize(0.8);
      display.display();
      }

      countC++;

      if (countC == 2) {
        
      }
    }
  }
 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateA = buttonStateA;
  lastButtonStateB = buttonStateB;
  lastButtonStateC = buttonStateC;


}
