/*
  FLEXA -the Flexible Anima- powered by Arduino Braccio®
  Created & Copyrighted by
    Team FLEXA 
      TI:Takafumi Imai
      YM:Yusuke Maikuma
      TH:Tatsuya Hasegawa
             
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

//タッチセンサー用変数
//int f = 0;

//超音波用変数
unsigned long interval1 = 0;
unsigned long interval2 = 0;
unsigned long interval3 = 0;
unsigned long distance1 = 0;
unsigned long distance2 = 0;
unsigned long distance3 = 0;

void setup() {
  Braccio.begin();
  //  Serial.begin(9600);

  //個別操作用
  base.attach(11);
  shoulder.attach(10);
  elbow.attach(9);
  wrist_rot.attach(6);
  wrist_ver.attach(5);
  gripper.attach(3);  // attaches the servo on pin 3 to the servo object

  //超音波センサのpin
  pinMode(22, OUTPUT);
  pinMode(23, INPUT);
  //sensor2
  pinMode(24, OUTPUT);
  pinMode(25, INPUT);
  //sensor3
  pinMode(26, OUTPUT);
  pinMode(27, INPUT);
}

void loop() {
  //===超音波センサ===
  //sensor1
  digitalWrite(22, HIGH);
  delayMicroseconds(100);
  digitalWrite(22, LOW);
  delayMicroseconds(100);
  interval1 = pulseIn(23, HIGH);
  distance1 = interval1 * 0.017; // cm

  //sensor2
  digitalWrite(24, HIGH);
  delayMicroseconds(100);
  digitalWrite(24, LOW);
  interval2 = pulseIn(25, HIGH);
  distance2 = interval2 * 0.017;

  //sensor3
  delayMicroseconds(100);
  digitalWrite(26, HIGH);
  delayMicroseconds(100);
  digitalWrite(26, LOW);
  interval3 = pulseIn(27, HIGH);
  distance3 = interval3 * 0.017;

  Serial.print("dist:");
  Serial.print(distance1, 4);
  Serial.print("cm \t");
  Serial.print(distance2, 4);
  Serial.print("cm \t");
  Serial.print(distance3, 4);
  Serial.print("cm \n");
  //===超音波===
  //===動き===
  if (false) {
    base.write(90);
    delay(1000);
    Braccio.ServoMovement(0, 90, 120, 50, 50, 45, 73);
  } else if (false) {
    base.write(0);
    delay(1000);
    Braccio.ServoMovement(0, 0, 120, 50, 50, 45, 73);
  } else if (distance3 <= 50) {
    base.write(180);
    delay(1000);
    //    Braccio.ServoMovement(20, 180, 120, 50, 50, 45, 73);
    shoulder.write(120);
    elbow.write(50);
    wrist_rot.write(50);
    wrist_ver.write(45);
    gripper.write(73);
  } else if (distance3 > 50) {
    base.write(90);
    //    Braccio.ServoMovement(20, 90, 100, 155, 0, 0, 10);//デフォルトポジションに戻る
    shoulder.write(100);
    elbow.write(155);
    wrist_rot.write(0);
    wrist_ver.write(0);
    gripper.write(10);
  }
  //===動き===
}
