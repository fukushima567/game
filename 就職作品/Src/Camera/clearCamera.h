#pragma once
#include "DxLib.h"


constexpr VECTOR CLEAR_CAMERA_FIRST_POS = { 0.0f,18.0f,8.0f };		//�J�����̏������W
constexpr VECTOR CLEAR_CAMERA_FIRST_FOCUS = { 0.0f,18.0f,0.0f };	//�J�����̏��������_
constexpr VECTOR CLEAR_CAMERA_UP = { 0.0f,1.0f,0.0f };				//�J�����̏����

constexpr int CLEAR_CAMERA_MOVE_FRAME_1 = 120;						//�J�������ړ�����t���[���P
constexpr int CLEAR_CAMERA_MOVE_FRAME_2 = 160;						//�J�������ړ�����t���[���Q

constexpr float CLEAR_CAMERA_MOVE_NUM = 0.5f;						//�J�����̈ړ���
constexpr float CLEAR_CAMERA_MAX_FOCUS_X = 20.0f;					//�J������X�ő咍���_
constexpr float CLEAR_CAMERA_MIN_POS_Y= 15.0f;						//�J������Y�ő�ʒu
constexpr float CLEAR_CAMERA_MAX_POS_Z = 35.0f;						//�J������Z�ő�ʒu


//�N���A���J����
class ClearCamera {
private:

	VECTOR cameraPos;		//�J�����̈ʒu
	VECTOR cameraFocus;		//�J�����̒����_
	VECTOR cameraUp;		//�J�����̏����
	VECTOR cameraRot;		//�J�����̉�]

	int frameCount;			//�t���[���̃J�E���g

public:

	ClearCamera();
	~ClearCamera(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�擾�֌W
	//�J�����̉�]�𓾂�
	VECTOR GetRot() { return cameraRot; }
};