#include <Arduino.h>
#include "FLEXA.h"
#include "VarSpeedServo.h"

//=======================================mode================
int mode = 1;// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
extern int usNumber; // 反応している超音波センサの数
extern int tsNumber; // 反応しているタッチセンサの数
int tsDirection;  // 1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
unsigned long time;
unsigned long randomPrev;//最後にランダムを使った時刻
unsigned long touchTimer;//一定時間タッチしてないともとに戻る
int touchPoint = 0; //タッチし続けると貯まるポイント
int maruPoint = 0;//丸まり続けたら元に戻る
//===========================================modeここまで================

//=======================================タッチセンサ================
//CapacitiveSensor cs1 = CapacitiveSensor(52, 53);
//CapacitiveSensor cs2 = CapacitiveSensor(38, 39);
//CapacitiveSensor cs3 = CapacitiveSensor(40, 41);
//CapacitiveSensor cs4 = CapacitiveSensor(42, 43);
extern long tsVal1;//タッチセンサ1の値
extern long tsVal2;
extern long tsVal3;
extern long tsVal4;
extern boolean ts1; //タッチセンサ1が反応してるか
extern boolean ts2;
extern boolean ts3;
extern boolean ts4;
//int tsLimit1 = 300;//タッチセンサの閾値
//int tsLimit2 = 300;
//int tsLimit3 = 300;
//int tsLimit4 = 300;
//===========================================タッチセンサここまで================

//=======================================超音波センサ================
//#define echoPin1 22 // Echo Pin
//#define trigPin1 23 // Trigger Pin
//#define echoPin2 24 // Echo Pin
//#define trigPin2 25 // Trigger Pin
//#define echoPin3 26 // Echo Pin
//#define trigPin3 27 // Trigger Pin
//#define echoPin4 28 // Echo Pin
//#define trigPin4 29 // Trigger Pin
//#define echoPin5 30 // Echo Pin
//#define trigPin5 31 // Trigger Pin
//#define echoPin6 32 // Echo Pin
//#define trigPin6 33 // Trigger Pin
//double Duration1 = 0; //受信した間隔
//double Duration2 = 0; //受信した間隔
//double Duration3 = 0; //受信した間隔
//double Duration4 = 0; //受信した間隔
//double Duration5 = 0; //受信した間隔
//double Duration6 = 0; //受信した間隔
extern double Distance1; //距離
extern double Distance2; //距離
extern double Distance3; //距離
extern double Distance4; //距離
extern double Distance5; //距離
extern double Distance6; //距離
extern int us1; //超音波センサ1が反応しているか　　0:overLimitFar 1:FarとNearの間　2:Nearより近い
extern int us2;
extern int us3;
extern int us4;
extern int us5;
extern int us6;
extern int usLimitFar;//超音波センサの閾値
extern int usLimitNear;
//===========================================超音波センサここまで================

//=======================================サーボモータ================
VarSpeedServo motor1;  // create servo object to control a servo
int pos1 = 90;    // variable to store the servo position
int sp1 = 20; //speed of servo
VarSpeedServo motor2;  // create servo object to control a servo
int pos2 = 90;    // variable to store the servo position
int sp2 = 20;
VarSpeedServo motor3;  // create servo object to control a servo
int pos3 = 90;    // variable to store the servo position
int sp3 = 20;
VarSpeedServo motor4;  // create servo object to control a servo
int pos4 = 90;    // variable to store the servo position
int sp4 = 20;
VarSpeedServo motor5;  // create servo object to control a servo
int pos5 = 90;    // variable to store the servo position
int sp5 = 20;
VarSpeedServo motor6;  // create servo object to control a servo
int pos6 = 90;    // variable to store the servo position
int sp6 = 20;
//===========================================サーボモータここまで================

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

  //=======================================braccio用================
  //個別操作用
  motor1.attach(11);
  motor2.attach(10);
  motor3.attach(9);
  motor4.attach(6);
  motor5.attach(5);
  motor6.attach(3);
  //初期動作
  motor1.write(90);
  motor2.write(95);
  motor3.write(82);
  motor4.write(83);
  motor5.write(85);
  motor6.write(90);
  //===========================================braccioここまで================

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

