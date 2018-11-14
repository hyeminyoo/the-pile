# the-pile: Project WaterBear and Project WaterSampler
 by: Kyle Neumann, Minnie Yoo, Danny La

## Project WaterBear
### source code:

PressureTempSensorTest.ino 
[PressureTempSensorTest.ino](https://github.com/hyeminyoo/the-pile/blob/master/temp_and_pressure/PressureTempSensorTest/PressureTempSensorTest.ino)


### implemented:
```
- temperature sensor TSYS01
- pressure sensor MS5837
- real time clock RTC_DS3231
```
### How to access datalogging file for Featherboot:
1. Implemented code is in PressureTempSensorTest.ino under temp_and_pressure folder
2. Upload the file while connected to featherboot_m0_express board
3. Check serial monitor (115200 serial baud) to see if the data has been logged onto CIRCUITPY
4. Then, press the reset button on the board twice and “FEATHERBOOT” is going to pop up as one of the devices
5. Find adafruit-circuitpython-feather_m0_express-2.3.1.uf2 file (also in this repo) and drag the file into the FEATHERBOOT disk
6. Then, a new device called CIRCUITPY (or it could be called NO NAME like my mac LOL) is going to appear after FEATHERBOOT disappears
7. click on the “datalog.txt” file and scroll all the way down to find the recent data!


## Project WaterSampler
  
### source code:
[simple.ino](https://github.com/hyeminyoo/the-pile/blob/master/WATER_SAMPLER/simple/simple.ino)

### description:
- water sampler that works for 24 hours
- Current is HIGH 100% until the step, and once it steps, it turns LOW 50%, and it goes back to HIGH and repeats

### implemented:
```
- LED
- current ramping
```
