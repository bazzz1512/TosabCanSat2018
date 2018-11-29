#include <SoftwareSerial.h>

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(7,6);
SoftwareSerial HC12(3, 2);
bool CanSend;

void setup()
{
  Serial.begin(9600);
   HC12.begin(1200);
   ss.begin(9600);
  CanSend = false;
  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  HC12.println("Hc12 tested");
}

void loop()
{
HC12.listen();
while (HC12.available()){
  char d = HC12.read();
  Serial.write(d);
  if (d == '$'){
  CanSend = true;
  

ss.listen();
  bool newData = false;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 2000;)
  {
    while (ss.available())
    {
      char c = ss.read();
//       Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData && CanSend)
  {
    HC12.listen();
   
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    HC12.print(F("GPS4("));
    Serial.print(F("GPS4("));
    HC12.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, DEC);
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, DEC);
    HC12.print(F(" , "));
    Serial.print(F(" , "));
    HC12.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon,DEC);
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, DEC);
    HC12.println(F(")!"));
    Serial.println(F(")!"));
    Serial.println();
    HC12.flush();
    CanSend = false;
  }
  else{
    HC12.write("!");
  }
  
}
}
}
