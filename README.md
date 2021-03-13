# ArduinoAbleton
Code for interfacing between Arduino and Ableton (via Max for Live - Cycling 74)

See Youtube for further details on this solution:
https://youtu.be/pBRe2xz7dgQ

# Installation
1) Copy file in the "MaxForLive_code" directory to Documents\Ableton\User Library\Presets\MIDI Effects\Max MIDI Effect
2) Copy folder in the "Arduino_code" directory to Documents\Arduino
3) Open Arduino IDE and program Arduino/Teensy/ESP32 with ArduinoAbletonEchoTest.ino (and LEAVE the device connected to the computer via USB)
4) Open Ableton and on the left goto Catagories -> Max for Live -> Max MIDI Effect and move ArduinoAbletonEchoTest to a midi track

# How to use
This simple example shows how to send an 8-bit control byte and a 16-bit value from Ableton to the Arduino, interpret it and send it back to Ableton. I tried to add as much as explanation as possible, so should be self-explanatory, but see for my Youtube video above for further explanations.

Have fun ;-)

mo thunderz
