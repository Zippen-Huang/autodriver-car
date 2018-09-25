//定义编码器读数变量
volatile long left_enc_pos = 0;
volatile long right_enc_pos = 0;

long leftCount = 0;
long rightCount = 0;

long readEncoder(int i);
long readCycleEncoder(int i);
void resetEncoder(int i);
void resetCycleEncoder(int i);
void leftZChange();
void rightZChange();
void initEncoders();

