#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

volatile int button_A_state = HIGH;
volatile int button_B_state = HIGH;
volatile int button_C_state = HIGH;
long debouncing_time = 250;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.display();
  delay(5000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("WELCOME TO WATERSAMPLER");
  display.setCursor(0,0);
  display.display();
  delay(3000);
  display.clearDisplay();

  display.print("Enter Input: ");
  display.display();
  
}

void loop() {
  int BUTTON_A_state = digitalRead(BUTTON_A);
  int BUTTON_B_state = digitalRead(BUTTON_B);
  int BUTTON_C_state = digitalRead(BUTTON_C);
  
}

