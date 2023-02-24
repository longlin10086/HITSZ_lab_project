#include "setup.h"

//--------------------------------------------------------光电循迹-----------------------------------------------------------------
void track(motor *pid_motor_l, motor *pid_motor_r)
{

  if (digitalRead(middle) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN;
    pid_motor_r->target = TARGET_BEGIN;
  }
  if (digitalRead(left1) == HIGH && digitalRead(right1) == LOW)
  {
    pid_motor_l->target *= 0;
    pid_motor_r->target *= 1;
  }
  if (digitalRead(left2) == HIGH && digitalRead(right2) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.5;
    pid_motor_r->target = TARGET_BEGIN * 0.6;
  }
  if (digitalRead(left3) == HIGH && digitalRead(right3) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.7;
    pid_motor_r->target = TARGET_BEGIN * 0.8;
  }

  if (digitalRead(right3) == HIGH && digitalRead(left3) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.7;
    pid_motor_r->target = TARGET_BEGIN * 0.8;
  }
  if (digitalRead(right2) == HIGH && digitalRead(left2) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.6;
    pid_motor_r->target = TARGET_BEGIN * 0.5;
  }
  if (digitalRead(right1) == HIGH && digitalRead(left1) == LOW)
  {
    pid_motor_l->target *= 1;
    pid_motor_r->target *= 0;
  }
  delay(100);
}

//---------------------------------------------------------pid控制---------------------------------------------------------------------
void control(motor *Motor)
{
  if (Motor->dir == 'l')
  {
    if (Motor->output > 0)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    Serial.println(Motor->output);
    Serial.println("--------------------------------------------------------------");
    analogWrite(PWM_1, abs(Motor->output));
  }
  else
  {
    if (Motor->output > 0)
    {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    Serial.println(Motor->output);
    Serial.println("****************************************************************");
    analogWrite(PWM_2, abs(Motor->output));
  }
}

void pidControl(motor *Motor)
{

  float kp = 0.05;
  float ki = 0.7;
  float kd = 0.01;

  float d_u = kp * (Motor->err_now - Motor->err_last) + ki * Motor->err_now + kd * (Motor->err_now + Motor->err_last_last - 2 * Motor->err_last);
  Motor->output += d_u;
  if (Motor->output > 255 - 0.01)
    Motor->output = 255;
  if (Motor->output < -255 + 0.01)
    Motor->output = -255;

  Motor->encoder = 0;
  control(Motor);
}

//-------------------------------------------------------初始化motor-----------------------------------------------------------------
void set(motor *Motor)
{
  Motor->v = (Motor->encoder / 780.0) * 3.1415 * 2.0 * (1000 / period);
  Serial.println(Motor->v);
  Serial.println(Motor->dir);
  Motor->err_last_last = Motor->err_last;
  Motor->err_last = Motor->err_now;
  Motor->err_now = Motor->target - Motor->output;
  pidControl(Motor);
}
