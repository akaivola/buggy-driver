int motor_A=5;
int motor_B=6;
int motor_Speed=3;
int switchIn=0;
int currentSpeed=0;
int acceleration=1;
int brakeSpeed=-5;

int forwardStickPin=4;
int reverseStickPin=5;
int reverseOrForward=1;

void setup() {
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  pinMode(motor_Speed, OUTPUT);
  pinMode(forwardStickPin, INPUT);
  pinMode(reverseStickPin, INPUT);
  pinMode(switchIn, INPUT);
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
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
  bool bothOff = !(f | r);
  //Serial.print(f);
  //Serial.print("/");
  //Serial.print(r);
  //Serial.print(" , ");
  //Serial.print(bothOff);

  int newReverseOrForward = bothOff ? reverseOrForward : f ? 1 : 0;
  return reverseOrForward ^ newReverseOrForward  && currentSpeed == 0 ? newReverseOrForward : reverseOrForward;
}

void loop() {
  int powerSwitch = ! analogRead(switchIn);
  reverseOrForward = readShiftStick();

  digitalWrite(motor_A, reverseOrForward ? HIGH : LOW);
  digitalWrite(motor_B, reverseOrForward ? LOW : HIGH);

  currentSpeed = setSpeed(powerSwitch ? acceleration : brakeSpeed);
  //Serial.println(reverseOrForward);

  delay(currentSpeed == 0 ? 300 : 10);
}
