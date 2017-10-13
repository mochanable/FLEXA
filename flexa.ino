#include "Flexa.h"
#include <Servo.h>
#include <CapacitiveSensor.h>

//=======================================mode================
int mode = 1;// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
int usNumber = 0; // 反応している超音波センサの数
int tsNumber = 0;     // 反応しているタッチセンサの数
int tsDirection = 1;  // 1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
//===========================================modeここまで================

//=======================================タッチセンサ================
CapacitiveSensor cs1 = CapacitiveSensor(36, 37);
CapacitiveSensor cs2 = CapacitiveSensor(38, 39);
CapacitiveSensor cs3 = CapacitiveSensor(40, 41);
CapacitiveSensor cs4 = CapacitiveSensor(42, 43);
long tsVal1;//タッチセンサ1の値
long tsVal2;
long tsVal3;
long tsVal4;
boolean ts1 = false; //タッチセンサ1が反応してるか
boolean ts2 = false;
boolean ts3 = false;
boolean ts4 = false;
int tsLimit1 = 600;
int tsLimit2 = 120;
int tsLimit3 = 150;
int tsLimit4 = 120;
//===========================================タッチセンサここまで================

//=======================================超音波センサ================
#define echoPin1 22 // Echo Pin
#define trigPin1 23 // Trigger Pin
#define echoPin2 24 // Echo Pin
#define trigPin2 25 // Trigger Pin
#define echoPin3 26 // Echo Pin
#define trigPin3 27 // Trigger Pin
#define echoPin4 28 // Echo Pin
#define trigPin4 29 // Trigger Pin
#define echoPin5 30 // Echo Pin
#define trigPin5 31 // Trigger Pin
#define echoPin6 32 // Echo Pin
#define trigPin6 33 // Trigger Pin
double Duration1 = 0; //受信した間隔
double Distance1 = 0; //距離
double Duration2 = 0; //受信した間隔
double Distance2 = 0; //距離
double Duration3 = 0; //受信した間隔
double Distance3 = 0; //距離
double Duration4 = 0; //受信した間隔
double Distance4 = 0; //距離
double Duration5 = 0; //受信した間隔
double Distance5 = 0; //距離
double Duration6 = 0; //受信した間隔
double Distance6 = 0; //距離
int us1 = 0; //超音波センサ1が反応しているか　　0:overLimitFar 1:FarとNearの間　2:Nearより近い
int us2 = 0;
int us3 = 0;
int us4 = 0;
int us5 = 0;
int us6 = 0;
int usLimitFar = 120;//超音波センサの閾値
int usLimitNear = 60;
//===========================================超音波センサここまで================

//=======================================サーボモータ================
Servo base;  // create servo object to control a servo
int pos1 = 90;    // variable to store the servo position
Servo shoulder;  // create servo object to control a servo
int pos2 = 90;    // variable to store the servo position
Servo elbow;  // create servo object to control a servo
int pos3 = 90;    // variable to store the servo position
Servo wrist_rot;  // create servo object to control a servo
int pos4 = 90;    // variable to store the servo position
Servo wrist_ver;  // create servo object to control a servo
int pos5 = 90;    // variable to store the servo position
//===========================================サーボモータここまで================

//=======================================動きアルゴリズム================
int t = 0;
float v = 0;
float motorPeakPrev1 = 180;
float motorPeakNew1 = 0;
float motorPeakPrev2 = 0;
float motorPeakNew2 = 180;
float motorPeakPrev3 = 180;
float motorPeakNew3 = 0;
float motorPeakPrev4 = 0;
float motorPeakNew4 = 180;
float motorPeakPrev5 = 0;
float motorPeakNew5 = 180;
//===========================================動きここまで================

void setup() {
  Braccio.begin();
  //=======================================タッチセンサ================
  //キャリブレーションするための時間とかそういうのだと思います。
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //===========================================タッチセンサここまで================

  //=======================================braccio用================
  //個別操作用
  base.attach(11);
  shoulder.attach(10);
  elbow.attach(9);
  wrist_rot.attach(6);
  wrist_ver.attach(5);

  //初期動作
  base.write(120);
  shoulder.write(96);
  elbow.write(90);
  wrist_rot.write(83);
  wrist_ver.write(100);
  //===========================================braccioここまで================

  //=========================超音波センサ_ pinMode(echoPin, INPUT); _ pinMode(trigPin, OUTPUT);========
  //sensor1
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  //sensor2
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  //sensor3
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  //sensor4
  pinMode(echoPin4, INPUT);
  pinMode(trigPin4, OUTPUT);
  //sensor5
  pinMode(echoPin5, INPUT);
  pinMode(trigPin5, OUTPUT);
  //sensor6
  pinMode(echoPin6, INPUT);
  pinMode(trigPin6, OUTPUT);
  //===========================================超音波センサここまで================
}//setup

