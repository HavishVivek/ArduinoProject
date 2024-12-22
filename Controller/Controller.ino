#include <RH_ASK.h>
#include <SPI.h>

#define JOYSTICK_X A1
#define JOYSTICK_Y A0
#define BUTTON_PIN 2
#define POTENTIOMETER_PIN A2
#define TX_PIN 12

RH_ASK driver;

void setup() {
  Serial.begin(9600);
  
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  if (!driver.init())
    Serial.println("Initialization failed.");
  
}

void loop() {
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);
  int potValue = analogRead(POTENTIOMETER_PIN);
  int buttonState = digitalRead(BUTTON_PIN);
  
  char message[50];
  sprintf(message, "%d,%d,%d,%d", xValue, yValue, potValue, buttonState);
  
  driver.send((uint8_t *)message, strlen(message));
  driver.waitPacketSent();
  
  delay(100);
}

