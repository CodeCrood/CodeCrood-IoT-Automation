#include <AFMotor.h>

// Define motors
AF_DCMotor leftMotor(2);  // M2 Left motor
AF_DCMotor rightMotor(3); // M3 Right motor

// Define sensor pins
const int sensorPins[5] = {A0, A1, A2, A3, A4}; // Sensors from left to right

// Define thresholds
const int blackThreshold = 600; // Black threshold for sensors

// Motor speeds
const int forwardSpeed = 90;  // Speed for forward movement
const int turnSpeed = 110;     // Speed for turning
const int backwardSpeed = 90; // Speed for backward movement

// Variable to track the last direction the car was turning
char lastDirection = 'C'; // 'C' for centered, 'L' for left, 'R' for right

void setup() {
    Serial.begin(9600); // Initialize Serial for debugging

    // Initialize motors
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);

    // Initialize sensor pins
    for (int i = 0; i < 5; i++) {
        pinMode(sensorPins[i], INPUT);
    }
}

void loop() {
    // Read sensor values
    int sensorValues[5];
    for (int i = 0; i < 5; i++) {
        sensorValues[i] = analogRead(sensorPins[i]);
    }

    // Determine sensor states (0 = white, 1 = black)
    int sensorStates[5];
    for (int i = 0; i < 5; i++) {
        sensorStates[i] = sensorValues[i] > blackThreshold ? 1 : 0;
    }

    // Debugging: Print sensor states
    Serial.print("Sensor States: ");
    for (int i = 0; i < 5; i++) {
        Serial.print(sensorStates[i]);
        Serial.print(" ");
    }
    Serial.println();

    // Handle all 32 combinations using only if conditions
    if (sensorStatesMatch(sensorStates, "00000")) {
        if (lastDirection == 'R') {
            slightRightRotation();
        } else if (lastDirection == 'L') {
            slightLeftRotation();
        }
          else if(lastDirection == 'C') {
            slightBackward();
        } else {
            moveForward(); // Default behavior if no last direction
        }
    }
    if (sensorStatesMatch(sensorStates, "00001")) {
        slightRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "00010")) {
        slightRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "00011")) {
        turnURight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "00100")) {
        moveForward();
        lastDirection = 'C'; // Centered, no specific direction
    }
    if (sensorStatesMatch(sensorStates, "00101")) {
        moveForward();
        lastDirection = 'C'; // Centered, no specific direction
    }
    if (sensorStatesMatch(sensorStates, "00110")) {
        slightRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "00111")) {
        sharpRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01000")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01001")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01010")) {
        rotateOnSpot();
        lastDirection = 'C'; // Centered, no specific direction
    }
    if (sensorStatesMatch(sensorStates, "01011")) {
        slightRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01100")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01101")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "01110")) {
        moveBackward();
        lastDirection = 'C'; // Centered, no specific direction
    }
    if (sensorStatesMatch(sensorStates, "01111")) {
        sharpRight();
        lastDirection = 'R'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10000")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10001")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10010")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10011")) {
        turnULeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10100")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10101")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10110")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "10111")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11000")) {
        turnULeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11001")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11010")) {
        slightLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11011")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11100")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11101")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11110")) {
        sharpLeft();
        lastDirection = 'L'; // Update last direction
    }
    if (sensorStatesMatch(sensorStates, "11111")) {
        moveForward();
        lastDirection = 'C'; // Centered, no specific direction
    }

    delay(10); // Small delay for stability
}

// Helper function to match sensor states
bool sensorStatesMatch(int states[], const char *pattern) {
    for (int i = 0; i < 5; i++) {
        if ((pattern[i] - '0') != states[i]) {
            return false;
        }
    }
    return true;
}

// Movement functions
void moveForward() {
    leftMotor.setSpeed(forwardSpeed);
    rightMotor.setSpeed(forwardSpeed);
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    Serial.println("Move Forward");
}

void slightLeft() {
    leftMotor.setSpeed(forwardSpeed / 2);
    rightMotor.setSpeed(forwardSpeed);
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    Serial.println("Slight Left");
}

void slightRight() {
    leftMotor.setSpeed(forwardSpeed);
    rightMotor.setSpeed(forwardSpeed / 2);
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    Serial.println("Slight Right");
}

void sharpLeft() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(BACKWARD);
    rightMotor.run(FORWARD);
    delay(240);
    Serial.println("Sharp Left");
}

void sharpRight() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(FORWARD);
    rightMotor.run(BACKWARD);
    delay(240);
    Serial.println("Sharp Right");
}

void turnULeft() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(BACKWARD);
    rightMotor.run(FORWARD);
    delay(400);
    Serial.println("U-Turn to Left");
}

void turnURight() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(FORWARD);
    rightMotor.run(BACKWARD);
    delay(400); // Adjust the delay for a proper U-turn
    Serial.println("U-Turn to Right");
}

void slightLeftRotation() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(BACKWARD);
    rightMotor.run(FORWARD);
    delay(160); // Adjust the delay for a slight left rotation
    Serial.println("Slight Left Rotation");
}

void slightRightRotation() {
    leftMotor.setSpeed(turnSpeed);
    rightMotor.setSpeed(turnSpeed);
    leftMotor.run(FORWARD);
    rightMotor.run(BACKWARD);
    delay(160); // Adjust the delay for a slight right rotation
    Serial.println("Slight Right Rotation");
}

void moveBackward() {
    leftMotor.setSpeed(backwardSpeed);
    rightMotor.setSpeed(backwardSpeed);
    leftMotor.run(BACKWARD);
    rightMotor.run(BACKWARD);
    Serial.println("Move Backward");
}

void rotateOnSpot() {
    leftMotor.setSpeed(turnSpeed-20);
    rightMotor.setSpeed(turnSpeed-20);
    leftMotor.run(FORWARD);
    rightMotor.run(BACKWARD);
    delay(400); // Adjust for a small rotation
    Serial.println("Rotate on Spot");
}

void slightBackward() {
    // Set the speed for a slight backward movement
    leftMotor.setSpeed(backwardSpeed);
    rightMotor.setSpeed(backwardSpeed);

    // Run both motors in reverse for a short duration to create a slight backward movement
    leftMotor.run(BACKWARD);
    rightMotor.run(BACKWARD);

    delay(160); // Adjust the delay to control the duration of the backward movement
    Serial.println("Slight Backward Movement");
}