void _FLEXA::modeCheck() {//=======================================modeCheck==============================================================================================================================
  time = millis();
  // mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  int maruPointLimit = 20;
  int touchPointLimit = 30;
  if ((mode == 4) && (maruPoint <= maruPointLimit)) {//一定時間丸まり続ける
    mode = 4;
  } else if (mode == 4 && maruPoint >= maruPointLimit) {//一定時間丸まったら、元に戻る、リセット
    mode = 1;
    maruPoint = 0;
    touchPoint = 0;
  } else  if (mode == 3 && touchPoint <= touchPointLimit) {//タッチされたら
    if (time - touchTimer <= 3000) {
      mode = 3;
    } else {
      mode = 1;
    }
    if (tsNumber >= 1) {
      touchPoint++;
    }
  } else if (mode == 3 && touchPoint >= touchPointLimit) {
    mode = 4;
  } else if (usNumber >= 2) { //二箇所以上から近寄られたら丸まる
    mode = 4;
  } else if (tsNumber >= 1) {//タッチセンサが1つでも反応していたら
    mode = 3;
    touchTimer = millis();
    if (ts1) {//タッチセンサ1が反応している
      if (ts2) {
        tsDirection = 5;//1&2→北東
      } else if (ts4) {
        tsDirection = 8;//1&4→北西
      } else {
        tsDirection = 1;//1のみ
      }
    } else if (ts2) {
      if (ts3) {
        tsDirection = 6;//2&3→南東
      } else {
        tsDirection = 2;//2のみ
      }
    } else if (ts3) {
      if (ts4) {
        tsDirection = 7;//3&4→南西
      } else {
        tsDirection = 3;//3のみ
      }
    } else if (ts4) {
      tsDirection = 4;//4のみ
    }

  } else if (usNumber == 1) {//タッチセンサは反応していなくて、超音波が一つだけ反応している
    mode = 2;
  } else if (usNumber == 0 && tsNumber == 0) { //タッチセンサも超音波センサも反応していない
    mode = 1;
  }
}

