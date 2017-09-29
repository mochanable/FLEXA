/*
  FLEXA -the Flexible Anima- powered by Arduino Braccio®
  Created & Copyrighted by
    Team FLEXA
      TI:Takafumi Imai
      YM:Yusuke Maikuma
      TH:Tatsuya Hasegawa

  ver2.2 @2017_9_21 by TI
  -超音波センサくくを6つに
  -新しい台座に移植
  -ソフトボディも改良

  ver2.1 @2017_9_19 by TH
  -超音波センサーを4つに
  -向きを台座と一致させる
  →3番がたまに11cmを取ってしまう不具合あり(ハード面？)

  ver2.0  @2017_9_4  by TH,YM
  -Servo個別操作追加
  -超音波観測追加
  -方向転換・回避動作テスト追加
  -Servo個別操作とBraccio.ServoMovement()を両方使うと挙動が一部おかしくなる
  →全てをServo個別操作で行う必要がある？
  →動きを制御する関数をつくる

  ver1.1  @2017_8_31  by TI
  -Braccio.begin() , Braccio.ServoMovement()を使わずともモータを動かせるのか？
  →なかなかうまく行かない。。
  -ただ、Braccio.hとBraccio.cppをもとに、Flexa.hとFlexa.cppを作成
  →それを使ってbegin()による変な動きを排除！


  ===公式が定義しているセーフティーポジション===
  Base (M1):90 degrees
  Shoulder (M2): 45 degrees
  Elbow (M3): 180 degrees
  Wrist vertical (M4): 180 degrees
  Wrist rotation (M5): 90 degrees
  gripper (M6): 10 degrees
  ===公式===

  ===Team FLEXAが定義するセーフティーポジション===
  Base (M1):90 degrees
  Shoulder (M2): 155 degrees
  Elbow (M3): 50 degrees
  Wrist vertical (M4): 50 degrees
  Wrist rotation (M5): 45 degrees
  gripper (M6): 73 degrees
  ===Team FLEXA===

  ===Braccio.ServoMovement()とは何か？===
  公式が用意している。
    変数1:Step Delay:各サーボの動きの間のミリ秒の遅延.許容値は10〜30ミリ秒.
    M1=base degrees.許容値＝0 to 180
    M2=shoulder degrees. 許容値＝15 to 165
    M3=elbow degrees.許容値＝0 to 180
    M4=wrist vertical degrees.許容値＝0 to 180
    M5=wrist rotation degrees.許容値＝0 to 180
    M6=gripper degrees.許容値＝10 to 73. 10
  ===ServoMovement()===

  ===色々な姿勢===
  カーブした姿勢
  Braccio.ServoMovement(20, 90, 155, 50, 50, 45, 73);

  サーボが止まっても倒れない姿勢
  Braccio.ServoMovement(20, 90, 100, 155, 0, 0, 10);

  まっすぐになる姿勢
  Braccio.ServoMovement(20, 90, 96, 100, 100, 83, 73);
  ===姿勢===

*/

//#include <Braccio.h>
#include "Flexa.h"
#include <Servo.h>

//サーボモータ
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

//超音波用変数
unsigned long interval1 = 0;
unsigned long interval2 = 0;
unsigned long interval3 = 0;
unsigned long interval4 = 0;
unsigned long interval5 = 0;
unsigned long interval6 = 0;

unsigned long distance1 = 0;
unsigned long distance2 = 0;
unsigned long distance3 = 0;
unsigned long distance4 = 0;
unsigned long distance5 = 0;
unsigned long distance6 = 0;

//タッチセンサ変数
//int f = 0;
//int n = 0;

void setup() {
  //beginの呼び出し-必要
  Braccio.begin();
  Serial.begin(9600);

  //個別操作用
  base.attach(11);
  shoulder.attach(10);
  elbow.attach(9);
  wrist_rot.attach(6);
  wrist_ver.attach(5);
  gripper.attach(3);  // attaches the servo on pin 3 to the servo object

  /*超音波センサのpin
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    //  */
  //  //sensor1
  //  pinMode(22, INPUT);
  //  pinMode(23, OUTPUT);
  //  //sensor2
  //  pinMode(26, INPUT);
  //  pinMode(27, OUTPUT);
  //  //sensor3
  //  pinMode(30, INPUT);
  //  pinMode(31, OUTPUT);
  //  //sensor4
  //  pinMode(34, INPUT);
  //  pinMode(35, OUTPUT);
  //  //sensor5
  //  pinMode(38, INPUT);
  //  pinMode(39, OUTPUT);
  //  //sensor6
  //  pinMode(42, INPUT);
  //  pinMode(43, OUTPUT);

  /*
     タッチセンサーのpin
  */
  //  //touch1
  //  pinMode(46, OUTPUT);
  //  pinMode(47, INPUT);
  //  //touch2
  //  pinMode(50, OUTPUT);
  //  pinMode(51, INPUT);


  base.write(120);
  shoulder.write(96);
  elbow.write(100);
  wrist_rot.write(83);
  wrist_ver.write(100);
  gripper.write(0);
}
float t = 0;
float s1 = 0;
float s2 = 0;
float s3 = 0;
float s4 = 0;
float v = 0;
float x1 = 90;
float x2 = 90;
float x3 = 90;
float x4 = 90;

