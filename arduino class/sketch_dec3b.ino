#define EN 6
#define IN1 12
#define IN2 11
#define A 10
#define B 9

long encoder;

void getencoder(){
    if(digitalRead(A)==LOW){
      if(digitalRead(B)==LOW) encoder++;
      else encoder--;
    }else{
      if(digitalRead(B)==HIGH) encoder++;
      else encoder--;
    }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(EN,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(A,INPUT);
  pinMode(B,INPUT);
  attachInterrupt(A,getencoder,RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    analogWrite(EN,100);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    
    Serial.print("encoder = ");
    Serial.print(encoder);
    Serial.print('\n');

}
