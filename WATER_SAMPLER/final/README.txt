- Version1 of sucessful UI OLED is oledworks.ino
- Version2 of UI OLED is oledworks2.ino

- oledworks.ino (Version1)
//// EDITS FOR VERSION1 MADE IN VERSION2 SO YOU SHOULD REFER TO VERSION2 ////
    - This version starts with Adafruit splash screen
    - Moves onto "Welcome to WATERSAMPLER" screen
    - Then says
	- "Enter Input:"
	- "Press A for hours"
	- "Press B for minutes"
	- "Press C if finished"
    - When A is pressed, it increments the number of hours
	- is saved in the counter
    - When B is pressed, it increments the number of minutes
	- is saved in the counter
    - When C is pressed, it shows how many hours and minutes it will work for
	- Then the user has to input delay before the Sampler works- Version2

- oledworks2.ino (Version2)
    - This version is written on top of Version1
    - I am trying to implement a next page that comes after the user presses 
	- It will ask for buffer time in the beginning
	- A for hours and B for minutes just like Version1C
    - When C is pressed, it shows how many hours and minutes it will work for
	- Then the user has to input delay(buffer) before the Sampler works

- oledworks3.ino (Version3)
    - This version just adds print function to version 2
    -
