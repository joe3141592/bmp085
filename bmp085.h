#ifndef bmp085_H
#define bmp085_H
#include <Arduino.h>
class bmp085 {
public:
	bmp085(int addr);
	~bmp085();
	float ReadTemp();
	long ReadPressure();
	float ReadPressureAtSeaLvl(float height);
	
private:
	void calibrate();
	int readRegister(int reg);
};

#endif;