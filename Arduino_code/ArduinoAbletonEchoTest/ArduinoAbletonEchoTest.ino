// --------------------------------------------------
//
// Simple test for Ableton <> Arduino connection
//     -> where and 8-bit control byte and a 16-bit 
//        value is sent back and forth between 
//        Ableton and Arduino-compatible HW.
//
// Four bytes are expected from Ableton
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value MSB> - [0:255]
// Byte 4: <value LSB> - [0:255]
//
// Written by mo thunderz (last update: 2.1.2021)
//
// --------------------------------------------------

#define CONNECTED_TIMEOUT 500000 // 0.5 second time for LED to indicate a command has been received

// for ESP32 define built-in LED (uncomment the statement below if you are using ESP32) -> Thanks to Ben Coleman for this addition :-)
// #define LED_BUILTIN 2

// internal variables
int rx_state = 0;
byte cc_type1;
byte cc_type2;
byte cc_val1;
byte cc_val2;

// needed for indication LED (goes on on arduino when serial info is received)
unsigned long   t = 0;                // current time
unsigned long   serial_t0 = 0;     // last time serial info was received

// simple function to merge most significant byte and least significant byte to single int
int bytesToInt(int l_highByte, int l_lowByte) {
  return ((unsigned int)l_highByte << 8) + l_lowByte;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // initialize LED for serial connection verification
  Serial.begin(38400);            // IMPORTANT: in MAX the same data rate must be used! Feel free to experiment with higher rates. 
}

void loop() {
  t = micros();           // take timestamp

  //-----------------------------update timeout led--------------------------------//
  if (digitalRead(LED_BUILTIN))
    if((t - serial_t0) > CONNECTED_TIMEOUT)
      digitalWrite(LED_BUILTIN, 0);

  //----------Check if control commands have been received from Ableton------------//
  if (Serial.available()) {
    serial_t0 = t;
    if (digitalRead(LED_BUILTIN) == 0)
      digitalWrite(LED_BUILTIN, 1);
      
    rx_state++;
    switch (rx_state) {
      case 1:                     // first byte is always 255 for sync
        cc_type1 = Serial.read();
        if(cc_type1 != 255) {     // reset if first is not 255 sync byte
          rx_state = 0;
        }
        break;
      case 2:                     // second is the control byte
        cc_type2 = Serial.read();
        break;        
      case 3:                     // third is the most significant byte of the value
        cc_val1 = Serial.read();     
        break;
      case 4:                     // fourth is the least significant byte of the value
        cc_val2 = Serial.read();
        rx_state = 0;

        int control = cc_type2;
        int value = bytesToInt(cc_val1, cc_val2);

        // This program simply echos the received commends back to Ableton (normally you would not do this as it loads the serial port)
        Serial.print(255);      // first byte is 255 (could have written cc_type1 here as well
        Serial.print(" ");
        Serial.print(control);  // second byte is the control byte
        Serial.print(" ");
        Serial.print(highByte(value));  // third byte is the most significant byte of the value
        Serial.print(" ");
        Serial.println(lowByte(value)); // fourth byte is the least significant byte of the value

        // At this location you can define what the Arduino should do with the received command
        
        break;
    }
  }
}
