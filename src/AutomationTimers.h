#ifndef AutomationTimers_h
#define AutomationTimers_h

#include "Arduino.h"

#ifndef ULONG_MAX
#define ULONG_MAX ((unsigned long)0 - 1)
#endif

class Timer {
  public:
    static void updateMillis();
    static unsigned long getCurrentMillis();
    void reset();
    operator unsigned long();
  private:
    static unsigned long _currentMillis;
    unsigned long _startMillis = 0;
    unsigned long _elapsedMillis;
};

class OnDelay {
  public:
    OnDelay(unsigned long delay);
    bool update(bool input);
    operator bool();
  private:
    Timer _timer;
    unsigned long _delay;
    bool _output;
};

class OffDelay {
  public:
    OffDelay(unsigned long delay);
    bool update(bool input);
    operator bool();
  private:
    Timer _timer;
    unsigned long _delay;
    bool _output;
};

class Debounce {
  public:
    Debounce(unsigned long delay);
    bool update(bool input);
    operator bool();
  private:
    Timer _timer;
    unsigned long _delay;
    bool _output;
};

class SquareWave {
  public:
    SquareWave(unsigned long totalPeriod, float dutyCycle = 0.5);
    SquareWave(unsigned long onPeriod, unsigned long offPeriod);
    operator bool();
  private:
    unsigned long _totalPeriod;
    unsigned long _onPeriod;
    unsigned long _startMillis;
};

class Edge {
  public:
    void update(bool input);
    bool rising();
    bool falling();
    bool change();
  private:
    bool _currentValue;
    bool _previousValue;
};

class AutomationTimersClass {
  public:
    void updateMillis();
    unsigned long getCurrentMillis();
};

extern AutomationTimersClass AutomationTimers;

#endif