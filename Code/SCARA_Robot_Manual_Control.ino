// ============================================================
// SCARA ROBOT - FULL MANUAL CONTROL
//
// LINK 1 -> NEMA17 + TB6600
// LINK 2 -> 28BYJ-48 + ULN2003
// LINK 3 -> 28BYJ-48 + ULN2003 + DC MOTOR
//
// FEATURES:
// 1. Move Link 1 by steps (+ or -)
// 2. Move Link 2 by steps (+ or -)
// 3. Calibrate Link 3
// 4. Link 3 Forward Sequence
// 5. Link 3 Reverse Sequence
// ============================================================

#include <AccelStepper.h>

// ============================================================
// LINK 1 -> NEMA17 + TB6600
// ============================================================
#define J1_STEP_PIN   3
#define J1_DIR_PIN    2
#define J1_LIMIT_PIN  A3

// ============================================================
// LINK 2 -> 28BYJ-48 + ULN2003
// ============================================================
#define J2_IN1  8
#define J2_IN2  10
#define J2_IN3  9
#define J2_IN4  11
#define J2_LIMIT_PIN 13

// ============================================================
// LINK 3 -> 28BYJ-48 + ULN2003
// ============================================================
#define J3_IN1  4
#define J3_IN2  6
#define J3_IN3  5
#define J3_IN4  7
#define J3_LIMIT_PIN 12

// ============================================================
// DC MOTOR PINS
// ============================================================
#define ENA  A0
#define INA1 A1
#define INA2 A2

// ============================================================
// MOTOR TYPES
// ============================================================
#define DRIVER_INTERFACE 1
#define FULL4WIRE 4

// ============================================================
// MOTOR OBJECTS
// ============================================================
AccelStepper joint1(DRIVER_INTERFACE,
                    J1_STEP_PIN,
                    J1_DIR_PIN);

AccelStepper joint2(FULL4WIRE,
                    J2_IN1,
                    J2_IN2,
                    J2_IN3,
                    J2_IN4);

AccelStepper joint3(FULL4WIRE,
                    J3_IN1,
                    J3_IN2,
                    J3_IN3,
                    J3_IN4);

// ============================================================
// VARIABLES
// ============================================================
String command;
long steps;

// ============================================================
// LIMIT SWITCH FUNCTION
// ============================================================
bool limitTriggered(int pin)
{
  return (digitalRead(pin) == LOW);
}

// ============================================================
// DC MOTOR FUNCTIONS
// ============================================================
void stopDCMotor()
{
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);

  analogWrite(ENA, 0);
}

void rotateDCMotorForward(int speedValue)
{
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);

  analogWrite(ENA, speedValue);
}

void rotateDCMotorBackward(int speedValue)
{
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);

  analogWrite(ENA, speedValue);
}

// ============================================================
// LINK 3 CALIBRATION
// ============================================================
void calibrateLink3()
{
  Serial.println("=================================");
  Serial.println("LINK 3 CALIBRATION STARTED");
  Serial.println("=================================");

  joint3.setMaxSpeed(300);
  joint3.setAcceleration(100);

  // Move toward limit switch
  joint3.moveTo(-100000);

  while (!limitTriggered(J3_LIMIT_PIN))
  {
    joint3.run();
  }

  Serial.println("Limit Switch Triggered");

  joint3.stop();
  joint3.runToPosition();

  joint3.setCurrentPosition(0);

  delay(500);

  // Move slightly away from switch
  Serial.println("Moving to Home Position");

  joint3.move(50);

  while (joint3.distanceToGo() != 0)
  {
    joint3.run();
  }

  joint3.setCurrentPosition(0);

  Serial.println("Calibration Complete");
}

// ============================================================
// MOVE LINK 1
// ============================================================
void moveLink1(long targetSteps)
{
  Serial.print("Moving Link 1 Steps = ");
  Serial.println(targetSteps);

  joint1.setMaxSpeed(800);
  joint1.setAcceleration(500);

  // Positive -> Forward
  // Negative -> Reverse
  joint1.move(targetSteps);

  while (joint1.distanceToGo() != 0)
  {
    joint1.run();
  }

  Serial.println("Link 1 Motion Complete");
}

// ============================================================
// MOVE LINK 2
// ============================================================
void moveLink2(long targetSteps)
{
  Serial.print("Moving Link 2 Steps = ");
  Serial.println(targetSteps);

  joint2.setMaxSpeed(500);
  joint2.setAcceleration(300);

  // Positive -> Forward
  // Negative -> Reverse
  joint2.move(targetSteps);

  while (joint2.distanceToGo() != 0)
  {
    joint2.run();
  }

  Serial.println("Link 2 Motion Complete");
}

