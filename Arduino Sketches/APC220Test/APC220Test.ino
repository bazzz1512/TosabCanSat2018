#include <SoftwareSerial.h>
SoftwareSerial apc220(10,11);//TX, RX
int number = 0;

void setup() {

Serial.begin(9600);
apc220.begin(9600);

}

void loop() {
(number ++);
Serial.print ("APC220 test   ");
Serial.println (number);
apc220.println (number);
delay (1000);
}
