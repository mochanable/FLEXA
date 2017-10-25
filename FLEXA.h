/*
  Braccio.h - board library Version 2.0
  Written by Andrea Martino and Angelo Ferrante
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

#ifndef FLEXA_h
#define FLEXA_h

#include <Arduino.h>
//#include <Servo.h>
#include "VarSpeedServo.h"

// You should set begin(SOFT_START_DISABLED) if you are using the Arm Robot shield V1.6
#define SOFT_START_DISABLED    -999

//The default value for the soft start
#define SOFT_START_DEFAULT    0

//The software PWM is connected to PIN 12. You cannot use the pin 12 if you are using
//a Braccio shield V4 or newer
#define SOFT_START_CONTROL_PIN  12

//Low and High Limit Timeout for the Software PWM
#define LOW_LIMIT_TIMEOUT 2000
#define HIGH_LIMIT_TIMEOUT 6000

class _FLEXA {
  public:
    _FLEXA();
    unsigned int begin(int soft_start_level = SOFT_START_DEFAULT);
    void modeCheck();
    void movement();
    void serial();
    // int ServoMovement(int delay, int Vbase,int Vshoulder, int Velbow, int Vwrist_ver, int Vwrist_rot, int Vgripper);
  private:
    void _softStart(int soft_start_level);
    void _softwarePWM(int high_time, int low_time);
};

extern _FLEXA FLEXA;

#endif // FLEXA_H_
