#include "setup.h"
float err;
float err_last;
float err_last_last;
float output;

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
    analogWrite(PWM_2, abs(Motor->output));
  }
}
//--------------------------------------------------------光电循迹-----------------------------------------------------------------
void track(motor *pid_motor_l, motor *pid_motor_r)
{
  float kp = 0.07;
  float ki = 0.65;
  float kd = 0.0005;
  float target = 0;

  err_last_last = err_last;
  err_last = err;
  err = target - output;

  if (digitalRead(left2) == HIGH)
    err = err - 7.25;
  if (digitalRead(left3) == HIGH)
    err = err - 1.5;
  if (digitalRead(right3) == HIGH)
    err = err + 1.5;
  if (digitalRead(right2) == HIGH)
    err = err + 7.25;

  output += kp * (err - err_last) + ki * err + kd * (err + err_last_last - 2 * err_last);
  pid_motor_l->target = TARGET_BEGIN - 3.75 * output;
  pid_motor_r->target = TARGET_BEGIN + 3.75 * output;

  if (digitalRead(left1) == HIGH && digitalRead(right1) == LOW)
  {

    // pid_motor_r->target = TARGET_BEGIN / 2;
    // pid_motor_r->output = TARGET_BEGIN / 2;
    // pid_motor_l->target = TARGET_BEGIN / 2;
    // pid_motor_l->output = TARGET_BEGIN / 2;
    // control(pid_motor_l);
    // control(pid_motor_r);
    // delay(100);

    pid_motor_r->target = -190;
    pid_motor_r->output = -190;
    pid_motor_l->target = 190;
    pid_motor_l->output = 190;
    control(pid_motor_l);
    control(pid_motor_r);
    pid_motor_l->target = 150;
    pid_motor_l->output = 150;
    control(pid_motor_l);
    // pid_motor_l->target = 130;
    // pid_motor_l->output = 130;
    // control(pid_motor_l);
  }
  if (digitalRead(right1) == HIGH && digitalRead(left1) == LOW)
  {

    // pid_motor_r->target = -TARGET_BEGIN / 2;
    // pid_motor_r->output = -TARGET_BEGIN / 2;
    // pid_motor_l->target = -TARGET_BEGIN / 2;
    // pid_motor_l->output = -TARGET_BEGIN / 2;
    // control(pid_motor_l);
    // control(pid_motor_r);
    // delay(100);

    pid_motor_l->target = -190;
    pid_motor_l->output = -190;
    pid_motor_r->target = 190;
    pid_motor_r->output = 190;
    control(pid_motor_l);
    control(pid_motor_r);
    pid_motor_r->target = 150;
    pid_motor_r->target = 150;
    control(pid_motor_r);
    // pid_motor_r->target = 130;
    // pid_motor_r->target = 130;
    // control(pid_motor_r);
  }
}

//---------------------------------------------------------pid控制---------------------------------------------------------------------

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
  Motor->err_last_last = Motor->err_last;
  Motor->err_last = Motor->err_now;
  Motor->err_now = Motor->target - Motor->output;
  pidControl(Motor);
}
