////////////////////////////////////TODO///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// 1. improve UI
// - sampling hours
// - delay hours
// (maybe make the user input certain hours for a variable and run the code itself 
//  calculates how long the sampling hours and the delay hours will be)
// 2. incorporate LED and look into that
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// Steppermotor that runs for however many hours
// delay(1+770)=delay(771) milliseconds * 56000 iterations = 12 hours
// In order to run for:
// 	12 hours: delay(771) per iteration;
// 	24 hours: delay(1542) per iteration;
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
// ----------------------------------------------------------
// OLED pins:
// A: 
// B: 
// C: 
//////////////////////////////////////////////////////////////////////////////////
// VERSION 3 (no LED and tried to take our the two for loops)
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

int init_delay = 1800000; // 1800000 milliseconds = 30 minutes
int i;

for (i=0; i<init_delay/1000; i++) {
  delay(500);
  delay(500);
}

digitalWrite(5, LOW);
//digitalWrite(5, HIGH);

while (int counter <= 56000) {
  // make current 100%
  digitalWrite(6, LOW);
  digitalWrite(12, LOW);
  // step once
  digitalWrite(9, HIGH);
  delay(1);
  // make current 25%
  digitalWrite(6, HIGH);
  digitalWrite(12, HIGH);
  // delay
  digitalWrite(9, LOW);
  delay(774);
  counter++;
}


}

void loop() {

}
