// Minnie Yoo, 4/9/19
// driveroled.ino
// This is the integration of OLED (oledworks3.ino) and Stepperdriver (simple.ino) files
//////////////////////////////////////////TODO///////////////////////////////////////////
//
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
// pin 15: direction pin
// pin 18: TRQ
// pin 8: green LED pin
// pin 16: step pin
// pin 19: TR1
// pin 13: red LED pin
// pin 23: M1
// pin 9: buttonA
// pin 6: buttonB
// pin 5: buttonC
// pin 22: M0
// pin 20: SDA
// pin 21: SCL
// pin 14: FLT
// pin 17: SLP
// pin 24: EN
///////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

  #define buttonA 9
  #define buttonB 6
  #define buttonC 5

// variables for counters
int countA = 0;
int countB = 0;
int countC = 0;
int firstA = 0; // countA will be stored in here so countA can be used again
int firstB = 0; // countB will be stored in here so countB can be used again
int loopCount = 0; // count how many iterations during the loop

int buttonStateA = 0;
int buttonStateB = 0;
int buttonStateC = 0;
int lastButtonStateA = 0;
int lastButtonStateB = 0;
int lastButtonStateC = 0;

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

void homing(int steps) {
  // go back however many steps it has taken so far
  digitalWrite(15, HIGH); // opposite direction
  for (int i=0; i<steps; i++) {
    digitalWrite(16, HIGH);
    delay(10);
    digitalWrite(16, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  // initialize the button pin as an input
  //////////// OLED /////////////
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);

  pinMode(15, OUTPUT); // direction
  digitalWrite(15, LOW);
  pinMode(23, OUTPUT); // M1
  pinMode(22, OUTPUT); // M0
  digitalWrite(23, LOW);
  digitalWrite(22, LOW);
  pinMode(17, OUTPUT); // sleep
  digitalWrite(17, HIGH);
  pinMode(14, INPUT); // fault
  
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
      //Serial.println("black");
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
      if (countC == 0) {
      // when countC is 0
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
      if (countC == 1) { // when countC is 1
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("All ready to go!");
      display.print("duration: ");
      printTime(firstA, firstB);
      display.print("delay: ");
      printTime(countA, countB);
      display.display();
      delay(5000);
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Press C to start");
      display.display();
      }
      if (countC == 2) { // when countC is 2
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Sampler starting...");
        display.display();

        /////// STEPPERMOTOR COMES IN HERE ///////
        Serial.println("steppermotor starting");
        // initial delay = countA hours + countB minutes --> convert them to seconds = countA*
        int init_delay = 60*(countA*60 + countB); // initial delay in seconds
        int motor_dur = 60*(firstA*60 + firstB); // motor duration in seconds
        int delayi = (motor_dur/7)-1;
        int i = 0;
       // pinMode(8, OUTPUT);
       // digitalWrite(8, HIGH);
        // already initialized M0 and M1 in setup
        //digitalWrite(22, LOW);
        //digitalWrite(23, LOW);
        
        // delay adds up to 10 seconds for each iteration 
        for (i=0; i<init_delay/10; i++) {
          //digitalWrite(8, HIGH);
          delay(500); // green LED for half a second
          //digitalWrite(8,LOW);
          delay(9500); // green LED off for 9.5 seconds
        }
        //digitalWrite(5, LOW);
        //digitalWrite(5, HIGH);
        Serial.println("delay over");
        Serial.println(buttonStateC);
       // buttonStateC = HIGH;
       // Serial.println(buttonStateC);

        // delay should change 
        // duration of the motor
        for (i=0; i<7000; i++) {
          // fault pin
          if (digitalRead(14) == LOW) {
            digitalWrite(13, HIGH); // red LED on
            display.clearDisplay();
            display.setCursor(0,0);
            display.print("FAULT");
            display.display();
          }
          // make current 100%
          digitalWrite(18, LOW);
          digitalWrite(19, LOW);
          // step once
          Serial.print("Step");
          digitalWrite(16, HIGH);
          delay(10);
          digitalWrite(16, LOW);
          // make current 25%
          digitalWrite(18, HIGH);
          digitalWrite(19, HIGH);
          // delay
          delay(delayi);
          loopCount++;
          //Serial.print(buttonStateC); // 1
          Serial.print(digitalRead(buttonC)); // 1
          if (loopCount > 20) {
         // if (digitalRead(buttonC) != buttonStateC) {
            if (digitalRead(buttonC) == LOW) {
              Serial.println(digitalRead(buttonC));
              break;
            }
         // }
          }

          
        } // loop done

        // next menu
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Home?");
        display.print("Press C");
        display.display();
        
      } // end of countC == 2

      if (countC == 3) {
        Serial.print(loopCount);
        homing(loopCount);
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
