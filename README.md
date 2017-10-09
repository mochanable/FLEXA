# FLEXA
  FLEXA -the Flexible Anima- powered by Arduino Braccio®
  Created & Copyrighted by
    Team FLEXA
      TI:Takafumi Imai
      YM:Yusuke Maikuma
      TH:Tatsuya Hasegawa

  ver2.2 @2017_9_21 by TI
  -超音波センサを6つに
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
