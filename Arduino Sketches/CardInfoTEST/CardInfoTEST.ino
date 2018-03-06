#include <SD.h>

#include <SoftwareSerial.h>
 
//Create software serial object to communicate with GPS
SoftwareSerial gps(7,6);
SoftwareSerial HC12(3,2); // HC-12 TX Pin, HC-12 RX Pin
 
File myFile; 
void setup()
{
  Serial.begin(9600);
  gps.begin(9600);
  HC12.begin(9600); 
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
 
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  gps.begin(9600);
  delay(1000);
  Serial.println("initialization done.");
  myFile = SD.open("test.txt", FILE_WRITE);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.print("dmadmkaimda");
  // close the file:
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop()
{
  myFile = SD.open("test.txt", FILE_WRITE);
 if (myFile) {
    Serial.print("Writing to test.txt...");
    while(gps.available()){
    myFile.write(gps.read());
    HC12.write(gps.read());
    }
  // close the file:
    Serial.println("done.");
    myFile.close();
  }
}
