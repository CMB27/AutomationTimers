/*
  SquareWaveExample

  This example demonstrates how to setup and use the SquareWave class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will turn the built-in LED on for one second and then off for one second, and then do it over and over again.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2025-03-22
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

const unsigned long onPeriod = 1000;
const unsigned long offPeriod = 1000;
SquareWave mySquareWave(onPeriod, offPeriod);

// alternatively
/*
const unsigned long totalPeriod = 2000;
const float dutyCycle = 0.5;
SquareWave mySquareWave(totalPeriod, dutyCycle);
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  AutomationTimers.update();
  digitalWrite(LED_BUILTIN, mySquareWave);
}
