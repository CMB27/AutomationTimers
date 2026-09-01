/*
  SquareWaveExample

  This example demonstrates how to setup and use the SquareWave class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will turn the built-in LED on for one second and then off for one second, and then do it over and over again.
  Changes to the LED status are sent to the Serial Monitor.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2026-08-31
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

const unsigned long ON_PERIOD = 1000;
const unsigned long OFF_PERIOD = 1000;
SquareWave mySquareWave(ON_PERIOD, OFF_PERIOD);

// alternatively
/*
const unsigned long TOTAL_PERIOD = 2000;
const float DUTY_CYCLE = 0.5;
SquareWave mySquareWave(TOTAL_PERIOD, DUTY_CYCLE);
*/

Edge myEdge;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  AutomationTimers.update();
  digitalWrite(LED_BUILTIN, mySquareWave);

  myEdge.update(mySquareWave);
  
  if (myEdge.change()) {
    Serial.print("time:");
    Serial.print(AutomationTimers.getCurrentMillis());
    Serial.print(",");
    Serial.print("output:");
    Serial.print(mySquareWave);
    Serial.println();
  }

  // This delay is not needed.
  // It introduces some timing error.
  // It is included here to show that the error does not accumulate.
  delay(3);
}
