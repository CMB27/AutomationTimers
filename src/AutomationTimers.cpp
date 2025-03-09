#include "AutomationTimers.h"


// Timer

unsigned long Timer::_currentMillis;

void Timer::updateMillis() {
  _currentMillis = millis();
}

unsigned long Timer::getCurrentMillis() {
  return _currentMillis;
}

void Timer::reset() {
  _startMillis = _currentMillis;
  _elapsedMillis = 0;
}

Timer::operator unsigned long() {
  if (_elapsedMillis != ULONG_MAX) {
    unsigned long tempElapsedMillis = _currentMillis - _startMillis;
    if (tempElapsedMillis < _elapsedMillis) _elapsedMillis = ULONG_MAX;
    else _elapsedMillis = tempElapsedMillis;
  }
  return _elapsedMillis;
}



// OnDelay

OnDelay::OnDelay(unsigned long delay) {
  _delay = delay;
}

bool OnDelay::update(bool input) {
  _output = false;
  if (!input) _timer.reset();
  else if (_timer >= _delay) _output = true;
  return _output;
}

OnDelay::operator bool() {
  return _output;
}



// OffDelay

OffDelay::OffDelay(unsigned long delay) {
  _delay = delay;
}

bool OffDelay::update(bool input) {
  _output = true;
  if (input) _timer.reset();
  else if (_timer >= _delay) _output = false;
  return _output;
}

OffDelay::operator bool() {
  return _output;
}



// Debounce

Debounce::Debounce(unsigned long delay) {
  _delay = delay;
}

bool Debounce::update(bool input) {
  if (input == _output) _timer.reset();
  else if (_timer >= _delay) {
    _output = input;
    _timer.reset();
  }
  return _output;
}

Debounce::operator bool() {
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
  unsigned long currentMillis = Timer::getCurrentMillis();
  unsigned long elapsedMillis = currentMillis - _startMillis;
  if (elapsedMillis > _totalPeriod) _startMillis = currentMillis - (currentMillis % _totalPeriod);
  if (elapsedMillis < _onPeriod) return true;
  return false;
}



// Edge

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



// AutomationTimersClass

void AutomationTimersClass::updateMillis() {
  Timer::updateMillis();
}

unsigned long AutomationTimersClass::getCurrentMillis() {
  return Timer::getCurrentMillis();
}