#include <bmp085.h>
#include <Wire.h>

float HEIGHT_MUNICH = 519.0;
bmp085 BMP(0x77);
void setup(){
Serial.begin(9600);
//BMP.calibrate();
}

void loop(){
 Serial.print("Temperature:"); 
 Serial.print(BMP.ReadTemp()); //Reading calibrated temperature
 Serial.println(" C");
 Serial.print("Pressure:");
 Serial.print(BMP.ReadPressure()); //Reading calibrated pressure
 Serial.println(" Pa");
 Serial.print("Pressure at sea level:");
 Serial.print(BMP.ReadPressureAtSeaLvl(HEIGHT_MUNICH)); //Reading pressure at sea level
 Serial.println(" hPa");
 delay(1000);

}