void loop() {
  //  if (t == 180) {
  //    t = 0;
  //  }
  //  if (t == 0) {
  ////    x1 = random(45, 90);
  //    //    x2 = random(45, 90);
  //    //    x3 = random(45, 90);
  //    //    x4 = random(45, 90);
  //    delay(200);
  //  }
  //  if (t == 90) {
  ////    x1 = random(0, 45);
  //    //    x2 = random(0, 45);
  //    //    x3 = random(0, 45);
  //    //    x4 = random(0, 45);
  //    delay(200);
  //  }

  v = t * PI / 180;
  s1 = 90 * (sin(v) + 1);
  gripper.write(s1);
  s2 = 60 * sin(v+PI/2) + 90 ;
  elbow.write(s2);
  s3 = 60 * sin(v+PI) + 90;
  wrist_rot.write(s3);
  s4 = 60 * sin(v+PI*3/2) + 90;
  wrist_ver.write(s4);
  t++;
  delay(10);


  //  Serial.print("t:" );
  //  Serial.print(t);
  //  Serial.print("\t");
  //  Serial.print("v:" );
  //  Serial.print(v);
  //  Serial.print("\t");
  //  Serial.print("s:" );
  //  Serial.print(s1);
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


  //  //===超音波センサに応じた動き===
  //  //sensor1
  //  digitalWrite(23, HIGH);
  //  delayMicroseconds(100);
  //  digitalWrite(23, LOW);
  //  delayMicroseconds(100);
  //  interval1 = pulseIn(22, HIGH);
  //  distance1 = interval1 * 0.017; // cm
  //
  //  //sensor2
  //  digitalWrite(27, HIGH);
  //  delayMicroseconds(100);
  //  digitalWrite(27, LOW);
  //  interval2 = pulseIn(26, HIGH);
  //  distance2 = interval2 * 0.017;
  //
  //  //sensor3
  //  delayMicroseconds(100);
  //  digitalWrite(31, HIGH);
  //  delayMicroseconds(100);
  //  digitalWrite(31, LOW);
  //  interval3 = pulseIn(30, HIGH);
  //  distance3 = interval3 * 0.017;
  //
  //  //sensor4
  //  delayMicroseconds(100);
  //  digitalWrite(35, HIGH);
  //  delayMicroseconds(100);
  //  digitalWrite(35, LOW);
  //  interval4 = pulseIn(34, HIGH);
  //  distance4 = interval4 * 0.017;
  //
  //  //  //sensor5
  //  //  delayMicroseconds(100);
  //  //  digitalWrite(39, HIGH);
  //  //  delayMicroseconds(100);
  //  //  digitalWrite(39, LOW);
  //  //  interval5 = pulseIn(38, HIGH);
  //  //  distance5 = interval5 * 0.017;
  //  //
  //  //  //sensor6
  //  //  delayMicroseconds(100);
  //  //  digitalWrite(43, HIGH);
  //  //  delayMicroseconds(100);
  //  //  digitalWrite(43, LOW);
  //  //  interval6 = pulseIn(42, HIGH);
  //  //  distance6 = interval6 * 0.017;
  //
  //  /*
  //    Serial.print(表示するもの, 小数点以下の桁数);
  //  */
  //    Serial.print("dist:");
  //    Serial.print(distance1, 4);
  //    Serial.print("cm \t");
  //    Serial.print(distance2, 4);
  //    Serial.print("cm \t");
  //    Serial.print(distance3, 4);
  //    Serial.print("cm \t");
  //    Serial.print(distance4, 4);
  ////    Serial.print("cm \t");
  //  //  Serial.print(distance5, 4);
  //  //  Serial.print("cm \t");
  //  //  Serial.print(distance6, 4);
  //   Serial.print("cm \n");
  //  //===超音波===
  //
  //  //===タッチセンサ===
  //  int a = 0;
  //  int b = 0;
  //  digitalWrite(46, HIGH);
  //  digitalWrite(50, HIGH);
  //  while (digitalRead(47) != HIGH) {
  //    a++;
  //  }
  //  while (digitalRead(51) != HIGH) {
  //    b++;
  //  }
  //  delay(1);
  //  digitalWrite(46, LOW);
  //  digitalWrite(50, LOW);
  //  f += (a - f) / 2;
  //  n += (b - n) / 2;
  //
  ////  Serial.println(f * 10);
  //
  //  //===タッチセンサ===
  //
  //
  //  //===動き===
  //  int limit1 = 10;
  //  int limit2 = 100;
  //
  //
  //
  //    if (f * 10 > 50) {
  //      gripper.write(90);
  //    } else {
  //      gripper.write(30);
  //    }
  //    if (n * 10 > 10) {
  //      gripper.write(90);
  //    } else {
  //      gripper.write(30);
  //    }
  //
  //
  //
  //  if (distance1 <= limit1) {
  //    base.write(0);
  //    gripper.write(30);
  //    wrist_ver.write(30);
  //    //    delay(1000);
  //    //      Braccio.ServoMovement(0, 90, 120, 50, 50, 45, 73);
  //  }
  //  else if (distance2 <= limit1) {
  //    base.write(60);
  //    gripper.write(30);
  //    wrist_ver.write(60);
  //    //    delay(1000);
  //    //      Braccio.ServoMovement(0, 0, 120, 50, 50, 45, 73);
  //  }
  //  else if (distance3 <= limit1) {
  //    base.write(120);
  //    gripper.write(30);
  //    wrist_ver.write(90);
  //    //        delay(1000);
  //  }
  //  else if (distance4 <= limit1) {
  //    base.write(180);
  //    gripper.write(30);
  //    //    delay(1000);
  //  }
  //  //else {
  //    //base.write(90);
  //    //    gripper.write(0);
  //    //    delay(500);
  //  //}
  //
  //  //
  //  //  else if (distance5 <= limit1) {
  //  //    base.write(60);
  //  //    gripper.write(180);
  //  //    delay(1000);
  //  //  }
  //  //  else if (distance6 <= limit1) {
  //  //    base.write(120);
  //  //    gripper.write(180);
  //  //    delay(1000);
  //  //  }
  //  //===動き===
}

