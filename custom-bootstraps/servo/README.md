Here's the Bootstrap sketch I use on Scouts that are attached to micro-servos. This is a very slightly customized version of Jacob Rosenthal's [servo bootstrap for Pinoccio](https://github.com/jacobrosenthal/TimerThree/blob/master/examples/Pinoccio/Pinoccio.ino).

All I've done is tweak a couple of things that sometimes prevent me from uploading sketches to my Scouts (I'm still looking into why): I changed  
`Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);`  
to simply  
`Scout.setup();`  
...and bundled all of these with the "Version.h" file that Arduino sometimes can't find.

Copy this WeatherServo folder to your /Arduino folder, where you keep your sketches. Open it in the Arduino IDE and upload it. (This takes a little longer than a regular Arduino sketch—just be patient!)

###Library
As noted by Jacob, this is is based on PJRC's [TimerThree](http://www.pjrc.com/teensy/td_libs_TimerOne.html) library, which you'll need to install first. Download it and add it to your /Arduino/libraries folder, and restart the Arduino IDE if you had it open.

###ScoutScript Examples

Enter these functions in the Arduino IDE, or in [Pinoccio HQ](http://hq.pinocc.io), to see some cool stuff happen.

In order for these to work, you'll first need to initialize the timer that controls the servo:
`timer3.initialize(20000);`

I recommend putting this in the startup function, along with any other setup functions you want to run, so that it will run every time the Scout boots up:
`function startup { timer3.initialize(20000); }`

####Basic positioning

`function tt { timer3.pwm(3, arg(1)); };`

This is the first function I usually put on a servo-ified Scout. It helps me find the positional range and center of the servo, which you want to do before fully attaching the servo head. For micro-servos, start with a range of about 40-110, and see how much lower or higher you can get before it starts making noise. (Not very much noise! Hold it close to your ear.) (It's also possible you could just, y'know, check the documentation...)

####Weather gauge
This is from a weather dial project I was working on with Sally, a while back. I made the code very adaptable, so that you can easily plug in values for any project that uses a servo as a gauge. We'll probably pick it up again at some point soon, but here are my notes for now, in case you want to try something similar.

```
Sally has drawn a weather dial with five states:
0. Snow
1. Rain
2. Cloudy
3. Partly cloudy
4. Clear & sunny

Here are the variables I'm working with:
CONFIG (fairly static)
l = servo lower limit = 40
h = servo max limit = 120
o = number of weather options = 5

CALCULATED FROM CONFIG (equally static)
r = servo range = h-l = 80
i = increment per weather option = r / (o-1) = 20

MODIFIED WHILE RUNNING
w = current weather state (per numbered list above)
p = servo position = iw + l

ALL THE FORMULAS (I MEAN FORMULAE) AGAIN
r = h - l 				// the servo's range is a positive number
i = r/o					// the servo moves in increments determined by the range divided by the number of possible states
p = iw + l				// the servo position is set by starting from the lower limit and adding the number of increments corresponding to the current weather state

If you know all of the CONFIG values, you can simply use those for l and i, plus a starting value for w (0) and the function for p. If you're going to be plugging in different servos (or changing dials), you might want to leave them as formulas and edit the startup function whenever you switch something out, then reboot the Scout.

FINAL SET OF THINGS THAT GO ON THE SCOUT
function startup { timer3.initialize(20000); l = 40; i = 20; w = 0; pos; }; 
function pos { p = (i*w) + l; print p; timer3.pwm(3,p); }; 
timer3.initialize(20000);														// OR reboot the Scout (since this is in the startup function)
run pos,60000																	// runs once per minute
```