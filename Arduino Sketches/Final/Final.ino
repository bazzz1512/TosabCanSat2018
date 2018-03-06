#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 9 
#define BMP_CS 8

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
SoftwareSerial HC12(3,2); // HC-12 TX Pin, HC-12 RX Pin
 SoftwareSerial apc220(10,11);//TX, RX

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  apc220.begin(9600);
  
  Serial.println(F("BMP280 test"));
  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
 
}

void loop() {
  HC12.listen();
  while (HC12.available()){
    char c = HC12.read();
    Serial.write(c);
    apc220.print(c);
    apc220.flush();
  }
//  apc220.listen();
  Serial.println(F("\n"));
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1030)); // this should be adjusted to your local forcase
    Serial.println(" m");
    
    Serial.println();

    apc220.print(F("Temperature = "));
    apc220.print(bmp.readTemperature());
    apc220.println(" *C");
    
    apc220.print(F("Pressure = "));
    apc220.print(bmp.readPressure());
    apc220.println(" Pa");

    apc220.print(F("Approx altitude = "));
    apc220.print(bmp.readAltitude(1030)); // this should be adjusted to your local forcase
    apc220.println(" m");
    
    apc220.println();
    apc220.flush();
    delay(1000);
}






