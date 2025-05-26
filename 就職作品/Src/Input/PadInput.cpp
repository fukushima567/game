#include "DxLib.h"
#include "PadInput.h"


#define BUTTON_BUF_LEN (16)

bool PadInput::connectPad;

bool currentButtonBuf[BUTTON_BUF_LEN] = { 0 };

bool preButtonBuf[BUTTON_BUF_LEN] = { 0 };

 bool PadInput::currentLStickXBuf;

 bool PadInput::preLStickXBuf;

 bool PadInput::currentLStickYBuf;

 bool PadInput::preLStickYBuf;

XINPUT_STATE PadInput::input;

//初期化
void PadInput::Init() {

	for (int index = 0; index < BUTTON_BUF_LEN; index++) {
		currentButtonBuf[index] = 0;
		preButtonBuf[index] = 0;
	}
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.1);
	
}


//前フレと現フレを記録(シーン管理の前に呼ぶ必要あり)
void PadInput::Step() {

	if (GetJoypadNum() == 0) {
		connectPad = false;
	}
	else {
		connectPad = true;
	}

	if (!connectPad) { return; }

	for (int index = 0;index < BUTTON_BUF_LEN;index++) {
		preButtonBuf[index] = currentButtonBuf[index];
	}


	preLStickXBuf = currentLStickXBuf;

	preLStickYBuf = currentLStickYBuf;

	// 入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	for (int index = 0;index < BUTTON_BUF_LEN;index++) {
		if (input.Buttons[index] > 0) {
			currentButtonBuf[index] = 1;
		}
		else {
			currentButtonBuf[index] = 0;
		}
	}

	if (GetLX() != 0) {
		currentLStickXBuf = 1;
	}
	else {
		currentLStickXBuf = 0;
	}

	if (GetLY() != 0) {
		currentLStickYBuf = 1;
	}
	else {
		currentLStickYBuf = 0;
	}
}


//今押された
bool PadInput::Push(int button_index) {
	if (!connectPad) { return false; }
	//前フレで押されていないかつ、現フレで押されている
	if (preButtonBuf[button_index] == 0 && currentButtonBuf[button_index] == 1) {
		return true;
	}
	else {
		//押されていないので false
		return false;
	}
}


//押されている
bool PadInput::Keep(int button_index) {
	if (!connectPad) { return false; }
	//現フレで押されている
	if (currentButtonBuf[button_index] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//離された
bool PadInput::Release(int button_index) {
	if (!connectPad) { return false; }
	//前フレで押されているかつ、現フレで押されていない。
	if (preButtonBuf[button_index] == 1 && currentButtonBuf[button_index] == 0) {
		return true;
	}
	else {
		return false;
	}
}


bool PadInput::Release2(int button_index) {
	if (!connectPad) { return false; }
	//前フレで押されていないかつ、現フレで押されていない。
	if (preButtonBuf[button_index] == 0 && currentButtonBuf[button_index] == 0) {
		return true;
	}
	else {
		return false;
	}
}

