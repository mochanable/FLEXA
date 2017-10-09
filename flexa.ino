#include "Flexa.h"
#include <Servo.h>
#include<CapacitiveSensor.h>

//=======================================サーボモータ================
Servo base;  // create servo object to control a servo
int pos1 = 0;    // variable to store the servo position
Servo shoulder;  // create servo object to control a servo
int pos2 = 0;    // variable to store the servo position
Servo elbow;  // create servo object to control a servo
int pos3 = 0;    // variable to store the servo position
Servo wrist_rot;  // create servo object to control a servo
int pos4 = 0;    // variable to store the servo position
Servo wrist_ver;  // create servo object to control a servo
int pos5 = 0;    // variable to store the servo position
Servo gripper;  // create servo object to control a servo
int pos6 = 0;    // variable to store the servo position
//===========================================ここまで================

//=======================================タッチセンサ================
CapacitiveSensor cs1 = CapacitiveSensor(36, 37);
CapacitiveSensor cs2 = CapacitiveSensor(38, 39);
CapacitiveSensor cs3 = CapacitiveSensor(40, 41);
CapacitiveSensor cs4 = CapacitiveSensor(42, 43);
CapacitiveSensor cs5 = CapacitiveSensor(44, 45);
CapacitiveSensor cs6 = CapacitiveSensor(46, 47);
//===========================================ここまで================

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
//===========================================ここまで================


//=======================================動きアルゴリズム================
//int t = 0;
//float v = 0;

//float motor1 = 0;
//float motorPeakPrev1 = 180;
//float motorPeakNew1 = 0;
//float motor2 = 0;
//float motorPeakPrev2 = 0;
//float motorPeakNew2 = 180;
//float motor3 = 0;
//float motorPeakPrev3 = 180;
//float motorPeakNew3 = 0;
//float motor4 = 0;
//float motorPeakPrev4 = 0;
//float motorPeakNew4 = 180;

//int angle1 = 45;
//int angle2 = 90;
//int angle3 = 90;
//int angle4 = 135;
//===========================================ここまで================

void setup() {
  Braccio.begin();
  Serial.begin(9600);

  //=======================================タッチセンサ================
  //キャリブレーションするための時間とかそういうのだと思います。
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //===========================================ここまで================

  //=======================================braccio用================
  //個別操作用
  base.attach(11);
  shoulder.attach(10);
  elbow.attach(9);
  wrist_rot.attach(6);
  wrist_ver.attach(5);
  gripper.attach(3);

  //初期動作
  base.write(120);
  shoulder.write(96);
  elbow.write(100);
  wrist_rot.write(83);
  wrist_ver.write(100);
  gripper.write(0);
  //===========================================ここまで================

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
  //===========================================ここまで================


}


