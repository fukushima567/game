#pragma once
#include "DxLib.h"


//コントローラーからの入力（Xinput）
class PadInput{
public:

	static XINPUT_STATE  input;

	static bool connectPad;

	static bool currentLStickXBuf;

	static bool preLStickXBuf;

	static bool currentLStickYBuf;

	static bool preLStickYBuf;


	//インプット初期化
	static void Init();

	//インプット通常処理
	static void Step();

	//今押された
	static bool Push(int button_index);

	//押されている
	static bool Keep(int button_index);

	//離された
	static bool Release(int button_index);

	//前フレームから離された
	static bool Release2(int button_index);

	//LスティックのX値を得る
	static int GetLX() { 
		if (!connectPad) { return 0; }
		if(abs(input.ThumbLX) < 2000) {
			return 0;
		}
		return input.ThumbLX;
	}

	//Lスティックが押された瞬間のX値を得る
	static int GetPushLX() {
		if (currentLStickXBuf == 1 && preLStickXBuf == 0) {
			return input.ThumbLX;
		}
		return 0;
	}

	//LスティックのY値を得る
	static int GetLY() { 
		if (!connectPad) { return 0; }
		if (abs(input.ThumbLY) < 2000) {
			return 0;
		}
		return input.ThumbLY;
	}

	//Lスティックが押された瞬間のY値を得る
	static int GetPushLY() {
		if (currentLStickYBuf == 1 && preLStickYBuf == 0) {
			return input.ThumbLY;
		}
		return 0;
	}

	//RスティックのX値を得る
	static int GetRX() {
		if (!connectPad) { return 0; }
		if (abs(input.ThumbRX) < 2000) {
			return 0;
		}
		return input.ThumbRX;
	}

	//RスティックのY値を得る
	static int GetRY() { 
		if (!connectPad) { return 0; }
		if (abs(input.ThumbRY) < 2000) {
			return 0;
		}
		return input.ThumbRY;
	}
};