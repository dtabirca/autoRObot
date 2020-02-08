#include "NewPing.h"

// MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8
#define MOTOR_1_PWM 5
// MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9
#define MOTOR_2_PWM 6
// SPEED
#define MOVE_INTERVAL 250 // ms delay
#define TURN_INTERVAL 100 // ms delay
short MOTOR_DEFAULT_SPEED = 150; // default motor speed; will change in relation with the moving object;
#define MOTOR_TURN_SPEED 255 // turn speed
// ULTRASONIC 1
#define SONIC_1_TRIGGER_PIN 10
#define SONIC_1_ECHO_PIN 11
#define SONIC_MAX_DISTANCE 400 // cm
#define SONIC_READ_INTERVAL 50 // read interval ms
#define SONIC_MIN_OBJECT_DISTANCE 45 // cm
#define SONIC_MAX_OBJECT_DISTANCE 80 // cm
float SONIC_1_DISTANCE;
// MODES
#define BOT_MODE_STANDBY 0
#define BOT_MODE_FOLLOW 1
#define BOT_MODE_AVOID 2
unsigned short BOT_MODE = BOT_MODE_STANDBY; // standby, follow, avoid

NewPing sonar(SONIC_1_TRIGGER_PIN, SONIC_1_ECHO_PIN, SONIC_MAX_DISTANCE);

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  pinMode(MOTOR_1_PWM, OUTPUT);
  pinMode(MOTOR_2_PWM, OUTPUT);
  pinMode(SONIC_1_TRIGGER_PIN, OUTPUT);
  pinMode(SONIC_1_ECHO_PIN, INPUT);
}

void loop()
{
  // read sensors
  SONIC_1_DISTANCE = sonar.ping_cm();
  if (SONIC_1_DISTANCE >= 400 || SONIC_1_DISTANCE <= 2){
    // probably reading error 
    // keep the same mode
  }
  else{
    if (SONIC_1_DISTANCE < SONIC_MIN_OBJECT_DISTANCE){
      BOT_MODE = BOT_MODE_AVOID;
    }
    else if (SONIC_1_DISTANCE > SONIC_MAX_OBJECT_DISTANCE){
      BOT_MODE = BOT_MODE_FOLLOW;      
    }
    else{
      BOT_MODE = BOT_MODE_STANDBY;    
    }
  }
  // set action
  switch (BOT_MODE) {
    case BOT_MODE_FOLLOW:
      moveForward();
      break;
    case BOT_MODE_AVOID:
      moveBackward();  
      break;
    case BOT_MODE_STANDBY:
    default:
      fullStop();
      break;
  }
  //
  delay(SONIC_READ_INTERVAL);
}
  
void fullStop(){
  Serial.println("Stop");
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, LOW);
  analogWrite(MOTOR_1_PWM, 0);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, LOW);
  analogWrite(MOTOR_2_PWM, 0);
}
void moveBackward(){
  Serial.println("Move back");
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  analogWrite(MOTOR_1_PWM, MOTOR_DEFAULT_SPEED);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH);
  analogWrite(MOTOR_2_PWM, MOTOR_DEFAULT_SPEED);
  delay(MOVE_INTERVAL);

}
void moveForward(){
  Serial.println("Move forward"); 
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, LOW);
  analogWrite(MOTOR_1_PWM, MOTOR_DEFAULT_SPEED);
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);
  analogWrite(MOTOR_2_PWM, MOTOR_DEFAULT_SPEED);  
  delay(MOVE_INTERVAL);
}
void turnLeft(){
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, LOW);
  analogWrite(MOTOR_1_PWM, MOTOR_TURN_SPEED);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH);
  analogWrite(MOTOR_2_PWM, MOTOR_TURN_SPEED);
  delay(TURN_INTERVAL);
}
void turnRight(){
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  analogWrite(MOTOR_1_PWM, MOTOR_TURN_SPEED);
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);
  analogWrite(MOTOR_2_PWM, MOTOR_TURN_SPEED);
  delay(TURN_INTERVAL);  
}
