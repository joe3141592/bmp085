#include <bmp085.h>
#include <Wire.h>

bmp085 BMP(0x77,495);
void setup(){
Serial.begin(9600);
//BMP.calibrate();
}

void loop(){
 Serial.print("TEMP:");
 Serial.println(BMP.ReadTemp());
 Serial.print("Pressure:");
 Serial.println(BMP.ReadPressure());
 delay(200);

}

