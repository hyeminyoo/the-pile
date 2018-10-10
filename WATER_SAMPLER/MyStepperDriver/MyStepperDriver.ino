#include <Stepper.h>
#define STEPS 200 // 200 steps per rev
Stepper stepper(STEPS, 8, 9);

void setup() {
int i;
stepper.setSpeed(120); // speed is 120 rpm
delay(10000); // delay 10 second before loop
//stepper.step(200);
//delay(500); // pause
for (i=0; i<10000; i++){ // used to be 14000 for 24 hours
    stepper.step(1);
    delay(3000); // used to be delay for 6 seconds
}
digitalWrite(8,LOW);
digitalWrite(9,LOW);
}


void loop() {

  
}

