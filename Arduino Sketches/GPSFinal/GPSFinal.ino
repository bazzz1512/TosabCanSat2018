#include <SoftwareSerial.h>

#include <TinyGPS.h>

/* 
Final code for our GPS tracker
*/
//Create SoftwareSerial ports
TinyGPS gps;
SoftwareSerial ss(6, 7); //ss stands for softwareserial and is our direct connection with the gps module
SoftwareSerial HC12(3, 2);

void setup()
{
  Serial.begin(9600);
   HC12.begin(9600);
   ss.begin(9600);

  //Output test sentences to Serial and to HC12
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  HC12.println("Hc12 tested");
}

void loop()
{
ss.listen();
  bool newData = false;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // Raw GPS data
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    //Prepare data to be sent with the HC12 
    HC12.listen();
   
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    HC12.print(F("L= "));
    Serial.print(F("L= "));
    HC12.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, DEC); //Check if the coordinates are avaible, if so, send them
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, DEC);
    HC12.print(F("B= "));
    Serial.print(F("B= "));
    HC12.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon,DEC); //check if the coordinates are avaible, if so, send them
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, DEC);
    Serial.println();
    HC12.flush();
  }
  
 
}
