// driveroled_fault.ino is the latest version
// driveroled_update.ino + fault feature = driveroled_fault.ino
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
// M0		M1	Microstep Resolution
// Low		Low	full step
// High		Low	Non-circular half step
// Low		High	Half step
// High		High	1/4 step
// Floating	Low	1/8 step
// Floating	High	1/16 step
// ----------------------------------------------------------
// pin 6: TRQ
// pin 12: TR1
// Adalogger pin #8 green LED (could use Neopixel)
// Adalogger pin #13 red LED (could use Neopixel)
//////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////
