These functions will take the temperature of your Scout and use three different methods to turn it into a visual display via the [torch LED](http://support.pinocc.io/hc/en-us/articles/200823430-LEDs#torch). They should help you get a feel for [ScoutScript](http://support.pinocc.io/hc/en-us/articles/200250539-ScoutScript-Overview).

#### if/else/else - Three Steps (Raul Sampedro)

Raul kicked off [this thread](https://pinocc.io/forum#!/your-projects:playing-with-leds) with an example that turns your Scout's Torch LED blue, green, or red, based on whether it is cold, warm, or hot.  
I've tweaked it very slightly to use the current `temperature.c` (Celsius temperature) variable.

```function readtemp {if (temperature.c < 21 ) {led.blue;} else {if (temperature.c > 30) {led.red;} else {led.green;} }; 
run readtemp, 1000```

With this function, everything below 21ºC shows blue, everything above 30ºC turns the LED red, and everything in between is green. A great way to approach "threshold" situations where you need to easily distinguish a couple of different states.

#### Switch function - Eight Steps (John Mann)

John chimed in on the thread with an eight-step function that takes advantage of [switch functions](https://github.com/billroy/bitlash/wiki/conditionals#switch-expr-stmt0-stmt1--stmtn). Again, I've simply modified it to use `temperature.c`:

`function colortemp { switch (temperature.c - 14) { led.blink(0, 0, 25, 500); led.blink(0, 12, 25, 500); led.blink(0, 25, 25, 500); led.blink(0, 25, 12, 500); led.blink(0, 25, 0, 500); led.blink(12, 25, 0, 500); led.blink(25, 25, 0, 500); led.blink(25, 12, 0, 500); led.blink(25, 0, 0, 500); } };`

Says John: "Temperatures 14 C and below display as blue and then each step up from there moves the color towards green and then red at 22 C and above. I put this in a loop and it will update continously":

`run colortemp, 500`

This is an easy way to work with multiple discrete states, if you have more than a few possibilities, and it easily expands to cover more cases – just tack them onto the end of your function.

#### Direct mathematical function - Continuous (Alex)

I wanted to throw in a third way of turning data into displays. Here's one that turns the temperature reading (Fahrenheit, this time) and transforms it into a color value that roughly represents the temperature curve:

`function templed { u = (temperature.f + 15)*2; d = 250-u; if (u < 48) {led.setrgb(0,u,d);} else {led.setrgb(u,d,0);}; }`

Here's the logic:  
The LED takes R, G, and B values from 0 to 255. 0-250 is a very easy scale to work with.  
I chose a 125-degree range of values that one might reasonably encounter, in all but the most intense seasonal flux: -15 to 110ºF.  
(Yes, laugh, Canadians, laugh...)  
Adding 15 to the temperature reading, I obtain a 0-125 scale.  
Multiplying this by 2, I scale the value to 0-250, which is close enough to our LED brightness range for each color.  

The LED is always ramping one color up (via the `u` brightness variable) and one down (with `d`), producing a unique color for each temperature in the range. The third color stays at 0.  
Now, the midpoint of our range is about 48ºF.  
So, for everything below that, I tie the blue to "down" and green to "up". Blue starts at full brightness and slowly dims; green comes up from 0.  
For everything above 48º, green fades down and red comes up.  
The end result: the range starts with full-brightness blue at -15ºF, and goes through cyan to green (at 48ºF, a pretty comfortable temperature), then through yellow and orange to full-on emergency red at 110. (Laugh, Texans, laugh...)  

This approach takes a bit more calculation to set up, but if you're tying your display to a mathematical value, it does the thinking for you and gives a nice smooth curve.