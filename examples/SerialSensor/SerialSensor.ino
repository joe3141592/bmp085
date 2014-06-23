#include <bmp085.h>
#include <Wire.h>

bmp085 BMP(0x77,495);
void setup(){
Serial.begin(9600);
//BMP.calibrate();
}

void loop(){
 Serial.print("Temperature:"); 
 Serial.println(BMP.ReadTemp()); //Reading calibrated temperature
 Serial.print("Pressure:");
 Serial.println(BMP.ReadPressure()); //Reading calibrated pressure
 Serial.print("Pressure at sea level:");
 Serial.println(BMP.ReadPressureAtSeaLvl()); //Reading pressure at sea level

 delay(200);

}