void _FLEXA::movement() {//=======================================movement================================================================================================================================
  // mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  //mode = 3;
  //  tsDirection = 1;
  if (mode == 1) { //=======================================mode1===============
    sp1 = random(10, 30);
    sp6 = 50;
    pos2 = 90;
    pos3 = 90;
    pos4 = 90;
    if (time % 30 <= 12) {
      if (randomPrev - time >= 20) {
        if (pos6 >= 90) {
          pos6 = random(0, 60);
        } else {
          pos6 = random(120, 180);
        }
        if (pos1 >= 90) {
          pos1 = random(90, 180);
        } else {
          pos1 = random(0, 90);
        }
        randomPrev = time;
      }
      pos5 = random(0, 20);
    }
  } else if (mode == 2) {  //=======================================mode2===============
    sp1 = 40;
    sp2 = sp3 = sp4 = sp6 = 20;
    sp5 = 40;
    pos2 = pos3 = pos4 = 90;
    if (us6 >= 1) {
      pos1 = 0;
      pos5 = 0;
      if (us6 == 2) {//近い
        pos3 = 90 + usLimitNear - Distance6;
        pos4 = -pos3 + 180;
      } else {//遠い
        pos3 = 90;
        pos4 = 90;
      }
    } else if (us1 >= 1) {//反転
      pos1 = 120;
      pos5 = 180;
      if (us1 == 2) {
        pos3 =  90 - usLimitNear + Distance1;
        pos4 = -pos3 + 180;
      } else {
        pos3 = 90;
        pos4 = 90;
      }
    } else if (us2 >= 1) {//反転
      pos1 = 60;
      pos5 = 180;
      if (us2 == 2) {//近い
        pos3 = 90 - usLimitNear + Distance2;
        pos4 = -pos3 + 180;
      } else {//遠い
        pos3 = 90;
        pos4 = 90;
      }
    } else if (us3 >= 1) {
      pos1 = 180;
      pos5 = 0;
      if (us3 == 2) {
        pos3 = 90 + usLimitNear - Distance3;
        pos4 = -pos3 + 180;
      } else {
        pos3 = 90;
        pos4 = 90;
      }
    } else if (us4 >= 1) {
      pos1 = 120;
      pos5 = 0;
      if (us4 == 2) {
        pos3 = 90 + usLimitNear - Distance4;
        pos4 = -pos3 + 180;
      } else {
        pos3 = 90;
        pos4 = 90;
      }
    } else if (us5 >= 1) {
      pos1 = 60;
      pos5 = 0;
      if (us5 == 2) {
        pos3 = 90 + usLimitNear - Distance5;
        pos4 = -pos3 + 180;
      } else {
        pos3 = 90;
        pos4 = 90;
      }
    } else {
      //error
    }
  } else if (mode == 3) {// //==================mode3===============接触　1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
    sp1 = sp2 = sp3 = sp4 = sp5 = sp6 = 20;
    if (tsDirection == 1) {//北・おなか
    } else if (tsDirection == 2) {//東
    } else if (tsDirection == 3) {//南・せなか
    } else if (tsDirection == 4) {//西
    } else if (tsDirection == 5) {//北東
    } else if (tsDirection == 6) {//東南
    } else if (tsDirection == 7) {//南西
    } else if (tsDirection == 8) {//北西
    }
    pos2 = 90;
    pos3 = 130;
    pos4 = 70;
    if (time % 50 <= 10 && randomPrev - time >= 70) {
      pos5 = random(70, 90);
      randomPrev = time;
    }
    if (time % 30 <= 10 && randomPrev - time >= 70) {
      pos6 = random(0, 180);
      randomPrev = time;
    }
  } else if (mode == 4) {//=======================================mode4===丸まる============
    sp1 = sp2 = sp3 = sp4 = sp5 = sp6 = 30;
    pos2 = 50;
    pos3 = 150;
    pos4 = 150;
    pos5 = 150;
    if (time % 30 <= 10 && randomPrev - time >= 70) {
      if (pos6 >= 90) {
        pos6 = random(0, 60);
      } else {
        pos6 = random(120, 180);
      }
      randomPrev = time;
    }
    maruPoint++;
  }
   sp1 = sp2 = sp3 = sp4 = sp5 = sp6 = 10;
  motor1.slowmove(pos1, sp1);
  motor2.slowmove(pos2, sp2);
  motor3.slowmove(pos3, sp3);
  motor4.slowmove(pos4, sp4);
  motor5.slowmove(pos5, sp5);
  motor6.slowmove(pos6, sp6);
}

void _FLEXA::serial() {
  Serial.print("mode:");
  Serial.print(mode);
  Serial.print("\t");
  Serial.print("usNumber:");
  Serial.print(usNumber);
  Serial.print("\t");
  Serial.print(Distance1);
  Serial.print("\t");
  Serial.print(Distance2);
  Serial.print("\t");
  Serial.print(Distance3);
  Serial.print("\t");
  Serial.print(Distance4);
  Serial.print("\t");
  Serial.print(Distance5);
  Serial.print("\t");
  Serial.print(Distance6);

  Serial.print("\t\ttsNumber:");
  Serial.print(tsNumber);
  Serial.print("\tTSVAL:");
  Serial.print(tsVal1);
  Serial.print("\t");
  Serial.print(tsVal2);
  Serial.print("\t");
  Serial.print(tsVal3);
  Serial.print("\t");
  Serial.print(tsVal4);

  Serial.print("\n");

}
