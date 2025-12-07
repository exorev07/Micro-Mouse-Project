# Micro-Mouse-Project

Arduino-based micromouse robot for autonomous maze navigation.

## Project Overview

This project is part of the Introduction to Robotics course (3rd semester). The micromouse is designed to autonomously navigate through a maze using IR sensors and a wall-following algorithm.

## Hardware Components

- Arduino board
- 2x DC motors (left and right wheels)
- Motor driver (L298N or similar)
- 3x IR sensors (front, left, right)
- Power supply

## Features

- Wall detection using IR sensors
- Left-hand wall-following algorithm
- Adjustable motor speeds
- Dead-end detection and U-turn capability

## Pin Configuration

**Motors:**
- Motor A (Left): ENA (Pin 9), IN1 (Pin 8), IN2 (Pin 7)
- Motor B (Right): ENB (Pin 10), IN3 (Pin 6), IN4 (Pin 5)

**Sensors:**
- Front IR: A0
- Left IR: A1
- Right IR: A2

## Setup Instructions

1. Upload the `micromouse_navigation_code.ino` to your Arduino board
2. Adjust the `wallThreshold` value based on your IR sensor readings
3. Modify `baseSpeed` to control robot speed (0-255)
4. Place the robot in a maze and power on

## Usage

The robot will automatically start navigating after a 2-second delay. It follows these rules:
- Turns left when no left wall is detected
- Moves forward when a left wall exists but no front wall
- Turns right when both left and front walls are present
- Performs U-turn when surrounded by walls (dead end)

## Team

Feel free to contribute by creating pull requests or opening issues for improvements.

## License

This project is licensed under the MIT License.
