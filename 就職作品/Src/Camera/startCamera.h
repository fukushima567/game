#pragma once
#include "DxLib.h"


//�J����1�x�ڂ̈ړ�
constexpr VECTOR START_CAMERA_POS_1 = { 0.0f,50.0f,500.0f };	//�J�����̍��W1
constexpr VECTOR START_CAMERA_ROT_1 = { 0.349f,0.0f,0.0f };		//�J�����̉�]1
constexpr float  START_CAMERA_MIN_Z = -10.0f;					//�J�����̍ŏ������W

//�J����2�x�ڂ̈ړ�
constexpr VECTOR START_CAMERA_POS_2 = { -200.0f,70.0f,250.0f };	//�J�����̍��W2
constexpr VECTOR START_CAMERA_ROT_2 = { 0.349f,1.396f, 0.0f };	//�J�����̉�]2

//�J����3�x�ڂ̈ړ�
constexpr VECTOR START_CAMERA_POS_3 = { 500.0f,20.0f,250.0f };	//�J�����̍��W3
constexpr VECTOR START_CAMERA_ROT_3 = { 0.523f, 5.235f, 0.0f };	//�J�����̉�]3
constexpr VECTOR START_CAMERA_UP = { 0.0f,1.0f,0.0f };			//�J�����̏����

constexpr float START_CAMERA_ROT_NUM = 0.002f;					//�J�����̃��b�g�ω���


//���_�ړ��̎��
enum VIEW_POINT_STATE {
	VIEW_MOVE,		//���ɓ���
	VIEW_SIDE,		//����]		
	VIEW_UP			//��ɉ�]
};

//�J�n���J����
class StartCamera {
private:

	VECTOR cameraPos;		//�J�����̈ʒu
	VECTOR cameraRot;		//�J�����̊p�x
	int viewPointState;		//���_�̏��


public:

	StartCamera();
	~StartCamera(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�擾�֌W
	//�J�����̉�]�𓾂�
	VECTOR GetRot() { return cameraRot; }
};