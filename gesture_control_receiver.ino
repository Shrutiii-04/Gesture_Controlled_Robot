#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
const int ENA = 5;
const int IN1 = 4;
const int IN2 = 3;
const int ENB = 6;
const int IN3 = 7;
const int IN4 = 8;
const int SPEED = 150;
char command = 'S';
unsigned long lastPacket = 0;
void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();
  if (!driver.init()) {
    Serial.println("433 MHz receiver failed");
    while (1);
  }
  Serial.println("Gesture robot receiver ready");
}
void loop() {
  uint8_t buffer[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t length = sizeof(buffer);
  if (driver.recv(buffer, &length) && length == 1) {
    char received = (char)buffer[0];
    if (received == 'F' || received == 'B' ||
        received == 'L' || received == 'R' ||
        received == 'S') {
      command = received;
      lastPacket = millis();
      Serial.print("Command: ");
      Serial.println(command);
    }
  }
  // Stop if the radio signal disappears.
  if (millis() - lastPacket > 500) {
    stopMotors();
    command = 'S';
    return;
  }
  switch (command) {
    case 'F': forward();  break;
    case 'B': backward(); break;
    case 'L': left();     break;
    case 'R': right();    break;
    default:  stopMotors(); break;
  }
}