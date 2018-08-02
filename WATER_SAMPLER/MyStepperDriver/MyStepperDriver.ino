#include <Stepper.h>
#define STEPS 200 // 200 steps per rev
Stepper stepper(STEPS, 8, 9);

void setup() {
int i;
stepper.setSpeed(120); // speed is 120 rpm
delay(1000); // delay
//stepper.step(200);
delay(500); // pause
for (i=0; i<14000; i++){
    stepper.step(1);
    delay(6000); // delay for 6 seconds
}
digitalWrite(8,LOW);
digitalWrite(9,LOW);
}


void loop() {

  
}

