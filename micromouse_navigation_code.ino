// Micro Mouse Navigation Code - Intro to Robotics Course Project
// exorev07

// Left Motor
#define ENA 9
#define IN1 8
#define IN2 7

// Right Motor
#define ENB 10
#define IN3 6
#define IN4 5

// IR Sensors
#define IR_FRONT A0
#define IR_LEFT A1
#define IR_RIGHT A2

// Thresholds
int wallThreshold = 500; // ~100 when wall detected & ~1000 when clear
int baseSpeed = 32; // Base motor speed (0-255)
float leftMotorCompensation = 1.0;
float rightMotorCompensation = 1.12;

void setup() {
  // Motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // IR sensor pins as inputs
  pinMode(IR_FRONT, INPUT);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  // Serial for debugging
  Serial.begin(9600);
  
  delay(2000);


void loop() {
  // Read IR sensors
  int frontVal = analogRead(IR_FRONT);
  int leftVal = analogRead(IR_LEFT);
  int rightVal = analogRead(IR_RIGHT);
  
  // Debug: Print sensor values
  Serial.print("Front: ");
  Serial.print(frontVal);
  Serial.print(" | Left: ");
  Serial.print(leftVal);
  Serial.print(" | Right: ");
  Serial.println(rightVal);
  
  // Wall detection
  bool frontWall = (frontVal < wallThreshold);
  bool leftWall = (leftVal < wallThreshold);
  bool rightWall = (rightVal < wallThreshold);
  
  // Navigation logic (left-hand rule for maze solving)
  if (frontWall && !rightWall) {
    // Wall in front, no wall on right - turn right
    stopMotors();
    delay(1000);
    turnRight();
    delay(700);
    stopMotors();
    delay(1000);
  }
  else if (frontWall && rightWall && !leftWall) {
    // Wall in front and right, no wall on left - turn left
    stopMotors();
    delay(1000);
    turnLeft();
    delay(700);
    stopMotors();
    delay(1000);
  }
  else if (frontWall && rightWall && leftWall) {
    // Walls everywhere - turn around
    stopMotors();
    delay(1000);
    turnAround();
    delay(400);
    stopMotors();
    delay(1000);
  }
  else {
    // No wall in front - keep moving forward
    moveForward(baseSpeed);
  }
  delay(10); // Small delay for stability
}

void moveForward(int speed) {
  // Left motor forward (with compensation)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Right motor forward (with compensation)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Set speeds with compensation
  analogWrite(ENA, speed * leftMotorCompensation);
  analogWrite(ENB, speed * rightMotorCompensation);
}

void moveBackward(int speed) {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speeds
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void turnLeft() {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Set speeds
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

void turnRight() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speeds
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

void turnAround() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speeds
  analogWrite(ENA, baseSpeed+10);
  analogWrite(ENB, baseSpeed+10);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}