// ============================================================
// LINK 3 FORWARD SEQUENCE
// ============================================================
void forwardSequence()
{
  Serial.println("=================================");
  Serial.println("FORWARD SEQUENCE STARTED");
  Serial.println("=================================");

  // ==========================================================
  // FAST MOVE
  // ==========================================================
  joint3.setMaxSpeed(600);
  joint3.setAcceleration(300);

  joint3.move(1200);

  while (joint3.distanceToGo() != 0)
  {
    joint3.run();
  }

  Serial.println("1200 Steps Reached");

  // ==========================================================
  // START DC MOTOR FORWARD
  // ==========================================================
  Serial.println("Starting DC Motor Forward");

  rotateDCMotorForward(80);

  delay(2000);

  // ==========================================================
  // SLOW MOVE
  // ==========================================================
  joint3.setMaxSpeed(250);
  joint3.setAcceleration(200);

  joint3.move(700);

  while (joint3.distanceToGo() != 0)
  {
    joint3.run();
  }

  // ==========================================================
  // STOP EVERYTHING
  // ==========================================================
  stopDCMotor();

  Serial.println("Forward Sequence Complete");
}

// ============================================================
// LINK 3 REVERSE SEQUENCE
// ============================================================
void reverseSequence()
{
  Serial.println("=================================");
  Serial.println("REVERSE SEQUENCE STARTED");
  Serial.println("=================================");

  // ==========================================================
  // START DC MOTOR REVERSE
  // ==========================================================
  rotateDCMotorBackward(80);

  delay(1000);

  // ==========================================================
  // REVERSE STEPPER
  // ==========================================================
  joint3.setMaxSpeed(600);
  joint3.setAcceleration(300);

  joint3.move(-1000);

  while (joint3.distanceToGo() != 0)
  {
    joint3.run();
  }

  // ==========================================================
  // STOP EVERYTHING
  // ==========================================================
  stopDCMotor();

  Serial.println("Reverse Sequence Complete");
}

// ============================================================
// SETUP
// ============================================================
void setup()
{
  Serial.begin(9600);

  // ==========================================================
  // LIMIT SWITCH PINS
  // ==========================================================
  pinMode(J1_LIMIT_PIN, INPUT_PULLUP);
  pinMode(J2_LIMIT_PIN, INPUT_PULLUP);
  pinMode(J3_LIMIT_PIN, INPUT_PULLUP);

  // ==========================================================
  // DC MOTOR PINS
  // ==========================================================
  pinMode(ENA, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);

  stopDCMotor();

  Serial.println("=================================");
  Serial.println("SCARA ROBOT READY");
  Serial.println("=================================");
}

// ============================================================
// LOOP
// ============================================================
void loop()
{
  Serial.println();
  Serial.println("=================================");
  Serial.println("ENTER COMMAND:");
  Serial.println("1 = Move Link 1");
  Serial.println("2 = Move Link 2");
  Serial.println("3 = Calibrate Link 3");
  Serial.println("f = Link 3 Forward Sequence");
  Serial.println("r = Link 3 Reverse Sequence");
  Serial.println("=================================");

  // Wait for user input
  while (Serial.available() == 0)
  {
  }

  command = Serial.readStringUntil('\n');

  command.trim();

  // ==========================================================
  // LINK 1 CONTROL
  // ==========================================================
  if (command == "1")
  {
    Serial.println("Enter Steps for Link 1:");
    Serial.println("Positive = Forward");
    Serial.println("Negative = Reverse");

    while (Serial.available() == 0)
    {
    }

    steps = Serial.parseInt();

    while (Serial.available())
    {
      Serial.read();
    }

    moveLink1(steps);
  }

  // ==========================================================
  // LINK 2 CONTROL
  // ==========================================================
  else if (command == "2")
  {
    Serial.println("Enter Steps for Link 2:");
    Serial.println("Positive = Forward");
    Serial.println("Negative = Reverse");

    while (Serial.available() == 0)
    {
    }

    steps = Serial.parseInt();

    while (Serial.available())
    {
      Serial.read();
    }

    moveLink2(steps);
  }

  // ==========================================================
  // LINK 3 CALIBRATION
  // ==========================================================
  else if (command == "3")
  {
    calibrateLink3();
  }

  // ==========================================================
  // LINK 3 FORWARD
  // ==========================================================
  else if (command == "f")
  {
    forwardSequence();
  }

  // ==========================================================
  // LINK 3 REVERSE
  // ==========================================================
  else if (command == "r")
  {
    reverseSequence();
  }

  // ==========================================================
  // INVALID COMMAND
  // ==========================================================
  else
  {
    Serial.println("Invalid Command");
  }

  Serial.println();
  Serial.println("NEXT COMMAND READY");
}
