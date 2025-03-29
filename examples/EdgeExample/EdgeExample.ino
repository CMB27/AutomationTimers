/*
  EdgeExample

  This example demonstrates how to setup and use the Edge class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will momentarily turn the built-in LED on when a button is pressed or released.
  This requires a pushbutton to be wired between pin 2 and ground.
  The button and edge values (rising, falling, and change) are displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2025-03-29
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

Edge myEdge;

const int8_t buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  myEdge.update(!digitalRead(buttonPin));
  digitalWrite(LED_BUILTIN, myEdge.change());

  Serial.print("input:");
  Serial.print(myEdge);
  Serial.print(",");
  Serial.print("rising:");
  Serial.print(myEdge.rising());
  Serial.print(",");
  Serial.print("falling:");
  Serial.print(myEdge.falling());
  Serial.print(",");
  Serial.print("change:");
  Serial.print(myEdge.change());
  Serial.println();

  delay(50);
}
