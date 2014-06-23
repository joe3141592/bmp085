#include "bmp085.h"
#include <Wire.h>

//oss 
int oss = 0;
// Calibration values
short ac1 = 0;
short ac2 = 0;
short ac3 = 0;
unsigned short ac4 = 0;
unsigned short ac5 = 0;
unsigned short ac6 = 0;
short b1 =  0;
short b2 =  0;
short mb =  0;
short mc =  0;
short md =  0;
// Global values
unsigned long UP = 0;
long temp = 0;
long b5 = 0;
int ADDR = 0;
int calibrated = 0;

int bmp085::readRegister(int reg){
  Wire.beginTransmission(ADDR);
  Wire.write(reg);
  Wire.endTransmission(); 
  delay(5);
  Wire.requestFrom(ADDR, 2);
  while (Wire.available()) {
     byte msb = Wire.read();
     byte lsb = Wire.read();
     return msb << 8 | lsb;
  }
}

bmp085::bmp085(int addr){
	ADDR = addr;
	
  
}
bmp085::~bmp085(){};

void bmp085::calibrate() {
  if (calibrated == 0) {
  ac1 = readRegister(0xAA);
  ac2 = readRegister(0xAC);
  ac3 = readRegister(0xAE);
  ac4 = readRegister(0xB0);
  ac5 = readRegister(0xB2);
  ac6 = readRegister(0xB4);
  b1 =  readRegister(0xB6);
  b2 =  readRegister(0xB8);
  mb =  readRegister(0xBa);
  mc =  readRegister(0xBC);
  md =  readRegister(0xBE);
  calibrated = 1;
}	
}

long bmp085::ReadPressure(){
calibrate();

  long b6, x1, x2, x3, b3, p;
  unsigned long b4, b7;
  Wire.beginTransmission(ADDR);
  Wire.write(0xF4);
  Wire.write(0x34 + (oss<<6));
  Wire.endTransmission();
  Wire.beginTransmission(ADDR);
  Wire.write(0xF6);
  Wire.endTransmission();
  delay(6);
  Wire.requestFrom(ADDR,3);
  unsigned long UP;
  while (Wire.available()) {
   unsigned char msb = Wire.read();
   unsigned char lsb = Wire.read(); 
   unsigned char xlsb = Wire.read();
   UP = (((unsigned long)msb<<16) | ((unsigned long)lsb << 8) | (unsigned long)xlsb) >> (8-oss);
  }
  
  b6 = b5-4000;
  x1 = (b2*(b6*b6/pow(2,12))) / pow(2,11);
  x2 = ac2*b6 / pow(2,11);
  x3 = x1+x2;
  b3 = (((ac1*4+x3)<<oss)+2)/4;
  x1 = ac3*b6/pow(2,13),
  x2 = (b1*(b6*b6/pow(2,12)))/pow(2,16);
  x3 = ((x1+x2)+2)/pow(2,2);
  b4 = ac4*(unsigned long) (x3+32768) / pow(2,15);
  b7 = ((unsigned long) UP - b3)*(50000>>oss);
if (b7< 0x80000000) { p = (b7 * 2) / b4; }
else {p = (b7/b4)*2;}
x1 = (p / pow(2,8))* (p / pow(2,8));
x1 = (x1*3038) / pow(2,16);
x2 = (-7357*p) / pow(2,16);
p = p + (x1+x2+3791) / pow(2,4);
return p;
}
  
float bmp085::ReadPressureAtSeaLvl(float height){
	long rawPres = ReadPressure();
	float result = rawPres / pow((1-height/44330.00),5.255)/100;
	return result;
}


float bmp085::ReadTemp (){
  calibrate();
  long x1 = 0;
  long x2 = 0;
  //Temperaturwerte anfordern, dazu wird der Wert 0x2E in Rge. 0xF4 geschrieben
  Wire.beginTransmission(ADDR);
  Wire.write(0xF4);
  Wire.write(0x2E);
  Wire.endTransmission();
  delay(5);
  //Pointer auf Register 0xF6 setzen
  Wire.beginTransmission(ADDR);
  Wire.write(0xF6);
  Wire.endTransmission();
  //Auslesen der Werte
  Wire.requestFrom(ADDR,2);
  while (Wire.available()){
  byte msb = Wire.read();
  byte lsb = Wire.read();
  long UT = msb << 8 | lsb;
  x1 = (UT-ac6)*ac5/pow(2,15);
  x2 = mc*pow(2,11)/(x1+md);
  b5 = x1+x2;
  return (b5+8)/pow(2,4)/10;
  
  } 

}