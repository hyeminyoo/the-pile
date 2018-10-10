// Steppermotor that runs for 12 hours
// delay(1+774)=delay(775) milliseconds * 56000 iterations = 12 hours
// In order to run for:
// 	12 hours: delay(774);
// 	24 hours: delay(1547);
// pin 8: Direction relative to the front of motor (Low is counter-clockwise, High is clockwise)
// pin 9: Step (Low is don't step, High is step)

void setup() {

int i;

delay(1800000); //1800000 milliseconds = 30 minutes

digitalWrite(8, LOW);
//digitalWrite(8, HIGH);

for (i=0; i<30000; i++) {
  digitalWrite(9, HIGH);
  delay(1);
  digitalWrite(9,LOW);
  delay(774);
}

// Second for loop is because ~ 36000 iterations maxes out the arduino's memory

for (i=0; i<26000; i++) {
  digitalWrite(9, HIGH); //Step
  delay(1);
  digitalWrite(9,LOW);
  delay(774);

}

}

void loop() {


}
