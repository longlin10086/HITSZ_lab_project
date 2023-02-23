//-------------检测电压-------------------
#define detect_volt A0
#define key A4


int count;
//--------------------------------------------------------检测电压-----------------------------------------------------------------
int button_click(){
  int flag = 1;
  if(flag && (digitalRead(key)==LOW)){
    flag = 0;
    return 1;
  }
  return 0;
}

void turn_off(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);  
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);     
}

void test_volt(){

  float sum;

  sum += analogRead(detect_volt);
  if(++count > 200){
    float volt_val = sum*0.05371/2;
    count = 0;
    sum = 0;
    if(volt_val < 700) turn_off();
  }
  if(button_click()) turn_off();
}