void loop() {

  //=======================================動きアルゴリズム================

  //  if (t == 361) {
  //    t = 1;
  //  }
  //
  //
  //  v = t * PI / 180;
  //  motor1 = motorPeakPrev1 + abs(motorPeakNew1 - motorPeakPrev1) * cos(v) / 2 + (motorPeakNew1 - motorPeakPrev1) / 2;
  //  gripper.write(motor1);
  //  motor2 = 180 - (motorPeakPrev2 + abs(motorPeakNew2 - motorPeakPrev2) * cos(v) / 2 + (motorPeakNew2 - motorPeakPrev2) / 2);
  //  wrist_ver.write(motor2);
  //  motor3 = motorPeakPrev3 + abs(motorPeakNew3 - motorPeakPrev3) * cos(v) / 2 + (motorPeakNew3 - motorPeakPrev3) / 2;
  //  wrist_rot.write(motor3);
  //  motor4 = 180 - (motorPeakPrev4 + abs(motorPeakNew4 - motorPeakPrev4) * cos(v) / 2 + (motorPeakNew4 - motorPeakPrev4) / 2);
  //  elbow.write(motor4);
  //  t++;
  //  delay(1);


  //  Serial.print("t:" );
  //  Serial.print(t);
  //  Serial.print("\t");
  //  Serial.print("v:" );
  //  Serial.print(v);
  //  Serial.print("\t");
  //  Serial.print("Prev:" );
  //  Serial.print(motorPeakPrev1);
  //  Serial.print("\t");
  //  Serial.print("New:" );
  //  Serial.print(motorPeakNew1);
  //  Serial.print("\t");
  //  Serial.print("motor:" );
  //  Serial.print(motor1);
  //  Serial.print("\n");

  //  base.write(120);
  //  shoulder.write(90);
  //  elbow.write(100);
  //  wrist_rot.write(83);
  //  wrist_ver.write(100);
  //  gripper.write(0);
  //  delay(300);
  //
  //  base.write(120);
  //  shoulder.write(96);
  //  elbow.write(80);
  //  wrist_rot.write(103);
  //  wrist_ver.write(70);
  //  gripper.write(0);
  //  delay(300);
  //
  //  base.write(120);
  //  shoulder.write(96);
  //  elbow.write(120);
  //  wrist_rot.write(63);
  //  wrist_ver.write(130);
  //  gripper.write(0);
  //  delay(300);
  //===========================================ここまで================


  //=======================================超音波センサ================
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

  //  //sensor5
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

  //  //sensor6
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


  int limit1 = 10;
  int limit2 = 100;
  //===========================================ここまで================


  //=======================================タッチセンサ================
  // ここの値はノイズをとる強さ：大きくするとノイズ◯/遅い : 小さくするとノイズ◯/速い
  long val1 = cs1.capacitiveSensor(30);
  long val2 = cs2.capacitiveSensor(30);
  long val3 = cs3.capacitiveSensor(30);
  long val4 = cs4.capacitiveSensor(30);
  long val5 = cs5.capacitiveSensor(30);
  long val6 = cs6.capacitiveSensor(30);
  //===========================================ここまで================

  //=======================================センサに応じた動きの指示================

  //=====超音波パート=====
  if (Distance1 <= limit1) {
    base.write(0);
    gripper.write(0);

    //wrist_ver.write(30);
    delay(1000);
  }
  else if (Distance6 <= limit1) {
    base.write(60);
    gripper.write(0);

    //wrist_ver.write(60);
    delay(1000);
  }
  else if (Distance5 <= limit1) {
    base.write(120);
    gripper.write(0);

    //wrist_ver.write(90);
    delay(1000);
  }
  else if (Distance4 <= limit1) {
    base.write(180);
    gripper.write(0);

    delay(1000);
  }
  else if (Distance3 <= limit1) {
    base.write(60);
    gripper.write(180);

    delay(1000);
  }
  else if (Distance2 <= limit1) {
    base.write(120);
    gripper.write(180);

    delay(1000);
  }
  //  else {
  //    base.write(90);
  //    gripper.write(180);
  //
  //    delay(500);
  //  }
  //=====ここまで=====

  //=====タッチパート=====
  if (val1 > 100) {
    gripper.write(50);
  }
  else if (val2 > 100) {
    gripper.write(60);
  }
  else if (val3 > 100) {
    gripper.write(80);
  }
  else if (val4 > 100) {
    gripper.write(100);
  }
  else if (val5 > 100) {
    gripper.write(120);
  }
  else if (val6 > 100) {
    gripper.write(140);
  }
  //=====ここまで=====


  //===========================================ここまで================

  //放電
  delay(10);


  //=======================================シリアルプリント================
  //音波
  Serial.print("onpa_dist:");
  Serial.print(Distance1);
  Serial.print("cm \t");
  Serial.print(Distance2);
  Serial.print("cm \t");
  Serial.print(Distance3);
  Serial.print("cm \t");
  Serial.print(Distance4);
  Serial.print("cm \t");
  Serial.print(Distance5);
  Serial.print("cm \t");
  Serial.print(Distance6);
  Serial.print("cm \n");

  //タッチ
  Serial.print("touch_value:");
  Serial.print(val1);
  Serial.print(" \t");
  Serial.print(val2);
  Serial.print(" \t");
  Serial.print(val3);
  Serial.print(" \t");
  Serial.print(val4);
  Serial.print(" \t");
  Serial.print(val5);
  Serial.print(" \t");
  Serial.println(val6);
  Serial.print(" \n");


}
