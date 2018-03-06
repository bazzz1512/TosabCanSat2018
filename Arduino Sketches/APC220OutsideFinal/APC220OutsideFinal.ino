/*    Our APC on the ground station.
Due to a broken CP2012, we had to connect our APC to an arduino to get the data from our Cansat
*/
#include <SoftwareSerial.h>
SoftwareSerial APC220(11,10); // TX Pin, RX Pin
void setup() {
  Serial.begin(9600);             // Serial port to computer
  APC220.begin(9600);
}
void loop() {
  while (APC220.available()) {        // If APC220 has data
    Serial.write(APC220.read());      // Send the data to Serial monitor
  }
  while (Serial.available()) {      // If Serial monitor has data
    APC220.write(Serial.read());      // Send that data to APC220
  }
  Serial.flush();
}
