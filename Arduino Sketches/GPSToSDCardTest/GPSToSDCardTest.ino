/*
  SD card connections:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */

int chipSelect = 4;

#include <SdFat.h>
#include <SPI.h>

SdFat SD;
File  gpsDataFile; // Data object you will write your sensor data to
const char *gpsFilename = "GPSData.txt";

//---------------------
//  Pick a serial port for the GPS

// BEST choice is a HardwareSerial port:
//    Use Serial1 on a Mega, Leo or Due board
//    You could use Serial on any board (disconnect GPS 
//       when uploading over USB).
//#define gpsPort Serial1

// 2nd best:
#include <AltSoftSerial.h>
AltSoftSerial gpsPort; // must be on specific pins (8 & 9 for an UNO)

// 3rd best: must be baud rate 9600, 19200 or 38400
//#include <NeoSWSerial.h>
//NeoSWSerial gpsPort(3,2);

// Worst: SoftwareSerial NOT RECOMMENDED
//---------------------

#include <NMEAGPS.h>
NMEAGPS GPS;
gps_fix fix;


void setup()
{
 // Serial.begin(115200);
  gpsPort.begin( 9600 );
  
  // Configure the GPS device
  GPS.send_P( &gpsPort, F("PGCMD,33,0") );  //Turn off antenna update nuisance data
  GPS.send_P( &gpsPort, F("PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0") ); //Request RMC and GGA Sentences only
  GPS.send_P( &gpsPort, F("PMTK220,1000") ); //Set update rate to 1 hz

  pinMode(10, OUTPUT); // reserve it to keep SD card happy
  if (!SD.begin(chipSelect)) {
    Serial.println( F("No SD card/reader found!") );
    for (;;); // hang here!
  }

  if (SD.exists(gpsFilename)) { //Delete old data files to start fresh
    SD.remove(gpsFilename);
  }

  gpsDataFile = SD.open(gpsFilename, FILE_WRITE);

  copyFile( "header.txt" );
}


void loop()
{
  // Read characters and parse into a fix structure
  if (GPS.available( gpsPort )) {

    // Get the new fix data (GPS quiet time just started)
    fix = GPS.read();

    // Only save data if we have a fix
    if (fix.valid.status &&
        (fix.status >= gps_fix::STATUS_STD)) {

      gpsDataFile.print( fix.latitude(), 5 );
      gpsDataFile.print( ',' );
      gpsDataFile.print( fix.longitude(), 5);
      gpsDataFile.print( ',' );
      gpsDataFile.println( fix.altitude() );
      Serial.println(F("Writing"));
      gpsDataFile.flush(); // this works, but it slows things down
    }
  }
  
  // if (button pressed) {
  //   copyFile( "trailer.txt" );  // copy the rest of the XML stuff
  //   gpsDataFile.close();
  //   while (true) { // forever
  //     blink an LED?  Beep?  LED off?
  //   }
  // }

} // loop


void copyFile( const char *filename )
{
  File file = SD.open( filename );
  if (file.isOpen()) {

    uint8_t buffer[ 256 ];
    for (;;) {
      int numRead = file.read( &buffer[0], sizeof(buffer) );
      if (numRead == 0)
        break;
      gpsDataFile.write( buffer, numRead );
    }

    file.close();
  }
}
