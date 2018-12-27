/*
Oneshot library using shared TIMER1 infrastructure

Original Copyright (c) 2015 Michael C. Miller. All right reserved.

< dec 23 2018 > modified for Oneshot125 ESC's by Andreotti

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#if defined(ESP8266)

#include <Arduino.h>
#include <Oneshot125.h>
#include "core_esp8266_waveform.h"

//-------------------------------------------------------------------
// Oneshot class methods

Oneshot::Oneshot()
{
  _attached = false;
  _valueUs = MIN_PULSE_WIDTH; // DEFAULT_PULSE_WIDTH;
}

Oneshot::~Oneshot()
{
  detach();
}


uint8_t Oneshot::attach(int pin)
{
  if (!_attached)
  {
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);
    _pin = pin;
    _attached = true;
  }

  write(_valueUs);
  return pin;
}

void Oneshot::detach()
{
  if (_attached)
  {
    stopWaveform(_pin);
    _attached = false;
    digitalWrite(_pin, LOW);
  }
}

void Oneshot::write(int value)
{
  value = constrain(value, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  value = map(value, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, ONESHOT_MIN, ONESHOT_MAX);
  writeMicroseconds(value);
}

void Oneshot::writeMicroseconds(int value)
{
  _valueUs = value;
  if (_attached)
	startWaveform(_pin, _valueUs, ONESHOT_REFRESH - _valueUs, 0);
}

bool Oneshot::attached()
{
  return _attached;
}

#endif
