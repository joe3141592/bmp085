#ifndef bmp085_H
#define bmp085_H
#include <Arduino.h>
class bmp085 {
public:
	bmp085(int addr, int height);
	~bmp085();
	float ReadTemp();
	long ReadRawPressure();
	float ReadPressure();
	
private:
	void calibrate();
	int readRegister(int reg);
};

#endif;