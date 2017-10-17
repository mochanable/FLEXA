/*
  Braccio.cpp - board library Version 2.0
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

#include "FLEXA.h"
//#include "VarSpeedServo.h"

//extern VarSpeedServo base;
//extern VarSpeedServo shoulder;
//extern VarSpeedServo elbow;
//extern VarSpeedServo wrist_rot;
//extern VarSpeedServo wrist_ver;
//extern VarSpeedServo gripper;
//
//extern int step_base = 90;
//extern int step_shoulder = 95;
//extern int step_elbow = 82;
//extern int step_wrist_rot = 83;
//extern int step_wrist_ver = 85;
//extern int step_gripper = 0;

_FLEXA FLEXA;

//Initialize Braccio object
_FLEXA::_FLEXA() {
}

/**
   Braccio initialization and set intial position
   Modifing this function you can set up the initial position of all the
   servo motors of Braccio
   @param soft_start_level: default value is 0 (SOFT_START_DEFAULT)
   You should set begin(SOFT_START_DISABLED) if you are using the Arm Robot shield V1.6
   SOFT_START_DISABLED disable the Braccio movements
*/
unsigned int _FLEXA::begin(int soft_start_level) {
  //Calling Braccio.begin(SOFT_START_DISABLED) the Softstart is disabled and you can use the pin 12
  if (soft_start_level != SOFT_START_DISABLED) {
    pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
    digitalWrite(SOFT_START_CONTROL_PIN, LOW);
  }

//  // initialization pin Servo motors サーボモータのピンを定義
//  base.attach(11);
//  shoulder.attach(10);
//  elbow.attach(9);
//  wrist_rot.attach(6);
//  wrist_ver.attach(5);
//  gripper.attach(3);
//
//  //For each step motor this set up the initial degree モータの初期角度を設定
//  base.write(90);
//  shoulder.write(95);
//  elbow.write(82);
//  wrist_ver.write(83);
//  wrist_rot.write(85);
//  gripper.write(0);
//  //Previous step motor position
//  step_base = 90;
//  step_shoulder = 95;
//  step_elbow = 82;
//  step_wrist_ver = 83;
//  step_wrist_rot = 85;
//  step_gripper = 0;

  if (soft_start_level != SOFT_START_DISABLED)
    _softStart(soft_start_level);
  return 1;
}

/*
  Software implementation of the PWM for the SOFT_START_CONTROL_PIN,HIGH
  @param high_time: the time in the logic level high
  @param low_time: the time in the logic level low
*/
void _FLEXA::_softwarePWM(int high_time, int low_time) {
  digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
  delayMicroseconds(high_time);
  digitalWrite(SOFT_START_CONTROL_PIN, LOW);
  delayMicroseconds(low_time);
}

/*
  This function, used only with the Braccio Shield V4 and greater,
  turn ON the Braccio softly and save it from brokes.
  The SOFT_START_CONTROL_PIN is used as a software PWM
  @param soft_start_level: the minimum value is -70, default value is 0 (SOFT_START_DEFAULT)
*/
void _FLEXA::_softStart(int soft_start_level) {
  long int tmp = millis();
  while (millis() - tmp < LOW_LIMIT_TIMEOUT)
    _softwarePWM(80 + soft_start_level, 450 - soft_start_level); //the sum should be 530usec

  while (millis() - tmp < HIGH_LIMIT_TIMEOUT)
    _softwarePWM(75 + soft_start_level, 430 - soft_start_level); //the sum should be 505usec

  digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
}
