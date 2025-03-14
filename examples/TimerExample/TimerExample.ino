/*
  TimerExample

  This example demonstrates how to setup and use the Timer class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will count how long a button is pressed in milliseconds.
  This requires a pushbutton to be wired between pin 2 and ground.
  The count in milliseconds is displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

Timer timer;

const int8_t button1Pin = 2;
const int8_t button2Pin = 3;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  AutomationTimers.update();
  
  if (digitalRead(button1Pin)) timer.reset();
  //else if (timer < 4294960000) timer = 4294960000;
  if (!digitalRead(button2Pin)) timer -= 1000;

  Serial.print("timer:");
  Serial.print(timer);
  Serial.println();

  delay(50);
}
