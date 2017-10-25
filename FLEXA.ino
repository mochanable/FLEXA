#include "FLEXA.h"
#include <CapacitiveSensor.h>
#include "VarSpeedServo.h"

int usLimitFar = 100;//超音波センサの閾値
int usLimitNear = 70;
int tsLimit1 = 300;//タッチセンサの閾値
int tsLimit2 = 300;
int tsLimit3 = 300;
int tsLimit4 = 300;


//=======================================mode================
//int mode = 1;// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
int usNumber = 0; // 反応している超音波センサの数
int tsNumber = 0; // 反応しているタッチセンサの数
//int tsDirection = 1;  // 1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
//unsigned long time;
//unsigned long randomPrev;//ランダム
//unsigned long touchTimer;//一定時間タッチしてないともとに戻る
//int touchPoint = 0; //タッチし続けると貯まるポイント
//int maruPoint = 0;//丸まり続けたら元に戻る
//===========================================modeここまで================

//=======================================タッチセンサ================
CapacitiveSensor cs1 = CapacitiveSensor(40, 41);
CapacitiveSensor cs2 = CapacitiveSensor(44, 45);
CapacitiveSensor cs3 = CapacitiveSensor(48, 49);
CapacitiveSensor cs4 = CapacitiveSensor(52, 53);
long tsVal1;//タッチセンサ1の値
long tsVal2;
long tsVal3;
long tsVal4;
boolean ts1 = false; //タッチセンサ1が反応してるか
boolean ts2 = false;
boolean ts3 = false;
boolean ts4 = false;
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
double Duration2 = 0; //受信した間隔
double Duration3 = 0; //受信した間隔
double Duration4 = 0; //受信した間隔
double Duration5 = 0; //受信した間隔
double Duration6 = 0; //受信した間隔
double Distance1 = 0; //距離
double Distance2 = 0; //距離
double Distance3 = 0; //距離
double Distance4 = 0; //距離
double Distance5 = 0; //距離
double Distance6 = 0; //距離
int us1 = 0; //超音波センサ1が反応しているか　　0:overLimitFar 1:FarとNearの間　2:Nearより近い
int us2 = 0;
int us3 = 0;
int us4 = 0;
int us5 = 0;
int us6 = 0;
//===========================================超音波センサここまで================

void setup() {
  FLEXA.begin();
  Serial.begin(9600);

  //=======================================タッチセンサ================
  //キャリブレーションするための時間とかそういうのだと思います。
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //===========================================タッチセンサここまで================

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

//void loop() {//=============================キャリブレーション用、ココからしたを全部コメントアウト
//  shoulder.slowmove(90, 80);
//  delay(1000);
//}

void loop() { //=======================================loop================================================================================================================================
  //=======================================超音波センサ===============
  //sensor1
  //  digitalWrite(trigPin1, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite( trigPin1, HIGH ); //超音波を出力
  //  delayMicroseconds( 10 ); //
  //  digitalWrite( trigPin1, LOW );
  //  Duration1 = pulseIn( echoPin1, HIGH ); //センサからの入力
  //  if (Duration1 > 0) {
  //    Duration1 = Duration1 / 2; //往復距離を半分にする
  //    if (Duration1 * 340 * 100 / 1000000 > 1000) {
  //      Distance1 = 1000;
  //    } else {
  //      Distance1 = Duration1 * 340 * 100 / 1000000; // 音速を340m/sに設定
  //    }
  //  }

  Distance1 = 3000;
  //sensor2
  //  digitalWrite(trigPin2, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite( trigPin2, HIGH ); //超音波を出力
  //  delayMicroseconds( 10 ); //
  //  digitalWrite( trigPin2, LOW );
  //  Duration2 = pulseIn( echoPin2, HIGH ); //センサからの入力
  //  if (Duration2 > 0) {
  //    Duration2 = Duration2 / 2; //往復距離を半分にする
  //    if (Duration2 * 340 * 100 / 1000000 > 1000) {
  //      Distance2 = 1000;
  //    } else {
  //      Distance2 = Duration2 * 340 * 100 / 1000000; // 音速を340m/sに設定
  //    }
  //  }
  Distance2 = 3000;

  //sensor3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin3, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin3, LOW );
  Duration3 = pulseIn( echoPin3, HIGH ); //センサからの入力
  if (Duration3 > 0) {
    Duration3 = Duration3 / 2; //往復距離を半分にする
    if (Duration3 * 340 * 100 / 1000000 > 1000) {
      Distance3 = 1000;
    } else {
      Distance3 = Duration3 * 340 * 100 / 1000000; // 音速を340m/sに設定
    }
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
    if (Duration4 * 340 * 100 / 1000000 > 1000) {
      Distance4 = 1000;
    } else {
      Distance4 = Duration4 * 340 * 100 / 1000000; // 音速を340m/sに設定
    }
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
    if (Duration5 * 340 * 100 / 1000000 > 1000) {
      Distance5 = 1000;
    } else {
      Distance5 = Duration5 * 340 * 100 / 1000000; // 音速を340m/sに設定
    }
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
    if (Duration6 * 340 * 100 / 1000000 > 1000) {
      Distance6 = 1000;
    } else {
      Distance6 = Duration6 * 340 * 100 / 1000000; // 音速を340m/sに設定
    }
  }

  //  Distance6 = 150;
  //=====値の処理=====
  usNumber = 0;//リセット
  us1 = us2 = us3 = us4 = us5 = us6 = 0;//リセット
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
  tsVal3 = cs2.capacitiveSensor(30);
  tsVal2 = cs3.capacitiveSensor(30);
  tsVal4 = cs4.capacitiveSensor(30);
  tsNumber = 0;//リセット
  ts1 = ts2 = ts3 = ts4 = false;//リセット
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
  //  delay(10);
  FLEXA.serial();
  FLEXA.modeCheck();
  FLEXA.movement();
}//loop

