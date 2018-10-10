void setup() {

int i;

delay(1800000);

digitalWrite(8, LOW);
//digitalWrite(8, HIGH); // direction (Low is In, High is Out)

for (i=0; i<30000; i++) {
  digitalWrite(9, HIGH); //Step
  delay(1);
  digitalWrite(9,LOW);
  delay(774); ///1547 => 24hours, 774 => 12 hours
}

// Second for loop is because ~ 36000 iterations maxes out the arduino's memory

for (i=0; i<26000; i++) {
  digitalWrite(9, HIGH); //Step
  delay(1);
  digitalWrite(9,LOW);
  delay(774); ///1547 => 24hours, 774 => 12 hours

} 

}

void loop() {

  
}
