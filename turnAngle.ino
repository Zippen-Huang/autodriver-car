#include "para.h"

//返回电位计的模拟值
int readPotentiometer(){
  return analogRead(potentiometerPin);
}

//返回电位计的模拟电压值
float readPotentiometerVoltage(){
  return analogRead(potentiometerPin)* (5.0 / 1023.0);
}

