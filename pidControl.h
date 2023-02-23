#include "setup.h"





//--------------------------------------------------------光电循迹-----------------------------------------------------------------
void track(motor* pid_motor_l, motor* pid_motor_r){
  if(digitalRead(left1)==LOW){
    pid_motor_l->target = 0;
    pid_motor_r->target *= 0.65;
  }
  if(digitalRead(left2)==LOW){
    pid_motor_l->target *= 0.15;
    pid_motor_r->target *= 0.75;
  }
  if(digitalRead(left3)==LOW){
    pid_motor_l->target *= 0.6;
    pid_motor_r->target *= 0.9;
  }
  if(digitalRead(middle)==LOW){
    pid_motor_l->target = pid_motor_l->output;
    pid_motor_r->target = pid_motor_r->output;
  }
  if(digitalRead(right3)==LOW){
    pid_motor_l->target *= 0.9;
    pid_motor_r->target *= 0.6;
  }
  if(digitalRead(right2)==LOW){
    pid_motor_l->target *= 0.75;
    pid_motor_r->target *= 0.15;
  }
  if(digitalRead(right1)==LOW){
    pid_motor_l->target *= 0.65;
    pid_motor_r->target = 0;
  }  
}



//---------------------------------------------------------pid控制---------------------------------------------------------------------
void control(motor* Motor){
  if(Motor->dir == 'l'){
    if(Motor->output > 0){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }else{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
   }
   Serial.println(Motor->output);
   Serial.println("--------------------------------------------------------------");
    analogWrite(PWM_1, abs(Motor->output));
    }else{
      if(Motor->output > 0){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }else{
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
   }
    Serial.println(Motor->output);
    Serial.println("****************************************************************");
    analogWrite(PWM_2, abs(Motor->output));
    }
}

void pidControl(motor* Motor){
    
  float kp = 0.05;
  float ki = 0.7;
  float kd = 0.01;


  float d_u = kp*(Motor->err_now-Motor->err_last)+ki*Motor->err_now+kd*(Motor->err_now+Motor->err_last_last-2*Motor->err_last);
  Motor->output += d_u;
  if(Motor->output > 255-0.01) Motor->output = 255;
  if(Motor->output < -255+0.01) Motor->output = -255;

  Motor->encoder = 0;
  control(Motor);
}

//-------------------------------------------------------初始化motor-----------------------------------------------------------------
void set(motor* Motor){
    Motor->v = (Motor->encoder/780.0)*3.1415*2.0*(1000/period);
    Motor->err_last_last = Motor->err_last;
    Motor->err_last = Motor->err_now;
    Motor->err_now = Motor->target - Motor->output;
    pidControl(Motor);
}
