Program / Source Code:
// Smart Toll Gate System using Arduino (C++)
// Components: HC-SR04, DC Motor Driver, Buzzer
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MOTOR_IN1 5
#define MOTOR_IN2 6
#define BUZZER_PIN 8
#define THRESHOLD 20   // Distance threshold in cm
// Function declarations

long getDistance();
void openGate();
void closeGate();
void buzz(int times);

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(9600);
    closeGate(); // Keep gate closed initially
}

void loop() {
    long distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
     // Vehicle detected
    if (distance > 0 && distance <= THRESHOLD) {
    Serial.println("Vehicle Detected!");
     openGate();
     buzz(2);
     delay(5000);   // Gate remains open for 5 seconds
     closeGate();
    }
delay(100);
}

// Function to measure distance using HC-SR04
long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2;
    return distance;
}

// Function to open gate
void openGate() {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    Serial.println("Gate Opened");
}
// Function to close gate
void closeGate() {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
    delay(1000);
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    Serial.println("Gate Closed");
}

// Function for buzzer sound
void buzz(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(300);
        digitalWrite(BUZZER_PIN, LOW);
        delay(300);
    }
}