void movement() {// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  if (mode == 1) {

  } else if (mode == 2) {
    if (us1 >= 1) {
      pos1 = 0;
      pos5 = 0;
      if (us1 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else if (us2 >= 1) {
      pos1 = 120;
      pos5 = 180;
      if (us2 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else if (us3 >= 1) {
      pos1 = 60;
      pos5 = 180;
      if (us3 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else if (us4 >= 1) {
      pos1 = 180;
      pos5 = 0;
      if (us4 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else if (us5 >= 1) {
      pos1 = 120;
      pos5 = 0;
      if (us5 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else if (us6 >= 1) {
      pos1 = 60;
      pos5 = 0;
      if (us6 == 2) {
        pos3 = 120;
      } else {
        pos3 = 90;
      }
    } else {
      //error
    }
  } else if (mode == 3) {//接触　1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
    if (tsDirection == 1) {//北

    } else if (tsDirection == 2) {//東

    } else if (tsDirection == 3) {//南

    } else if (tsDirection == 4) {//西

    } else if (tsDirection == 5) {//北東

    } else if (tsDirection == 6) {//東南

    } else if (tsDirection == 7) {//南西

    } else if (tsDirection == 8) {//北西

    }


  } else if (mode == 4) {//丸まる
    //    pos1 = 90;
    //    pos2 = 90;
    //    pos3 = 90;
    //    pos4 = 90;
    //    pos5 = 90;
  }
  //=======================================動きアルゴリズム================
  //  v = t * PI / 180;
  //  pos1 = motorPeakPrev1 + abs(motorPeakNew1 - motorPeakPrev1) * cos(v) / 2 + (motorPeakNew1 - motorPeakPrev1) / 2;
  //  pos2 = motorPeakPrev2 + abs(motorPeakNew2 - motorPeakPrev2) * cos(v) / 2 + (motorPeakNew2 - motorPeakPrev2) / 2;
  //  pos3 = motorPeakPrev3 + abs(motorPeakNew3 - motorPeakPrev3) * cos(v) / 2 + (motorPeakNew3 - motorPeakPrev3) / 2;
  //  pos4 = motorPeakPrev4 + abs(motorPeakNew4 - motorPeakPrev4) * cos(v) / 2 + (motorPeakNew4 - motorPeakPrev4) / 2;
  //  pos5 = motorPeakPrev5 + abs(motorPeakNew5 - motorPeakPrev5) * cos(v) / 2 + (motorPeakNew5 - motorPeakPrev5) / 2;
  //  t++;
  //  delay(1);
  //===========================================動きここまで================
  base.write(pos1);
  shoulder.write(pos2);
  elbow.write(pos3);
  wrist_rot.write(pos4);
  wrist_ver.write(pos5);

  if (mode == 4) {
    //delay(2000);
  }


}//movement

void modeCheck() { // mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  if (usNumber >= 2) { //二箇所以上から近寄られたら丸まる
    //mode = 4;
  } else if (tsNumber >= 1) {//タッチセンサが1つでも反応していたら
    if (tsNumber >= 3) {
      mode = 4;
    } else {
      mode = 3;
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
    }
  } else if (usNumber == 1) {//タッチセンサは反応していなくて、超音波が一つだけ反応している
    mode = 2;
  } else {//タッチセンサも超音波センサも反応していない
    mode = 1;
  }
  movement();
}//modeCheck

void loop() { //=======================================loop================================================================================================================================

  //=======================================超音波センサ===============
  //sensor1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin1, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin1, LOW );
  Duration1 = pulseIn( echoPin1, HIGH ); //センサからの入力
  if (Duration1 > 0) {
    Duration1 = Duration1 / 2; //往復距離を半分にする
    Distance1 = Duration1 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }

  //sensor2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin2, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin2, LOW );
  Duration2 = pulseIn( echoPin2, HIGH ); //センサからの入力
  if (Duration2 > 0) {
    Duration2 = Duration2 / 2; //往復距離を半分にする
    Distance2 = Duration2 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }

  //sensor3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin3, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin3, LOW );
  Duration3 = pulseIn( echoPin3, HIGH ); //センサからの入力
  if (Duration3 > 0) {
    Duration3 = Duration3 / 2; //往復距離を半分にする
    Distance3 = Duration3 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }

  //sensor4
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin4, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin4, LOW );
  Duration4 = pulseIn( echoPin4, HIGH ); //センサからの入力
  if (Duration4 > 0) {
    Duration4 = Duration4 / 2; //往復距離を半分にする
    Distance4 = Duration4 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }

  //sensor5
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin5, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin5, LOW );
  Duration5 = pulseIn( echoPin5, HIGH ); //センサからの入力
  if (Duration5 > 0) {
    Duration5 = Duration5 / 2; //往復距離を半分にする
    Distance5 = Duration5 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }

  //sensor6
  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin6, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin6, LOW );
  Duration6 = pulseIn( echoPin6, HIGH ); //センサからの入力
  if (Duration6 > 0) {
    Duration6 = Duration6 / 2; //往復距離を半分にする
    Distance6 = Duration6 * 340 * 100 / 1000000; // 音速を340m/sに設定
  }
  //=====値の処理=====
  usNumber = 0;
  us1 = us2 = us3 = us4 = us5 = us6 = 0;
  if (Distance1 <= usLimitFar) {
    if (Distance1 <= usLimitNear) {
      us1 = 2;
    } else {
      us1 = 1;
    }
    usNumber++;
  }
  if (Distance2 <= usLimitFar) {
    if (Distance2 <= usLimitNear) {
      us2 = 2;
    } else {
      us2 = 1;
    }
    usNumber++;
  }
  if (Distance3 <= usLimitFar) {
    if (Distance3 <= usLimitNear) {
      us3 = 2;
    } else {
      us3 = 1;
    }
    usNumber++;
  }
  if (Distance4 <= usLimitFar) {
    if (Distance4 <= usLimitNear) {
      us4 = 2;
    } else {
      us4 = 1;
    }
    usNumber++;
  }
  if (Distance5 <= usLimitFar) {
    if (Distance5 <= usLimitNear) {
      us5 = 2;
    } else {
      us5 = 1;
    }
    usNumber++;
  }
  if (Distance6 <= usLimitFar) {
    if (Distance6 <= usLimitNear) {
      us6 = 2;
    } else {
      us6 = 1;
    }
    usNumber++;
  }
  //===========================================超音波センサここまで================

  //===========================================タッチセンサ================
  // ここの値はノイズをとる強さ：大きくするとノイズ◯/遅い : 小さくするとノイズ◯/速い
  tsVal1 = cs1.capacitiveSensor(30);
  tsVal2 = cs2.capacitiveSensor(30);
  tsVal3 = cs3.capacitiveSensor(30);
  tsVal4 = cs4.capacitiveSensor(30);
  tsNumber = 0;
  ts1 = ts2 = ts3 = ts4 = false;
  if (tsVal1 > tsLimit1) {
    ts1 = true;
    tsNumber++;
  }
  if (tsVal2 > tsLimit2) {
    ts2 = true;
    tsNumber++;
  }
  if (tsVal3 > tsLimit3) {
    ts3 = true;
    tsNumber++;
  }
  if (tsVal4 > tsLimit4) {
    ts4 = true;
    tsNumber++;
  }
  //===========================================タッチセンサここまで================
  //放電
  delay(10);

  //  =======================================シリアルプリント================
  Serial.begin(9600);
  // 超音波
  //    Serial.print("onpa_dist:");
  //    Serial.print(Distance1);
  //    Serial.print("cm \t");
  //    Serial.print(Distance2);
  //    Serial.print("cm \t");
  //    Serial.print(Distance3);
  //    Serial.print("cm \t");
  //    Serial.print(Distance4);
  //    Serial.print("cm \t");
  //    Serial.print(Distance5);
  //    Serial.print("cm \t");
  //    Serial.print(Distance6);
  //    Serial.print("cm \n");
  //  Serial.print(us1);
  //  Serial.print("\t");
  //  Serial.print(us2);
  //  Serial.print("\t");
  //  Serial.print(us3);
  //  Serial.print("\t");
  //  Serial.print(us4);
  //  Serial.print("\t");
  //  Serial.print(us5);
  //  Serial.print("\t");
  //  Serial.print(us6);
  //  Serial.print("\t");
  Serial.print(mode);
  Serial.print("\t");
  Serial.print(tsNumber);
  Serial.print("\t");
  //  Serial.print(usNumber);
  //  Serial.print("\n");

  //タッチ
  //  Serial.print("touch_value:");
  //  Serial.print(tsVal1);
  //  Serial.print(" \t");
  //  Serial.print(tsVal2);
  //  Serial.print(" \t");
  //  Serial.print(tsVal3);
  //  Serial.print(" \t");
  //  Serial.print(tsVal4);
  //  Serial.print(" \n");
  //===========================================シリアルプリントここまで================

  modeCheck();
}//loop

