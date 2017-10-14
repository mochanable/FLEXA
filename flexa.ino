#include "Flexa.h"
#include <CapacitiveSensor.h>
#include <VarSpeedServo.h>

//=======================================mode================
int mode = 1;// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
int usNumber = 0; // 反応している超音波センサの数
int tsNumber = 0; // 反応しているタッチセンサの数
int tsDirection = 1;  // 1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
unsigned long time;
unsigned long randomPrev;//ランダム
unsigned long touchTimer;//一定時間タッチしてないともとに戻る
int touchPoint = 0; //タッチし続けると貯まるポイント
int maruPoint = 0;//丸まり続けたら元に戻る
//===========================================modeここまで================

//=======================================タッチセンサ================
CapacitiveSensor cs1 = CapacitiveSensor(52, 53);
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
int tsLimit1 = 300;//タッチセンサの閾値
int tsLimit2 = 300;
int tsLimit3 = 300;
int tsLimit4 = 300;
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
int usLimitFar = 100;//超音波センサの閾値
int usLimitNear = 80;
//===========================================超音波センサここまで================

//=======================================サーボモータ================
VarSpeedServo base;  // create servo object to control a servo
int pos1 = 90;    // variable to store the servo position
int sp1 = 20; //speed of servo
VarSpeedServo shoulder;  // create servo object to control a servo
int pos2 = 90;    // variable to store the servo position
int sp2 = 20;
VarSpeedServo elbow;  // create servo object to control a servo
int pos3 = 90;    // variable to store the servo position
int sp3 = 20;
VarSpeedServo wrist_rot;  // create servo object to control a servo
int pos4 = 90;    // variable to store the servo position
int sp4 = 20;
VarSpeedServo wrist_ver;  // create servo object to control a servo
int pos5 = 90;    // variable to store the servo position
int sp5 = 20;
VarSpeedServo gripper;  // create servo object to control a servo
int pos6 = 90;    // variable to store the servo position
int sp6 = 20;
//===========================================サーボモータここまで================

//=======================================動きアルゴリズム================
//int t = 0;
//float v = 0;
//float motorPeakPrev1 = 180;
//float motorPeakNew1 = 0;
//float motorPeakPrev2 = 0;
//float motorPeakNew2 = 180;
//float motorPeakPrev3 = 180;
//float motorPeakNew3 = 0;
//float motorPeakPrev4 = 0;
//float motorPeakNew4 = 180;
//float motorPeakPrev5 = 0;
//float motorPeakNew5 = 180;
//===========================================動きここまで================

