#include <Encoder.h>

#define LEFT           0
#define RIGHT          1

#define pi 3.14
/*
1寸=3.3333厘米

1英寸=2.54厘米

两者不一样，1寸=10/3厘米，1英寸=2.54厘米
*/
#define diameter 254             //轮子直径10寸-单位：mm
#define hole_number  4000       //一圈4000个脉冲
#define T_sample  20            //20ms的编码器采样频率
unsigned long nowtime = 0;
unsigned long lasttime = 0;
double v_left;
double v_right;

/*mega的中断引脚定义
  #define CORE_NUM_INTERRUPT  6
  #define CORE_INT0_PIN   2
  #define CORE_INT1_PIN   3
  #define CORE_INT2_PIN   21
  #define CORE_INT3_PIN   20
  #define CORE_INT4_PIN   19
  #define CORE_INT5_PIN   18*/

//编码器引脚定义
//------A相和B相---------------
#define LeftEncoderInterrupt 0 //中断号0 Pin-2
#define LEFT_ENC_PIN_A 2
#define LEFT_ENC_PIN_B 5
#define RightEncoderInterrupt 1 //中断号1 Pin-3
#define RIGHT_ENC_PIN_A 3
#define RIGHT_ENC_PIN_B 6
//------Z相-------------------
#define LEFT_ENC_PIN_Z  20
#define RIGHT_ENC_PIN_Z 21

//定义编码器函数
Encoder read_left_encoder(LEFT_ENC_PIN_A,LEFT_ENC_PIN_B);
Encoder read_right_encoder(RIGHT_ENC_PIN_A,RIGHT_ENC_PIN_B);
  //定义编码器读数变量
volatile long left_enc_pos = 0;
volatile long right_enc_pos = 0;

long leftCount = 0;
long rightCount = 0;

//返回左右AB相编码器的读数
long readEncoder(int i){
  if (i == LEFT) return -read_left_encoder.read();
  else return  read_right_encoder.read();
}

//返回左右轮圈数--Z相
long readCycleEncoder(int i){
  if (i == LEFT) return leftCount;
  else return  rightCount;
}

//重置左 或者 右AB相编码器
void resetEncoder(int i) {
    if (i == LEFT){
      read_left_encoder.write(0);
      return;
    } else { 
      read_right_encoder.write(0);
      return;
    }
  }

//重置左 或者 右Z相编码器
void resetCycleEncoder(int i) {
    if (i == LEFT){
      leftCount=0;
    } else { 
      rightCount=0;
    }
  }

//定义Z相的中断回调函数
void leftZChange()
{
  if(digitalRead(LEFT_ENC_PIN_Z)==HIGH)
       {leftCount ++;}
  if(digitalRead(LEFT_ENC_PIN_Z)==LOW)
       {leftCount--;}
}

void rightZChange()
{
  if(digitalRead(RIGHT_ENC_PIN_Z)==HIGH)
       {rightCount ++;}
  if(digitalRead(RIGHT_ENC_PIN_Z)==LOW)
       {rightCount--;}
}

void initEncoders(){
  //初始化AB相
  read_left_encoder.write(0);
  read_right_encoder.write(0);

  //初始化Z相
  pinMode(LEFT_ENC_PIN_Z, INPUT);
  pinMode(RIGHT_ENC_PIN_Z, INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_PIN_Z), leftZChange, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_PIN_Z),rightZChange, RISING);
}


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
  Serial.println(v_right);
//  Serial.print(" -----leftCount:");
//  Serial.print(readCycleEncoder(LEFT));
//  Serial.print(" ------rightCount:");
//  Serial.println(readCycleEncoder(RIGHT));
}
