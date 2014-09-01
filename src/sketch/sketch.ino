int motor_A=12;
int motor_B=13;
int motor_Speed=3;
int switchIn=0;
int currentSpeed=0;
int acceleration=1;
int brakeSpeed=-5;

int forwardStickPin=4;
int reverseStickPin=5;
int reverseOrForward=1;

void setup() {
  Serial.begin(9600);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
}

int setSpeed(int delta) {
  int newSpeed = constrain(currentSpeed + delta, 0, 255);
  analogWrite(motor_Speed, newSpeed);
  return newSpeed;
}

// set to reverse if last was forward,
// set to forward if last was reverse
int readShiftStick() {
  int f = !analogRead(forwardStickPin);
  int r = !analogRead(reverseStickPin);

  reverseOrForward = f ? 1 : 0;

  digitalWrite(motor_A, reverseOrForward ? HIGH : LOW);
  digitalWrite(motor_B, reverseOrForward ? LOW : HIGH);
}

void loop() {
  int powerSwitch = ! analogRead(switchIn);
  readShiftStick();

  currentSpeed = setSpeed(powerSwitch ? acceleration : brakeSpeed);

  delay(currentSpeed == 0 ? 300 : 10);
}
