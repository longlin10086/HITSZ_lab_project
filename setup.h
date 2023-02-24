//------------电机驱动------------------
#define PWM_1 12
#define PWM_2 11

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

//-----------pid-------------------------
#define encoder_A_1 2
#define encoder_B_1 8
#define encoder_A_2 3
#define encoder_B_2 13
#define period 20
#define TARGET_BEGIN 70

typedef struct PID
{
    /* data */
    volatile int encoder;
    char dir;
    float err_now;
    float err_last;
    float err_last_last;
    float v;
    float output = 0;
    float target = TARGET_BEGIN;
} motor;

//-------------循迹----------------------
#define left1 48
#define left2 50
#define left3 52
#define middle 38
#define right3 26
#define right2 24
#define right1 22
