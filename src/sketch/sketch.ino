int motor_A=5;
int motor_B=6;
int motor_Speed=3;

void setup() {
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
}

void forLoop() {
  for (int i=0; i<256; i+=5) {
    analogWrite(motor_Speed, i);
    delay(20);
  }
  for (int i=255; i>0; i-=5) {
    analogWrite(motor_Speed, i);
    delay(20);
  }
}

void loop() {
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);

  forLoop();

  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, HIGH);

  forLoop();
}
