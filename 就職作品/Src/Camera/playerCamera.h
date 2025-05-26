#pragma once
#include "DxLib.h"


//����
constexpr VECTOR PLAYER_CAMERA_UP = { 0.0f,1.0f,0.0f };			//�J�����̏����
constexpr float	 PLAYER_CAMERA_ADD_FOCUS_NUM = 18.0f;			//�����_����Ɍ������
constexpr float	 PLAYER_CAMERA_RADIUS_CHANGE_NUM = 5.0f;		//�����_�Ƃ̋����̕ω���
constexpr float	 PAD_SENSITIVITY = 300000.0f;					//�R���g���[���[���x
constexpr float	 MOUSE_SENSITIVITY = 200.0f;					//�}�E�X���x


//�ʏ펞
constexpr float PLAYER_CAMERA_NORMAL_RADIUS_NUM = -55.0f;		//�ʏ펞�̃J�����ƒ����_�̋���
constexpr float PLAYER_CAMERA_MAX_NORMAL_ROT_X = 70.0f;			//�ʏ펞���̃J�����ő�w
constexpr float PLAYER_CAMERA_MIN_NORMAL_ROT_X = -60.0f;		//�ʏ펞���̃J�����ŏ��w


//�_�b�V��
constexpr float PLAYER_CAMERA_DASH_RADIUS_NUM = -1.0f;			//�_�b�V�����̒����_�Ƃ̋���
constexpr float PLAYER_CAMERA_MAX_DASH_ROT_X = 10.0f;			//�_�b�V�����̃J�����ő�w
constexpr float PLAYER_CAMERA_MIN_DASH_ROT_X = -10.0f;			//�_�b�V�����̃J�����ŏ��w
constexpr float PLAYER_CAMERA_LICK_ROT_Y_NUM = 0.06f;			//���b�N�I���ύX���̃J������]��



//�v���C���[�J����
class PlayerCamera {
private:

	VECTOR cameraPos;		//�J�����̈ʒu
	VECTOR cameraFocus;		//�J�����̒����_
	VECTOR cameraUp;		//�J�����̏����
	VECTOR cameraRot;		//�J�����̉�]

	int mouseX;				//�}�E�X�̈ړ���X
	int mouseY;				//�}�E�X�̈ړ���Y

	float radius;			//�����_�Ƃ̋���
	float maxRadius;		//�����_�Ƃ̍ő勗��

public:

	PlayerCamera();
	~PlayerCamera(){}

	//����������
	void Init();

	//�ʏ폈��
	void Step(VECTOR focus,float lock_rad, bool is_dash);
	
	//�擾�֌W
	//�J�����̉�]�𓾂�
	VECTOR GetRot() { return cameraRot; }

	//�J�����ƒ����_�̋����𓾂�
	float GetRadius() { return radius; }
};