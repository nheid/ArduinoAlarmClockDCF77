ArduinoAlarmClockDCF77
======================

a 7 segment radio controlled alarm clock based on arduino

work in progress.

thanks to http://tronixstuff.com/tutorials/ for the great tutorials.

hardware based on:
ELV
68-10 56 97	I2C-4-Digit LED Display I2C-4DLED, Komplettbausatz ohne Frontplatte
68-09 16 10	DCF-Empfangsmodul DCF-2

buttons from left to right -> 1 2 3 4

currenlty has two modes.

time mode:
button 1 - disables/enables display
button 4 - switches to alarm mode

alarm mode (to set alarm time):
button 1 - switch back to time mode
button 2 - add one hour to alarm time
button 3 - add one minute to alarm time
button 4 - enable/disable alarm ( a dot between hour and minute shows if it's on)

wiring:
connect dcf signal to pin 2
connect buzzer to pin 9
