#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
 // #define buttonPin 9

// variables
//int counter = 0;
//int cur_state = 0;
//int prev_state = 0;

int counterA = 0;
int counterB = 0;
int counterC = 0;
int cur_stateA = 0;
int prev_stateA = 0;
int cur_stateB = 0;
int prev_stateB = 0;
int cur_stateC = 0;
int prev_stateC = 0;

void setup() {
  Serial.begin(9600);
 
  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
 
  Serial.println("OLED begun");
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
 
  // Clear the buffer.
  display.clearDisplay();
  display.display();
 
  Serial.println("IO test");
 
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
 // pinMode(buttonPin, INPUT_PULLUP);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Welcome to WATERSAMPLER");
  display.setCursor(0,0);
  display.display();
  delay(3000);
  display.clearDisplay();

  display.print("Enter Input: ");
  display.display();
  // text display tests
  // actually display all of the above
}
 
void loop() {
  //cur_state = digitalRead(buttonPin);
  cur_stateA = digitalRead(BUTTON_A);
  cur_stateB = digitalRead(BUTTON_B);
  cur_stateC = digitalRead(BUTTON_C);
  
  if(cur_stateA != prev_stateA) {
    if (cur_stateA == LOW) {
    counterA++;
    display.print("pushed A ");
    display.print(counterA);
    display.print(" times");
    }
  }
  if(cur_stateB != prev_stateB) {
    if (cur_stateB == LOW) {
    counterB++;
    display.print("pushed B ");
    display.print(counterB);
    display.print(" times");
    }
  }
  if(cur_stateC != prev_stateC) {
    if (cur_stateC == LOW) {
    counterC++;
    display.print("pushed C ");
    display.print(counterC);
    display.print(" times");
    }

  //if (!cur_state = 
   prev_stateA = cur_stateA;
   prev_stateB = cur_stateB;
   prev_stateC = cur_stateC;
  }
  delay(10);
  yield();
  display.display();
}
