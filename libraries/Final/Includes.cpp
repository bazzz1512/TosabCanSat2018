/*#include <Includes.h>

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
BMPSensor BMPR; //BMPRelated

bool BMPSensor::Setup() {
	Serial.println(F("Initializing BMP Sensor \n"));
	if (!bmp.begin()) {
		return false;
	}
	return true;
}

void BMPSensor::Output() {
	Serial.print(F("Temperature = "));
	Serial.print(Temperature);
	Serial.println(F(" *C"));

	Serial.print(F("Pressure = "));
	Serial.print(Pressure);
	Serial.println(F(" Pa"));

	Serial.print(F("Approx altitude = "));
	Serial.print(Pressure); // Delft http://regenradar.tudelft.nl/today.php
	Serial.println(F(" m"));

	Serial.println();
}

void BMPSensor::GetData() {
	Temperature = bmp.readTemperature();
	Pressure = bmp.readPressure();
	Altitude = bmp.readAltitude(1030.04);
}

void BMPSensor::Clear() {
	Temperature = 0;
	Pressure = 0;
	Altitude = 0;
}*/