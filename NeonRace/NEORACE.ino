#include <RH_ASK.h>
#include <SPI.h>

#define RX_PIN 11
#define LED_PIN 13

int in1 = 2;
int in2 = 4;
int enA = 3;

int in3 = 5;
int in4 = 7;
int enB = 6;

int aut = 1;

RH_ASK driver;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  if (!driver.init())
    Serial.println("Initialization failed.");

}

void loop() {
  uint8_t buf[50];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';  // Null-terminate the received message

    // Parse the received message
    int xValue, yValue, potValue, buttonState;
    sscanf((char*)buf, "%d,%d,%d,%d", &xValue, &yValue, &potValue, &buttonState);

    // Print values to Serial Monitor
    Serial.print("Joystick X: ");
    Serial.print(xValue);
    Serial.print("\tJoystick Y: ");
    Serial.print(yValue);
    Serial.print("\tPotentiometer: ");
    Serial.print(potValue);
    Serial.print("\tButton State: ");
    Serial.println(buttonState);

    int motorSpeed = map(potValue, 0, 1023, 0, 255);

    // If button is pressed (buttonState == LOW), print "Button Pressed"
    if (buttonState == LOW && aut == 1) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(enA, 100);
      digitalWrite(enB, 100);
      delay(5000);

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(enA, 0);
      digitalWrite(enB, 0);
      delay(500);

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      digitalWrite(enA, 100);
      digitalWrite(enB, 100);
      delay(5000);

      aut += 1;
    }

    if (aut == 2){
      aut = 1;
      Serial.print(aut);
    }
    if ((xValue == 0)) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, motorSpeed);
    analogWrite(enB, motorSpeed);
    }

    else if ((xValue == 1023)){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, motorSpeed);
    analogWrite(enB, motorSpeed);
    }

    else if((xValue > 630 || xValue < 670)){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(enA, 0);
    digitalWrite(enB, 0);
    }
  }
}