#include "FrameRate.h"



//コンストラクタ
FrameRate::FrameRate(){
	 currentTime = 0;
	 lastFrameTime = 0;
	 count = 0;
	 calcFpsTime = 0;
	 fps = 0;
	}


//通常処理
void FrameRate::Step() {

	Sleep(1);

	currentTime = GetNowCount();

	if (calcFpsTime == 0.0f) {
		fps = (float)FRAME_RATE;
	}

	
}


//ループさせるか
bool FrameRate::Play() {

	if (currentTime - lastFrameTime >= FRAME_TIME) {
		lastFrameTime = currentTime;
		count++;
		return true;
	}
	else {
		return false;
	}

}


//FPS計算
void FrameRate::CalcFps() {

		int difTime = currentTime - calcFpsTime;


		if (difTime > 1000) {
			float frameCount = (float)(count * 1000.0f);


			fps = frameCount / difTime;

			count = 0;
			calcFpsTime = currentTime;
		}

}


//FPS表示
void FrameRate::DrawCalc() {
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(0, 0, color, "FPS[%.2f]",fps);
}