void setup() {
  Braccio.begin();
  Serial.begin(9600);
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
  gripper.attach(3);
  //初期動作
  base.write(90);
  shoulder.write(95);
  elbow.write(82);
  wrist_rot.write(83);
  wrist_ver.write(85);
  gripper.write(90);
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

//void loop() {//=============================キャリブレーション用、ココからしたを全部コメントアウト
//  base.slowmove(90,80);
//  delay(1000);
//}

void movement() {// mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  //mode = 3;
  //  tsDirection = 1;
  if (mode == 1) { //=======================================mode1===============
    sp1 = random(10, 30);
    pos2 = 90;
    pos3 = 90;
    pos4 = 90;
    if (time % 30 <= 5) {
      if (randomPrev - time >= 50) {
        if (pos6 >= 90) {
          pos6 = random(0, 60);
        } else {
          pos6 = random(120, 180);
        }
        if (pos1 >= 90) {
          pos6 = random(160, 180);
          pos1 = random(90, 180);
        } else {
          pos6 = random(0, 30);
          pos1 = random(0, 90);
        }
        randomPrev = time;
      }
      pos5 = random(0, 20);
    }
  } else if (mode == 2) {  //=======================================mode2===============
    sp1 = 40;
    sp2 = sp3 = sp4 = sp6 = 20;
    sp5 = 60;
    int hoge = 170;
    pos2 = pos3 = pos4 = 90;
      //60度づつずらす！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    if (us1 >= 1) {
      pos1 = 0;
      pos5 = 0;
      if (us1 == 2) {//近い
        pos3 = hoge - Distance1;
      } else {//遠い
        pos3 = 90;
      }
    } else if (us2 >= 1) {
      pos1 = 120;
      pos5 = 180;
      if (us2 == 2) {
        pos3 =  180 - hoge + Distance2;
      } else {
        pos3 = 90;
      }
    } else if (us3 >= 1) {
      pos1 = 60;
      pos5 = 180;
      if (us3 == 2) {//近い
        pos3 = 180 + Distance3 - hoge;
        pos4 = hoge - Distance3;
      } else {//遠い
        pos3 = 90;
      }
    } else if (us4 >= 1) {
      pos1 = 180;
      pos5 = 0;
      if (us4 == 2) {
        pos3 = 180 - (hoge - Distance4);
        pos4 = hoge - Distance4;
      } else {
        pos3 = 90;
      }
    } else if (us5 >= 1) {
      pos1 = 120;
      pos5 = 0;
      if (us5 == 2) {
        pos3 = 180 - (hoge - Distance5);
        pos4 = hoge - Distance5;
      } else {
        pos3 = 90;
      }
    } else if (us6 >= 1) {
      pos1 = 60;
      pos5 = 0;
      if (us6 == 2) {
        pos3 = 180 - (hoge - Distance6);
        pos4 = hoge - Distance6;
      } else {
        pos3 = 90;
      }
    } else {
      //error
    }
  } else if (mode == 3) {// //==================mode3===============接触　1:北　2:東　3:南　4:西　5:北東　6:東南　7:南西　8:北西
    sp1 = sp2 = sp3 = sp4 = sp5 = sp6 = 60;
    if (tsDirection == 1) {//北・おなか
      pos2 = 130;
      pos3 = 60;
      pos4 = 70;
      if (time % 50 <= 10 && randomPrev - time >= 70) {
        pos5 = random(70, 90);
        // pos6 = random(0, 180);
        randomPrev = time;
      }
      if (time % 30 <= 10 && randomPrev - time >= 70) {
        //  pos5 = random(70, 90);
        pos6 = random(0, 180);
        randomPrev = time;
      }
    } else if (tsDirection == 2) {//東

    } else if (tsDirection == 3) {//南・せなか
      pos2 = 60;
      pos3 = 130;
      pos4 = 130;
      if (time % 50 <= 10 && randomPrev - time >= 70) {
        pos5 = random(70, 90);
        // pos6 = random(0, 180);
        randomPrev = time;
      }
      if (time % 30 <= 10 && randomPrev - time >= 70) {
        //  pos5 = random(70, 90);
        pos6 = random(0, 180);
        randomPrev = time;
      }
    } else if (tsDirection == 4) {//西

    } else if (tsDirection == 5) {//北東

    } else if (tsDirection == 6) {//東南

    } else if (tsDirection == 7) {//南西

    } else if (tsDirection == 8) {//北西

    }


  } else if (mode == 4) {//=======================================mode4===丸まる============
    sp1 = sp2 = sp3 = sp4 = sp5 = sp6 = 30;
    pos2 = 30;
    pos3 = 170;
    pos4 = 170;
    pos5 = 170;
    pos6 = 90;
    maruPoint++;
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

  base.slowmove(pos1, sp1);
  shoulder.slowmove(pos2, sp2);
  elbow.slowmove(pos3, sp3);
  wrist_rot.slowmove(pos4, sp4);
  wrist_ver.slowmove(pos5, sp5);
  gripper.slowmove(pos6, sp6);

  //  Serial.print(time % 100);
  //  Serial.print("\n");

}//movement

void modeCheck() { // mode1:通常　mode2:接近感知　mode3:接触感知　mode4:丸まる
  if ((mode == 4) && (maruPoint <= 30)) {//一定時間丸まり続ける
    mode = 4;
  } else if (mode == 4 && maruPoint >= 30) {//一定時間丸まったら、元に戻る、リセット
    mode = 1;
    maruPoint = 0;
    touchPoint = 0;
  } else  if (mode == 3 && touchPoint <= 5) {//タッチされたら
    if (time - touchTimer <= 3000) {
      mode = 3;
    } else {
      mode = 1;
    }
    if (tsNumber >= 1) {
      touchPoint++;
    }
  } else if (mode == 3 && touchPoint >= 6) {
    mode = 4;
  } else if (usNumber >= 3) { //二箇所以上から近寄られたら丸まる
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
  movement();
}//modeCheck

void loop() { //=======================================loop================================================================================================================================
  time = millis();
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
  tsVal2 = cs2.capacitiveSensor(30);
  tsVal3 = cs3.capacitiveSensor(30);
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
  delay(10);

  //  =======================================シリアルプリント================
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
  //  Serial.print(Distance5);
  //  Serial.print("cm \t");
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
  // Serial.print(time);
  //  Serial.print("\t");
  //  Serial.print(tsNumber);
  // Serial.print("\t");
  Serial.print("\t mode: \t");
  Serial.print(mode);
  Serial.print("\t P:\t");
  Serial.print(touchPoint);
  Serial.print("\t");
  //タッチ
  Serial.print("touch_value:");
  Serial.print(tsVal1);
  Serial.print(" \t");
  Serial.print(tsVal2);
  Serial.print(" \t");
  Serial.print(tsVal3);
  Serial.print(" \t");
  Serial.print(tsVal4);
  Serial.print(" \n");
  //===========================================シリアルプリントここまで================

  modeCheck();
}//loop

