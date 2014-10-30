Enter these two functions on one of your Scouts, and switch on the whole troop!
```
function rotate { r = random(255); g = random(255); b = random(255); color; };
function color { led.setrgb(r,g,b); command.scout(11, "led.sethex", "`led.gethex`") }
```

Here, we're using the `random` function to pick a number from 0 to 255, which is the range of each color on the Scouts' torch LEDs. For example, (0,127,255) means that red is off, green is halfway on, and blue is fully on. The result is a slightly turquoise blue color.

Next, we call the `color` function from that one. This will set the torch LED according to those randomly generated numbers, to create a completely unpredictable color. (Fun fact: `random` uses noise from the RF antenna to create a truly random result!)  
Then, we run `led.gethex` on this Scout, and feed the result as an argument into an led.sethex command sent to all the other Scouts.

The last thing we want to do is set this to happen once per second, so you get an ever-changing, coordinated light show:

`run rotate,1000`

Sit back and enjoy!
