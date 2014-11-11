This is just a quick example to show how you can combine two Arduino/Pinoccio libraries in the same bootstrap sketch. This one combines the NeuroSky and NeoPixel custom bootstraps.

Copy this NeuroCcio folder to your /Arduino folder, where you keep your sketches. Open it in the Arduino IDE and upload it. (This takes a little longer than a regular Arduino sketch—just be patient!)

###Library
This is based on Hector's [NeoPixelStripAnimator](https://github.com/urtubia/NeoPixelStripAnimator) library for Pinoccio, which you'll need to install first. Download it and add it to your /Arduino/libraries folder, and restart the Arduino IDE if you had it open.

Do the same with [kitschpatrol's Brain library](https://github.com/kitschpatrol/Brain).

###ScoutScript Examples

Enter these functions in the Arduino IDE, or in [Pinoccio HQ](http://hq.pinocc.io), to see some cool stuff happen.

####Flash of inspiration

This causes the NeoPixel strip to flash bright white, then fade out, when you hit your target attention value. It's super distracting, but good for demos. :)  
Don't point the NeoPixels at your eyes!! They're very, very bright.

`function brainpixel { a = brain.attention; if (a < 80) { pixels.fadeout; }; };`