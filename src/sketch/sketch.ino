int motor_A=5;
int motor_B=6;
int motor_Speed=3;
int throttleIn=0;
int switchIn=5;
int currentSpeed=0;
int direction=1;
int acceleration=10;
int brakeSpeed=20;

void setup() {
  Serial.begin(9600);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
}

int setSpeed(int speed) {
  int newSpeed = constrain(0, currentSpeed + acceleration, speed);
  analogWrite(motor_Speed, speed);
  return newSpeed;
}

int forward(int speed) {
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
  return setSpeed(speed);
}

int backward(int speed) {
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, HIGH);
  return setSpeed(speed);
}

int readShiftStick() {
  return 1;
}

void loop() {
  int powerSwitch = analogRead(switchIn) < 512 ? 0 : 1;
  int throttle = analogRead(throttleIn);
  int speed = map(throttle, 0, 1023, 0, 255);
  direction = readShiftStick(); // +1 or -1

  if (!powerSwitch) {
    currentSpeed = setSpeed(speed - brakeSpeed);
  }
  else {
    currentSpeed = direction ?
                     forward(throttle) :
                     backward(throttle);
  }
}
