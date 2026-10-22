# Gesture_Controlled_Robot

## About the Project

GestureDrive is a wireless robot controlled using hand gestures. An MPU6050 accelerometer and gyroscope detects hand movements, and an Arduino Nano transmits movement commands through a 433 MHz RF transmitter. A second Arduino Nano receives these commands and controls the robot's DC motors using an L298N motor driver.

The robot supports five commands: **Forward, Backward, Left, Right, and Stop.**

## Components Used

1. Arduino Nano
2. MPU6050
3. 433 MHz RF transmitter
4. 433 MHz RF receiver
5. L298N motor driver
6. DC geared motors
7. Robot chassis and wheels
8. Battery and suitable power supplies
9. Jumper wires

## Pinout

### 1. Transmitter Unit — Arduino Nano

**MPU6050 connections**

| MPU6050 Pin | Arduino Nano Pin |
|---|---|
| VCC | 3.3 V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

**433 MHz RF transmitter connections**

| RF Transmitter Pin | Arduino Nano Pin |
|---|---|
| DATA | D12 |
| VCC | 3.3 V |
| GND | GND |

### 2. Receiver Unit — Arduino Nano

**433 MHz RF receiver connections**

| RF Receiver Pin | Arduino Nano Pin |
|---|---|
| DATA | D11 |
| VCC | 3.3 V |
| GND | GND |

**L298N motor driver connections**

| L298N Pin | Arduino Nano Pin |
|---|---|
| ENA | D5 |
| IN1 | D4 |
| IN2 | D3 |
| ENB | D6 |
| IN3 | D7 |
| IN4 | D8 |
| GND | GND |
