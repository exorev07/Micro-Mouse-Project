// Micro Mouse Navigation Code - Intro to Robotics Course Project
// Ekansh Arohi

// Motor A (Left Motor)
#define ENA 9
#define IN1 8
#define IN2 7

// Motor B (Right Motor)
#define ENB 10
#define IN3 6
#define IN4 5

// IR Sensors
#define IR_FRONT A0
#define IR_LEFT A1
#define IR_RIGHT A2

// Thresholds (adjust based on your sensors)
int wallThreshold = 300;  // Analog value threshold for wall detection
int baseSpeed = 50;      // Base motor speed (0-255)

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
  
  // Start serial for debugging
  Serial.begin(9600);
  
  delay(2000); // 2 second delay before starting
  
  // ===== TEST SECTION - Remove this after testing =====
  Serial.println("Testing motors - both wheels forward for 3 seconds");
  moveForward(baseSpeed);
  delay(3000);
  stopMotors();
  delay(1000); // Pause before starting main program
  Serial.println("Test complete - starting main navigation");
  // ===== END TEST SECTION =====
}

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
  bool frontWall = (frontVal > wallThreshold);
  bool leftWall = (leftVal > wallThreshold);
  bool rightWall = (rightVal > wallThreshold);
  
  // Navigation logic (left-hand rule)
  if (!frontWall && !leftWall) {
    // No wall in front or left - turn left
    turnLeft();
    delay(300);
  }
  else if (!frontWall) {
    // No wall in front - go forward
    moveForward(baseSpeed);
  }
  else if (!rightWall) {
    // Wall in front, no wall on right - turn right
    turnRight();
    delay(300);
  }
  else {
    // Walls everywhere - turn around
    turnAround();
    delay(600);
  }
  
  delay(50); // Small delay for stability
}

// Move forward
void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Swapped for right motor
  digitalWrite(IN4, HIGH); // Swapped for right motor
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

// Move backward
void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); // Swapped for right motor
  digitalWrite(IN4, LOW);  // Swapped for right motor
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

// Turn left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Swapped for right motor
  digitalWrite(IN4, HIGH); // Swapped for right motor
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

// Turn right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Swapped for right motor
  digitalWrite(IN4, LOW);  // Swapped for right motor
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

// Turn around (180 degrees)
void turnAround() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

// Stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}