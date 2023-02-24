#include <Servo.h>
#define SERVO_X 9 
#define SERVO_Z 10



void pick_up(Servo* servo){
    servo->write(0);
    delay(150);
    servo->write(180);
    delay(150);
}

void head_up(Servo* servo){
    servo->write(90);
    delay(150);
    servo->write(0);
    delay(150);
}

void close(Servo* servo){
    servo->write(0);
    delay(150); 
    servo->write(180);
    delay(150);
}

void setup_servo(Servo* servo_x, Servo* servo_z){
    servo_x->write(180);
    delay(200);
    servo_z->write(0);
    delay(200); 
    pick_up(servo_x);
    head_up(servo_z);
    close(servo_x);
    delay(1000);
}
