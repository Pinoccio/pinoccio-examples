Community member François designed a [Capacitive Touch backpack](http://support.pinocc.io/hc/en-us/articles/202311914-Capacitive-Touch) for us, and put the template on OSHPark so you can order your own! [Here's our full tutorial](http://www.hackster.io/pinoccio/pinoccio-touch-sensor), from start to finish, including soldering components to the backpack and this bootstrap.

Copy the CapTouchPinoccio folder to your /Arduino folder, where you keep your sketches. Open it in the Arduino IDE and upload it. (This takes a little longer than a regular Arduino sketch—just be patient!)

###Library
This uses Paul Badger's [Capacitive Sensor library](http://playground.arduino.cc/Main/CapacitiveSensor), which you'll need to install first. Download it and add it to your /Arduino/libraries folder, and restart the Arduino IDE if you had it open.

###ScoutScript Examples

Enter these functions in the Arduino IDE, or in [Pinoccio HQ](http://hq.pinocc.io), to see some cool stuff happen.

####P-I-N-O
```
function on.cp.high { led.red }; 
function on.cp.low { led.off };
function on.ci.high { led.green }; 
function on.ci.low { led.off };
function on.cn.high { led.blue }; 
function on.cn.low { led.off };
function on.co.high { led.yellow }; 
function on.co.low { led.off };
```

When you poke the "P" touch pad, the torch LED should turn red, and go off when you release it.
I: same thing, but green.
N: same thing, blue.
O: same thing, yellow.

####Demo setup for events
```
function ping { command.all("led.torch",500); print "ping!"; };
function on.cp.high { ping; };
```

Poke the "P" touch pad to make each Scout in your troop blink its torch LED. Good for explaining to people how the network functions!  
I also recommend having a [button](http://www.hackster.io/erictj/pinoccio-button-press) on another Scout, with a similar command, so you can demonstrate that **any** scout can control all the others.  
You could also combine this with a [command.scout()](https://docs.pinocc.io/scoutcommands.html#command-scout) call, to show off how each Scout can be addressed individually.

[See it in action!](https://vine.co/u/1049166214951567360)