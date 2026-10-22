
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <RH_ASK.h>
#include <SPI.h>
MPU6050 mpu6050(Wire);
RH_ASK driver;
char command = 'S';
unsigned long lastSend = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  if (!driver.init()) {
    Serial.println("433 MHz transmitter failed");
    while (1);
  }
  Serial.println("Gesture transmitter ready");
}
void loop() {
  mpu6050.update();
  float ax = mpu6050.getAccX();
  float ay = mpu6050.getAccY();
  // Adjust signs after testing your sensor orientation.
  if (ay > 0.35) {
    command = 'F';
  } else if (ay < -0.35) {
    command = 'B';
  } else if (ax > 0.35) {
    command = 'R';
  } else if (ax < -0.35) {
    command = 'L';
  } else {
    command = 'S';
  }
  if (millis() - lastSend >= 100) {
    driver.send((uint8_t*)&command, 1);
    driver.waitPacketSent();
    Serial.print("Command: ");
    Serial.print(command);
    Serial.print(" | AccX: ");
    Serial.print(ax);
    Serial.print(" | AccY: ");
    Serial.println(ay);
    lastSend = millis();
  }
}
