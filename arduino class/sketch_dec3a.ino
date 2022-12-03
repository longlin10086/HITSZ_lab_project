#define EN 13
#define IN1 12
#define IN2 11


void setup() {
  // put your setup code here, to run once:
  pinMode(EN,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(EN,HIGH);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    delay(3000);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);

}
