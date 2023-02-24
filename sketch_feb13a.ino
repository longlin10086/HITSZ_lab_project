
#include <MsTimer2.h>
#include "servo.h"
#include "pidControl.h"
#include "detect.h"

Servo servo_X;
Servo servo_Z;

motor Motor_L;
motor Motor_R;

//---------------------------------------------------------编码器---------------------------------------------------------------------
void encoding_1()
{
  motor *Motor = &Motor_L;
  if (digitalRead(encoder_A_1) == HIGH)
  {
    if (digitalRead(encoder_B_1) == LOW)
      Motor->encoder++;
    else
      Motor->encoder--;
  }
  else
  {
    if (digitalRead(encoder_B_1) == HIGH)
      Motor->encoder++;
    else
      Motor->encoder--;
  }
}

void encoding_2()
{
  motor *Motor = &Motor_R;
  if (digitalRead(encoder_A_2) == HIGH)
  {
    if (digitalRead(encoder_B_2) == LOW)
      Motor->encoder++;
    else
      Motor->encoder--;
  }
  else
  {
    if (digitalRead(encoder_B_2) == HIGH)
      Motor->encoder++;
    else
      Motor->encoder--;
  }
}

void pid_set_up()
{
  motor *pid_motor_l = &Motor_L;
  motor *pid_motor_r = &Motor_R;
  set(pid_motor_l);
  set(pid_motor_r);
  track(pid_motor_l, pid_motor_r);
}

void setup()
{
  // put your setup code here, to run once:
  // TCCR1B=TCCR1B&B11111000|B00000001;
  // TCCR2B=TCCR2B&B11111000|B00000001;
  pinMode(detect_volt, INPUT);
  // pinMode(PWM_1, OUTPUT);
  // pinMode(PWM_2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(encoder_A_1, INPUT);
  pinMode(encoder_B_1, INPUT);
  pinMode(encoder_A_2, INPUT);
  pinMode(encoder_B_2, INPUT);
  Motor_L.dir = 'l';
  Motor_R.dir = 'r';

  pinMode(key, INPUT);
  servo_X.attach(SERVO_X);
  servo_Z.attach(SERVO_Z);
  setup_servo(&servo_X, &servo_Z);

  pinMode(left1, INPUT);
  pinMode(left2, INPUT);
  pinMode(left3, INPUT);
  pinMode(middle, INPUT);
  pinMode(right1, INPUT);
  pinMode(right2, INPUT);
  pinMode(right3, INPUT);

  MsTimer2::set(period, pid_set_up);
  MsTimer2::start();

  attachInterrupt(0, encoding_1, CHANGE);
  attachInterrupt(1, encoding_2, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  test_volt();
  delay(100);

  // motor* Motor = &Motor_L;
  /*Serial.print("now:");
  Serial.print(Motor->err_now);
  Serial.print("\r\n");
   Serial.print("n-l:");
  Serial.print(Motor->err_now-Motor->err_last);
  Serial.print("\r\n");
  Serial.print("output:");
  Serial.print(Motor->output);
  Serial.print("\r\n");
  Serial.print("vol:");
  Serial.print(Motor->v);
  Serial.print("\r\n");
  Serial.print("enc:");
  Serial.print(Motor->encoder);
  Serial.print("\r\n");*/
}
