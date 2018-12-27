/*
  Oneshot.h - Interrupt driven Oneshot library for Esp8266 using timers
  Original Copyright (c) 2015 Michael C. Miller. All right reserved.

  < dec 23 2018 > modified for Oneshot125 ESC's by Andreotti

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  */


//   A Oneshot is activated by creating an instance of the Oneshot class passing
//   the desired pin to the attach() method.
//   The Oneshots are pulsed in the background using the value most recently
//   written using the write() method.
//
//   The methods are:
//
//   Oneshot - Class for manipulating Oneshot ESC's connected to ESP8266 pins.
//
//   attach(pin )  - Attaches a Oneshot motor to an i/o pin.
//   write()       - Sets the Oneshot angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
//   writeMicroseconds() - Sets the Oneshot pulse width in microseconds
//   attached()    - Returns true if there is a Oneshot attached.
//   detach()      - Stops an attached Oneshots from pulsing its i/o pin.
  

#ifndef Oneshot125_h
#define Oneshot125_h

#include <Arduino.h>

#define MIN_PULSE_WIDTH      1000     // the shortest pulse from transmitter
#define MAX_PULSE_WIDTH      2000     // the longest pulse from transmitter 
#define ONESHOT_MIN          125      // the shortest pulse sent to a ESC
#define ONESHOT_MAX          250      // the longest pulse sent to a ESC
#define ONESHOT_REFRESH      1000     // minumim time to refresh Oneshots in microseconds 

#if !defined(ESP8266)

#error "This library only supports esp8266 boards."

#endif

class Oneshot
{
public:
    Oneshot();
    ~Oneshot();
    uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
    void detach();
    void write(int value);             // value between 1000 and 2000, otherwise as pulse width in microseconds 
    void writeMicroseconds(int value); // Write pulse width in microseconds 
    bool attached();                   // return true if this Oneshot is attached, otherwise false 
private:
    bool     _attached;
    uint8_t  _pin;
    uint16_t _valueUs;
};

#endif
