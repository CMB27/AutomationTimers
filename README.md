# AutomationTimers
This is an Arduino library for managing event timing.
It provides *relatively* intuitive tools for creating non-blocking timing events in your code.

This library consists of a collection of classes:
- `Timer`: counts up in milliseconds, can be reset
- `OnDelay`: turns an output on a set number of milliseconds after an input is turned on.
- `OffDelay`: turns an output off a set number of milliseconds after an input is turned off.
- `Debounce`: is essentially a combination of both `OnDelay` and `OffDelay`; it can be used to debounce an input.
- `SquareWave`: generates a square wave with a set period and duty cycle.
- `Edge`: detects the rising and falling edge of an input.
- `LinearRamp`: a software linear ramp generator.



## Compatibility
This library should work on any microcontroller board.
It relies on [millis()](https://docs.arduino.cc/language-reference/en/functions/time/millis/) and [abs()](https://docs.arduino.cc/language-reference/en/functions/math/abs/) from the Arduino API/Language, but has no other dependencies.



## Examples
- [TimerExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/TimerExample/TimerExample.ino)
- [OnDelayExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/OnDelayExample/OnDelayExample.ino)
- [OffDelayExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/OffDelayExample/OffDelayExample.ino)
- [DebounceExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/DebounceExample/DebounceExample.ino)
- [SquareWaveExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/SquareWaveExample/SquareWaveExample.ino)
- [EdgeExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/EdgeExample/EdgeExample.ino)
- [LinearRampExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/LinearRampExample/LinearRampExample.ino)



## Method

<details><summary id="automationtimers-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the time for all classes in this library except `Edge`.
`Edge` is event based, not time based.
This is usually run once at the beginning of `loop()`.

### Syntax
`AutomationTimers.update()`

### Example
``` C++
#include <AutomationTimers.h>

void setup() {
  // run setup stuff here
}

void loop() {
  AutomationTimers.update();
  // run other loop stuff here
}
```
</blockquote></details>





## Classes



<details><summary id="timer"><strong>Timer</strong></summary><blockquote>

### Description
A `Timer` object acts like a read-only `unsigned long` that always counts up in milliseconds.
It can be reset to 0 using the `reset()` method.

The value of the `Timer` is prevented from overflowing; once the timer reaches the highest value an `unsigned long` can hold, it will stay there until reset.

### Example
``` C++
#include <AutomationTimers.h>

Timer myTimer;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  // AutomationTimers.update() is what actually updates the timer value.
  // It should be run once per loop.
  // It only needs to be run once, even when using multiple Timer objects.
  AutomationTimers.update();
  
  // If pin 2 is HIGH, the timer will be reset to 0, so the timer only counts up when pin 2 is LOW.
  if (digitalRead(2)) myTimer.reset();

  // This will print the timer value in milliseconds.
  Serial.println(myTimer);

  delay(50);
}
```

### Methods

<details><summary id="timer-constructor"><strong>Timer</strong> <em>constructor</em></summary><blockquote>

### Description
Creates a `Timer` object.

### Example
``` C++
Timer myTimer;
```

</blockquote></details>

<details><summary id="timer-operator"><strong>Timer</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the timer in milliseconds.

### Returns
Data type: `unsigned long`.

### Example
``` C++
if (myTimer >= 2000) {
  // do something
}
```

</blockquote></details>

<details><summary id="timer-reset"><strong>reset()</strong></summary><blockquote>

### Description
Resets the timer to 0.

### Example
``` C++
if (myTimer >= 2000) {
  myTimer.reset();
  // do something else
}
```

</blockquote></details>


### Note
`Timer` is utilized in the `OnDelay`, `OffDelay`, `Debounce`, and `LinearRamp` classes.

</blockquote></details>





<details><summary id="ondelay"><strong>OnDelay</strong></summary><blockquote>

### Description

```
INPUT:  ___/""""""""""""""""""\___
           |
OUTPUT: ___|_________/""""""""\___
           |         |
           |<-DELAY->|
```


### Methods

<details><summary id="ondelay-constructor"><strong>OnDelay</strong> <em>constructor</em></summary><blockquote>

### Description
Creates an `OnDelay` object.

### Syntax
`OnDelay(delay)`

### Parameter
`delay`: the delay in milliseconds to wait before setting the output `true`. Allowed data type: `unsigned long`.

### Example
``` C++
OnDelay myOnDelay(1000);
```

</blockquote></details>

<details><summary id="ondelay-operator"><strong>OnDelay</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
Data type: `bool`.

### Example
``` C++
if (myOnDelay) {
  // do something
}
```

</blockquote></details>

<details><summary id="ondelay-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of an `OnDelay` object.

### Syntax
`myOnDelay.update(input)`

### Parameters
- `myOnDelay`: an `OnDelay` object.
- `input`: Allowed data type `bool`.

### Returns
The value of the output. Data type: `bool`.  
*Reading the output is optional.*

</blockquote></details>

<details><summary id="ondelay-setDelay"><strong>setDelay()</strong></summary><blockquote>

### Description
Changes the delay of an `OnDelay` object.

### Syntax
`myOnDelay.setDelay(delay)`

### Parameters
- `myOnDelay`: an `OnDelay` object.
- `delay`: the delay in milliseconds to wait before setting the output `true`. Allowed data type: `unsigned long`.

</blockquote></details>


</blockquote></details>





<details><summary id="offdelay"><strong>OffDelay</strong></summary><blockquote>

### Description

```
INPUT:  ___/""""""""\_____________
                    |
OUTPUT: ___/""""""""|"""""""""\___
                    |         |
                    |<-DELAY->|
```


### Methods

<details><summary id="offdelay-constructor"><strong>OffDelay</strong> <em>constructor</em></summary><blockquote>

### Description
Creates an `OffDelay` object.

### Syntax
`OffDelay(delay)`

### Parameter
`delay`: the delay in milliseconds to wait before setting the output `false`. Allowed data type: `unsigned long`.

### Example
``` C++
OffDelay myOffDelay(1000);
```

</blockquote></details>

<details><summary id="offdelay-operator"><strong>OffDelay</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
Data type: `bool`.

### Example
``` C++
if (myOffDelay == false) {
  // do something
}
```

</blockquote></details>

<details><summary id="offdelay-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of an `OffDelay` object.

### Syntax
`myOffDelay.update(input)`

### Parameter
- `myOffDelay`: an `OffDelay` object.
- `input`: Allowed data type `bool`.

### Returns
The value of the output. Data type: `bool`.  
*Reading the output is optional.*

</blockquote></details>

<details><summary id="offdelay-setDelay"><strong>setDelay()</strong></summary><blockquote>

### Description
Changes the delay of an `OffDelay` object.

### Syntax
`myOffDelay.setDelay(delay)`

### Parameters
- `myOffDelay`: an `OffDelay` object.
- `delay`: the delay in milliseconds to wait before setting the output `false`. Allowed data type: `unsigned long`.

</blockquote></details>


</blockquote></details>





<details><summary id="debounce"><strong>Debounce</strong></summary><blockquote>

### Description

```
INPUT:  ___/""""""""""""""""""\_____________
           |                  |
OUTPUT: ___|_________/""""""""|"""""""""\___
           |         |        |         |
           |<-DELAY->|        |<-DELAY->|
```


### Methods

<details><summary id="debounce-constructor"><strong>Debounce</strong> <em>constructor</em></summary><blockquote>

### Description
Creates a `Debounce` object.

### Syntax
`Debounce(delay)`

### Parameter
`delay`: the delay in milliseconds to wait before setting the output `true` and the delay to wait before setting the output `false`. Allowed data type: `unsigned long`.

### Example
``` C++
Debounce myDebounce(1000);
```

</blockquote></details>

<details><summary id="debounce-operator"><strong>Debounce</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
Data type: `bool`.

### Example
``` C++
if (myDebounce) {
  // do something
}
```

</blockquote></details>

<details><summary id="debounce-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of an `Debounce` object.

### Syntax
`myDebounce.update(input)`

### Parameters
- `myDebounce`: a `Debounce` object.
- `input`: Allowed data type `bool`.

### Returns
The value of the output. Data type: `bool`.  
*Reading the output is optional.*

</blockquote></details>

<details><summary id="debounce-setDelay"><strong>setDelay()</strong></summary><blockquote>

### Description
Changes the delay of an `Debounce` object.

### Syntax
`myDebounce.setDelay(delay)`

### Parameters
- `myDebounce`: a `Debounce` object.
- `delay`: the delay in milliseconds to wait before setting the output `true` and the delay to wait before setting the output `false`. Allowed data type: `unsigned long`.

</blockquote></details>


</blockquote></details>





<details><summary id="squarewave"><strong>SquareWave</strong></summary><blockquote>

### Description
Generates a square wave.

```
OUTPUT: ___/"""""""""""""\______________/"""
           |             |              |
           |<-ON PERIOD->|<-OFF PERIOD->|
           |                            |
           |<-------TOTAL PERIOD------->|
```
$`dutyCycle=\frac{onPeriod}{totalPeriod}`$


### Methods

<details><summary id="SquareWave-constructor"><strong>SquareWave</strong> <em>constructor</em></summary><blockquote>

### Description
Creates an `SquareWave` object.

### Syntax
- `SquareWave(totalPeriod, dutyCycle)`
- `SquareWave(onPeriod, offPeriod)`

### Parameters
- `totalPerid`: the total period of the square wave in milliseconds. Allowed data type: `unsigned long`.
- `dutyCycle`: the duty cycle of the squate wave. This should be less than `1` and greater than `0`. Allowed data type: `float`.
- `onPerid`: the period square wave is `true`/`HIGH` in milliseconds. Allowed data type: `unsigned long`.
- `offPerid`: the period square wave is `false`/`LOW` in milliseconds. Allowed data type: `unsigned long`.

### Example
``` C++
SquareWave myFirstSquareWave(2000, 0.5);
SquareWave mySecondSquareWave(1000, 1000);
```

</blockquote></details>

<details><summary id="SquareWave-operator"><strong>SquareWave</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
Data type: `bool`.

### Example
``` C++
digitalWrite(LED_BUILTIN, mySquareWave);
```

</blockquote></details>


</blockquote></details>





<details><summary id="edge"><strong>Edge</strong></summary><blockquote>

### Description

```
INPUT:   ___/""""""""""\____
RISING:  ___/\______________
FALLING: ______________/\___
CHANGE:  ___/\_________/\___
```


### Methods

<details><summary id="edge-constructor"><strong>Edge</strong> <em>constructor</em></summary><blockquote>

### Description
Creates a `Edge` object.

### Example
``` C++
Edge myEdge;
```

</blockquote></details>

<details><summary id="Edge-operator"><strong>Edge</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the input.

### Returns
Data type: `bool`.

### Example
``` C++
bool input = myEdge;
```

</blockquote></details>

<details><summary id="edge-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of an `Edge` object.

### Syntax
`myEdge.update(input)`

### Parameters
- `myEdge`: an `Edge` object.
- `input`: Allowed data type `bool`.

### Returns
Nothing

</blockquote></details>

<details><summary id="edge-rising"><strong>rising()</strong></summary><blockquote>

### Description
Returns `true` when a rising edge is detected on the input.

### Syntax
`myEdge.rising()`

### Parameter
`myEdge`: an `Edge` object.

### Returns
Data type: `bool`.

</blockquote></details>

<details><summary id="edge-falling"><strong>falling()</strong></summary><blockquote>

### Description
Returns `true` when a falling edge is detected on the input.

### Syntax
`myEdge.falling()`

### Parameter
`myEdge`: an `Edge` object.

### Returns
Data type: `bool`.

</blockquote></details>

<details><summary id="edge-change"><strong>change()</strong></summary><blockquote>

### Description
Returns `true` when a change is detected on the input.

### Syntax
`myEdge.change()`

### Parameter
`myEdge`: an `Edge` object.

### Returns
Data type: `bool`.

</blockquote></details>

</blockquote></details>





<details><summary id="linearramp"><strong>LinearRamp</strong></summary><blockquote>

### Description

```
            |""""""""""""|
INPUT:  ____|            |             _______
                         |            |
            |            |____________|
            |
            |            |            |
            |            |            |
            |                         |
            | /"""""""""""\           |
OUTPUT: _____/             \          |  _____
                            \         | /
                             \_________/
```

### Methods

<details><summary id="linearramp-constructor"><strong>LinearRamp</strong> <em>constructor</em></summary><blockquote>

### Description
Creates a `LinearRamp` object.

### Syntax
`LinearRamp(rate)`

### Parameter
`rate`: the inital ramp rate in units per millisecond. Allowed data type: `float`.

### Example
``` C++
LinearRamp myRamp(0.1);
```

</blockquote></details>

<details><summary id="linearramp-operator"><strong>LinearRamp</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
Data type: `long`.

### Example
``` C++
long output = myRamp;
```

</blockquote></details>

<details><summary id="linearramp-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of a `LinearRamp` object.

### Syntax
`myRamp.update(input)`

### Parameters
- `myRamp`: a `LinearRamp` object.
- `input`: the target value to ramp to. Allowed data type `long`.

### Returns
Returns the value of the output. Data type: `long`.  
*Reading the output is optional.*

</blockquote></details>

<details><summary id="linearramp-setrate"><strong>setRate()</strong></summary><blockquote>

### Description
sets the ramp rate in units per millisecond of a `LinearRamp` object.

### Syntax
`myRamp.setRate(rate)`

### Parameters
- `myRamp`: a `LinearRamp` object.
- `rate`: the ramp rate. Allowed data type: `float`.

</blockquote></details>


</blockquote></details>