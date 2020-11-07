/**
 * Simple routine that performs the following:
 *  1. Configures the software UART on pins 2 and 4 (RX,TX)
 *  2. Increments a 32-bit variable every 500ms
 *  4. If it receives a '1' character from bluetooth, it toggles an LED
 *     
 *  @author Justin Bauer - mcuhq.com
 *  @date 4.24.2016
 *  
 *  @editor Chase Fensore
 *  
 *  
 *  RESOURCE: https://forum.arduino.cc/index.php?topic=151663.0
 *  
 *  SERIAL BT LIBRARY: https://www.arduino.cc/en/Reference/softwareSerial
 */

#include <SoftwareSerial.h> // use the software uart
SoftwareSerial bluetooth(2, 4); // RX, TX

unsigned long previousMillis = 0;        // will store last time
const long interval = 500;           // interval at which to delay
static uint32_t tmp; // increment this

void setup() {
  pinMode(13, OUTPUT); // for LED status
  bluetooth.begin(9600); // start the bluetooth uart at 9600 which is its default
  delay(200); // wait for voltage stabilize
  bluetooth.print("AT+NAMEmcuhq.com"); // place your name in here to configure the bluetooth name.
                                       // will require reboot for settings to take affect. 
  delay(3000); // wait for settings to take affect. 
}

//TODO: send value that is 1 greater than what we want for the laser power.

void loop() {
  if (bluetooth.available() ) { // check if anything in UART buffer
  unsigned char b = 57; // NOTE: bluetooth value MUST be compared to ASCII value as char. 
        // i.e: "255" sent over bluetooth SHOULD = (255 + 48)
        // GOAL: send unique #'s 0-255 over Bluetooth. 
        // IDEA: Lmost digit [], Mid digit [], Rmost digit [], TERMINATING DIGIT

        
    if((bluetooth.read()) == b){ // did we receive this character (255)?
       digitalWrite(13,!digitalRead(13)); // if so, toggle the onboard LED
    }
  }
  //On Arduino, char is int8_t but byte is uint8_t.
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bluetooth.print(tmp++); // print this to bluetooth module
  }

}
