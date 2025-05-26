#pragma once
#include "DxLib.h"

//設定フレームレート
constexpr int FRAME_RATE = 60;

//１フレームの時間(ミリ秒)
constexpr int FRAME_TIME = 1000 / FRAME_RATE;


//フレームレートクラス
class FrameRate {
private:

	int currentTime;
	int lastFrameTime;
	int count;
	int calcFpsTime;
	float fps;

public:

	//コンストラクタ
	FrameRate();
	~FrameRate(){}

	//通常処理
	void Step();

	//ループさせるか
	bool Play();

	//FPS計算
	void CalcFps();

	//FPS表示
	void DrawCalc();

};