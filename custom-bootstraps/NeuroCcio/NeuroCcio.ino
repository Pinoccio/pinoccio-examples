// Eric's notes:
// You can get the signal strength, attention, and meditation values directly by 
// calling the scoutscript:  `print brain.signal`, `print brain.attention`, or 
// `print brain.meditation`.


#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>
 
#include <Brain.h>
 
#include "version.h"
 
// hook up the Neurosky to Serial 1 (RX1/TX1)
Brain brain(Serial1);
 
void setup() {
  Scout.setup();
  // Add custom setup code here
  
  Serial1.begin(9600);
  addBitlashFunction("brain.signal", (bitlash_function)signal);
  addBitlashFunction("brain.attention", (bitlash_function)attention);
  addBitlashFunction("brain.meditation", (bitlash_function)meditation);
}
 
void loop() {
  Scout.loop();
  // Add custom loop code here
  
  char buf[32];
  
  // Expect packets about once per second.
   if (brain.update()) {
    Serial.println(brain.readErrors());
    Serial.println(brain.readCSV());
    
    // signal
    snprintf(buf, sizeof(buf), "on.brain.signal(%d)", brain.readSignalQuality());
    if (findscript(buf)) {
      doCommand(buf);
    }
    // attention
    snprintf(buf, sizeof(buf), "on.brain.attention(%d)", brain.readAttention());
    if (findscript(buf)) {
      doCommand(buf);
    }
    // meditation
    snprintf(buf, sizeof(buf), "on.brain.meditation(%d)", brain.readMeditation());
    if (findscript(buf)) {
      doCommand(buf);
    }
  }
}
 
numvar signal() {
  return brain.readSignalQuality();
}
 
numvar attention() {
  return brain.readAttention();
}
 
numvar meditation() {
  return brain.readMeditation();
}
