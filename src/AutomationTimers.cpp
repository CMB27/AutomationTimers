#include "AutomationTimers.h"


// AutomationTimersClass

unsigned long AutomationTimersClass::_currentMillis;

void AutomationTimersClass::update() {
  _currentMillis = millis();
}

unsigned long AutomationTimersClass::getCurrentMillis() {
  return _currentMillis;
}



// Timer

Timer::operator unsigned long() {
  if (_elapsedMillis != ULONG_MAX) {
    unsigned long tempElapsedMillis = _currentMillis - _startMillis;
    if (tempElapsedMillis < _elapsedMillis) _elapsedMillis = ULONG_MAX;
    else _elapsedMillis = tempElapsedMillis;
  }
  return _elapsedMillis;
}

void Timer::reset() {
  _elapsedMillis = 0;
  _startMillis = _currentMillis;
}

void Timer::set(unsigned long setMillis) {
  _elapsedMillis = setMillis;
  _startMillis = _currentMillis - _elapsedMillis;
}



// DigitalTimerProcess

void DigitalTimerProcess::setDelay(unsigned long delay) {
  _delay = delay;
}



// OnDelay

OnDelay::OnDelay(unsigned long delay) {
  setDelay(delay);
}

bool OnDelay::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _firstRun = false;
  }
  _output = false;
  if (!input) _timer.reset();
  else if (_timer >= _delay) _output = true;
  return _output;
}



// OffDelay

OffDelay::OffDelay(unsigned long delay) {
  setDelay(delay);
}

bool OffDelay::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _firstRun = false;
  }
  _output = true;
  if (input) _timer.reset();
  else if (_timer >= _delay) _output = false;
  return _output;
}



// Debounce

Debounce::Debounce(unsigned long delay) {
  setDelay(delay);
}

bool Debounce::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _output = input;
    _firstRun = false;
  }
  if (input == _output) _timer.reset();
  else if (_timer >= _delay) {
    _output = input;
    _timer.reset();
  }
  return _output;
}



// SquareWave

SquareWave::SquareWave(unsigned long totalPeriod, float dutyCycle) {
  _totalPeriod = totalPeriod;
  if (dutyCycle > 1.0) dutyCycle = 1.0;
  if (dutyCycle < 0.0) dutyCycle = 0.0;
  _onPeriod = (unsigned long)((float)_totalPeriod * dutyCycle);
}

SquareWave::SquareWave(unsigned long onPeriod, unsigned long offPeriod) {
  _onPeriod = onPeriod;
  _totalPeriod = _onPeriod + offPeriod;
}

SquareWave::operator bool() {
  unsigned long elapsedMillis = _currentMillis - _startMillis;
  if (elapsedMillis > _totalPeriod) _startMillis = _currentMillis - (_currentMillis % _totalPeriod);
  if (elapsedMillis < _onPeriod) return true;
  return false;
}



// Edge

Edge::operator bool() {
  return _currentValue;
}

void Edge::update(bool input) {
  _previousValue = _currentValue;
  _currentValue = input;
}

bool Edge::rising() {
  if (_currentValue > _previousValue) return true;
  return false;
}

bool Edge::falling() {
  if (_currentValue < _previousValue) return true;
  return false;
}

bool Edge::change() {
  if (_currentValue != _previousValue) return true;
  return false;
}



// LinearRamp

LinearRamp::LinearRamp(float rate) {
  setRate(rate);
}

LinearRamp::operator float() {
  return _output;
}

float LinearRamp::update(float input) {
  if (input != _target) {
    _target = input;
    _start = _output;
    float deltaUnits = _target - _start;
    if (deltaUnits < 0.0) deltaUnits = deltaUnits * -1.0;
    _deltaMilliseconds = deltaUnits / _rate;
    _timer.reset();
  }
  if (_timer < _deltaMilliseconds) {
    if (_target > _start) _output = _rate * _timer + _start;
    else _output = -_rate * _timer + _start;
  }
  else _output = _target;
  return _output;
}

void LinearRamp::setRate(float rate) {
  if (rate < 0.0) rate = rate * -1.0;
  if (rate != 0.0) _rate = rate;
}



// Instantiate AutomationTimers
AutomationTimersClass AutomationTimers;
