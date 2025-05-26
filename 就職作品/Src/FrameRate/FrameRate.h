#pragma once
#include "DxLib.h"

//�ݒ�t���[�����[�g
constexpr int FRAME_RATE = 60;

//�P�t���[���̎���(�~���b)
constexpr int FRAME_TIME = 1000 / FRAME_RATE;


//�t���[�����[�g�N���X
class FrameRate {
private:

	int currentTime;
	int lastFrameTime;
	int count;
	int calcFpsTime;
	float fps;

public:

	//�R���X�g���N�^
	FrameRate();
	~FrameRate(){}

	//�ʏ폈��
	void Step();

	//���[�v�����邩
	bool Play();

	//FPS�v�Z
	void CalcFps();

	//FPS�\��
	void DrawCalc();

};