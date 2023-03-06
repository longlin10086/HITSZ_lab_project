#include "setup.h"

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
void track(motor *pid_motor_l, motor *pid_motor_r, wheel *wheel_l, wheel *wheel_r)
{
  // wheel *wheel_l = &Wheel_l;
  // wheel *wheel_r = &Wheel_r;
  float kp = 0.05;
  float ki = 0.8;
  float kd = 0.005;

  // float kp = 0.015;
  // float ki = 0.9;
  // float kd = 0.000005;
  // float target = 0;
  wheel_l->pid_setup(kp, ki, kd);
  wheel_r->pid_setup(kp, ki, kd);

  if (digitalRead(left2) == LOW && digitalRead(left3) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.8;
    pid_motor_r->target = TARGET_BEGIN * 0.8;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_l->output -= 0.17;
    wheel_r->output += 0.17;
  }
  if (digitalRead(right2) == LOW && digitalRead(right3) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.8;
    pid_motor_r->target = TARGET_BEGIN * 0.8;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_r->output -= 0.17;
    wheel_l->output += 0.17;
  }

  if (digitalRead(left2) == HIGH && digitalRead(left3) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.75;
    pid_motor_r->target = TARGET_BEGIN * 0.75;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_l->output -= 0.22;
    wheel_r->output += 0.22;
  }
  if (digitalRead(right2) == HIGH && digitalRead(right3) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.75;
    pid_motor_r->target = TARGET_BEGIN * 0.75;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_r->output -= 0.22;
    wheel_l->output += 0.22;
  }

  if (digitalRead(left2) == HIGH && digitalRead(left3) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.65;
    pid_motor_r->target = TARGET_BEGIN * 0.65;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_l->output -= 0.25;
    wheel_r->output += 0.25;
  }
  if (digitalRead(right2) == HIGH && digitalRead(right3) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.65;
    pid_motor_r->target = TARGET_BEGIN * 0.65;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_r->output -= 0.25;
    wheel_l->output += 0.25;
  }

  if (digitalRead(middle) == HIGH && digitalRead(left3) == LOW && digitalRead(left3) == LOW)
  {
    pid_motor_l->target = TARGET_BEGIN * 1.2;
    pid_motor_l->output = TARGET_BEGIN * 1.2;
    pid_motor_r->target = TARGET_BEGIN * 1.2;
    pid_motor_r->target = TARGET_BEGIN * 1.2;
    wheel_l->output = 1;
    wheel_r->output = 1;
    control(pid_motor_l);
    control(pid_motor_r);
  }

  if (digitalRead(left1) == HIGH && digitalRead(left2) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.45;
    pid_motor_l->output = TARGET_BEGIN * 0.45;
    pid_motor_r->target = TARGET_BEGIN * 0.45;
    pid_motor_r->output = TARGET_BEGIN * 0.45;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_l->output -= 0.3;
    wheel_r->output += 0.3;
  }
  if (digitalRead(right1) == HIGH && digitalRead(right2) == HIGH)
  {
    pid_motor_l->target = TARGET_BEGIN * 0.45;
    pid_motor_l->output = TARGET_BEGIN * 0.45;
    pid_motor_r->target = TARGET_BEGIN * 0.45;
    pid_motor_r->output = TARGET_BEGIN * 0.45;
    control(pid_motor_l);
    control(pid_motor_r);
    wheel_r->output -= 0.3;
    wheel_l->output += 0.3;
  }

  if (digitalRead(left1) == HIGH && digitalRead(right1) == LOW)
  {
    pid_motor_r->target = -200;
    pid_motor_r->output = -200;
    pid_motor_l->target = 200;
    pid_motor_l->output = 200;
    control(pid_motor_l);
    control(pid_motor_r);
    pid_motor_l->target = 120;
    pid_motor_l->output = 120;
    control(pid_motor_l);
  }

  if (digitalRead(right1) == HIGH && digitalRead(left1) == LOW)
  {

    pid_motor_l->target = -200;
    pid_motor_l->output = -200;
    pid_motor_r->target = 200;
    pid_motor_r->output = 200;
    control(pid_motor_l);
    control(pid_motor_r);
    pid_motor_r->target = 120;
    pid_motor_r->output = 120;
    control(pid_motor_r);
  }

  // if (digitalRead(right1) == LOW && digitalRead(left1) == LOW && digitalRead(right2) == LOW && digitalRead(left2) == LOW && digitalRead(right3) == LOW && digitalRead(left3) == LOW && digitalRead(middle) == LOW)
  // {
  //   if (wheel_l->err_last_last < 0 && wheel_r->err_last_last > 0)
  //   {
  //     pid_motor_r->target = -200;
  //     pid_motor_r->output = -200;
  //     pid_motor_l->target = 200;
  //     pid_motor_l->output = 200;
  //     control(pid_motor_l);
  //     control(pid_motor_r);
  //     pid_motor_l->target = TARGET_BEGIN * 2.25;
  //     pid_motor_l->output = TARGET_BEGIN * 2.25;

  //     pid_motor_r->target = -TARGET_BEGIN * 2.25;
  //     pid_motor_r->output = -TARGET_BEGIN * 2.25;
  //     control(pid_motor_l);
  //     control(pid_motor_r);
  //   }
  //   if (wheel_l->err_last_last > 0 && wheel_r->err_last_last < 0)
  //   {
  //     pid_motor_l->target = -200;
  //     pid_motor_l->output = -200;
  //     pid_motor_r->target = 200;
  //     pid_motor_r->output = 200;
  //     control(pid_motor_l);
  //     control(pid_motor_r);
  //     pid_motor_r->target = TARGET_BEGIN * 2.25;
  //     pid_motor_r->output = TARGET_BEGIN * 2.25;
  //     control(pid_motor_r);
  //     pid_motor_l->target = -TARGET_BEGIN * 2.25;
  //     pid_motor_l->output = -TARGET_BEGIN * 2.25;
  //     control(pid_motor_l);
  //   }
  // }

  pid_motor_l->target = pid_motor_l->target * wheel_r->output;
  pid_motor_r->target = pid_motor_r->target * wheel_l->output;

  // if (digitalRead(left1) == HIGH && digitalRead(right1) == LOW && digitalRead(left2) == LOW)
  // {
  //   pid_motor_r->target = -200;
  //   pid_motor_r->output = -200;
  //   pid_motor_l->target = 200;
  //   pid_motor_l->output = 200;
  //   control(pid_motor_l);
  //   control(pid_motor_r);
  //   pid_motor_l->target = 140;
  //   pid_motor_l->output = 140;
  //   control(pid_motor_l);
  // }
  // if (digitalRead(right1) == HIGH && digitalRead(left1) == LOW && digitalRead(right2) == LOW)
  // {

  //   pid_motor_l->target = -200;
  //   pid_motor_l->output = -200;
  //   pid_motor_r->target = 200;
  //   pid_motor_r->output = 200;
  //   control(pid_motor_l);
  //   control(pid_motor_r);
  //   pid_motor_r->target = 140;
  //   pid_motor_r->output = 140;
  //   control(pid_motor_r);
  // }
}

//---------------------------------------------------------pid控制---------------------------------------------------------------------

void pidControl(motor *Motor)
{

  float kp = 0.01;
  float ki = 0.95;
  float kd = 0.001;

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
  Serial.println(Motor->v);
  pidControl(Motor);
}
