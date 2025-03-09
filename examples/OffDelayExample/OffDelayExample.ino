/*
  OffDelayExample

  This example demonstrates how to setup and use the OffDelay class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will turn the built-in LED on when a button pressed, but wait one second to turn it off once the button is released.
  This requires a pushbutton to be wired between pin 2 and ground.
  The button input and LED output values are displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

OffDelay offDelay(1000);

const int8_t buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  AutomationTimers.updateMillis();

  bool input = !digitalRead(buttonPin);
  bool output = offDelay.update(input);

  digitalWrite(LED_BUILTIN, output);

  Serial.print("input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("output:");
  Serial.print(output);
  Serial.println();

  delay(50);
}
