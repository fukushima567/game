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

//������
void PadInput::Init() {

	for (int index = 0; index < BUTTON_BUF_LEN; index++) {
		currentButtonBuf[index] = 0;
		preButtonBuf[index] = 0;
	}
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.1);
	
}


//�O�t���ƌ��t�����L�^(�V�[���Ǘ��̑O�ɌĂԕK�v����)
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

	// ���͏�Ԃ��擾
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


//�������ꂽ
bool PadInput::Push(int button_index) {
	if (!connectPad) { return false; }
	//�O�t���ŉ�����Ă��Ȃ����A���t���ŉ�����Ă���
	if (preButtonBuf[button_index] == 0 && currentButtonBuf[button_index] == 1) {
		return true;
	}
	else {
		//������Ă��Ȃ��̂� false
		return false;
	}
}


//������Ă���
bool PadInput::Keep(int button_index) {
	if (!connectPad) { return false; }
	//���t���ŉ�����Ă���
	if (currentButtonBuf[button_index] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//�����ꂽ
bool PadInput::Release(int button_index) {
	if (!connectPad) { return false; }
	//�O�t���ŉ�����Ă��邩�A���t���ŉ�����Ă��Ȃ��B
	if (preButtonBuf[button_index] == 1 && currentButtonBuf[button_index] == 0) {
		return true;
	}
	else {
		return false;
	}
}


bool PadInput::Release2(int button_index) {
	if (!connectPad) { return false; }
	//�O�t���ŉ�����Ă��Ȃ����A���t���ŉ�����Ă��Ȃ��B
	if (preButtonBuf[button_index] == 0 && currentButtonBuf[button_index] == 0) {
		return true;
	}
	else {
		return false;
	}
}

