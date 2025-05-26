#pragma once
#include "DxLib.h"


//�R���g���[���[����̓��́iXinput�j
class PadInput{
public:

	static XINPUT_STATE  input;

	static bool connectPad;

	static bool currentLStickXBuf;

	static bool preLStickXBuf;

	static bool currentLStickYBuf;

	static bool preLStickYBuf;


	//�C���v�b�g������
	static void Init();

	//�C���v�b�g�ʏ폈��
	static void Step();

	//�������ꂽ
	static bool Push(int button_index);

	//������Ă���
	static bool Keep(int button_index);

	//�����ꂽ
	static bool Release(int button_index);

	//�O�t���[�����痣���ꂽ
	static bool Release2(int button_index);

	//L�X�e�B�b�N��X�l�𓾂�
	static int GetLX() { 
		if (!connectPad) { return 0; }
		if(abs(input.ThumbLX) < 2000) {
			return 0;
		}
		return input.ThumbLX;
	}

	//L�X�e�B�b�N�������ꂽ�u�Ԃ�X�l�𓾂�
	static int GetPushLX() {
		if (currentLStickXBuf == 1 && preLStickXBuf == 0) {
			return input.ThumbLX;
		}
		return 0;
	}

	//L�X�e�B�b�N��Y�l�𓾂�
	static int GetLY() { 
		if (!connectPad) { return 0; }
		if (abs(input.ThumbLY) < 2000) {
			return 0;
		}
		return input.ThumbLY;
	}

	//L�X�e�B�b�N�������ꂽ�u�Ԃ�Y�l�𓾂�
	static int GetPushLY() {
		if (currentLStickYBuf == 1 && preLStickYBuf == 0) {
			return input.ThumbLY;
		}
		return 0;
	}

	//R�X�e�B�b�N��X�l�𓾂�
	static int GetRX() {
		if (!connectPad) { return 0; }
		if (abs(input.ThumbRX) < 2000) {
			return 0;
		}
		return input.ThumbRX;
	}

	//R�X�e�B�b�N��Y�l�𓾂�
	static int GetRY() { 
		if (!connectPad) { return 0; }
		if (abs(input.ThumbRY) < 2000) {
			return 0;
		}
		return input.ThumbRY;
	}
};