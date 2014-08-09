int motor_A=5;
int motor_B=6;
int motor_Speed=3;
int throttleIn=0;
int throttle=0;
int powerSwitch=0;
int switchIn=5;

void setup() {
  Serial.begin(9600);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
}

void setSpeed(int throttle) {
  int speed = map(throttle, 0, 511, 0, 255);
  analogWrite(motor_Speed, speed);
}

void forward(int throttle) {
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
  setSpeed(throttle);
}

void backward(int throttle) {
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, HIGH);
  setSpeed(throttle);
}

void loop() {
  powerSwitch = analogRead(switchIn) < 512 ? 0 : 1;
  throttle = analogRead(throttleIn) - 512;

  if (!powerSwitch)
    setSpeed(0);
  else if (throttle <= 0)
    backward(throttle * -1);
  else
    forward(throttle);
}
