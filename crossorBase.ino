#include "encoder.h"
#include "turnAngle.h"
#include "para.h"

unsigned long nowtime = 0;
unsigned long lasttime = 0;
double v_left;
double v_right;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  initEncoders();
  nowtime=millis();
  //lasttime=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print("left:");
//  Serial.print(readEncoder(LEFT));
//  Serial.print(" -----right:");
//  Serial.print(readEncoder(RIGHT ));
//  Serial.print(" -----leftCount:");
//  Serial.print(readCycleEncoder(LEFT));
//  Serial.print(" ------rightCount:");
//  Serial.println(readCycleEncoder(RIGHT));

  
  //计算轮速
  if((millis() - nowtime) >= T_sample)
  {
    //double v_left = (readEncoder(LEFT) - left_enc_pos)/hole_number*2*pi*(diameter/2)/(T_sample/1000);
    v_left = (readEncoder(LEFT) - left_enc_pos)*pi*diameter/hole_number/T_sample;//单位：m/s
    v_right = (readEncoder(RIGHT) - right_enc_pos)*pi*diameter/hole_number/T_sample;
//    v_left = (readEncoder(LEFT) - left_enc_pos);//单位：m/s
//    v_right = (readEncoder(RIGHT) - right_enc_pos);
    left_enc_pos = readEncoder(LEFT);
    right_enc_pos = readEncoder(RIGHT);
    nowtime = millis();
    }

  Serial.print(" v_left:");
  Serial.print(v_left);
  Serial.print(" ----v_right:");
  Serial.print(v_right);
//  Serial.print(" -----leftCount:");
//  Serial.print(readCycleEncoder(LEFT));
//  Serial.print(" ------rightCount:");
//  Serial.println(readCycleEncoder(RIGHT));

  Serial.print(" Potentiometer:");
  Serial.print(readPotentiometer());
  Serial.print(" readPotentiometerVoltage:");
  Serial.println(readPotentiometerVoltage());
  
}
