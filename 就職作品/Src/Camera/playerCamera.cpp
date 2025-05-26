#include "playerCamera.h"
#include "../MyLib/myLib.h"
#include "../Common.h"
#include "../GameData/gameData.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera() {

	memset(&cameraPos,0,sizeof(VECTOR));
	memset(&cameraFocus, 0, sizeof(VECTOR));
	memset(&cameraUp, 0, sizeof(VECTOR));
	memset(&cameraRot, 0, sizeof(VECTOR));

	mouseX = 0;
	mouseY = 0;
	radius = 0.0f;
	maxRadius = 0.0f;
}


//����������
void PlayerCamera::Init() {

	cameraUp = PLAYER_CAMERA_UP;
	radius = PLAYER_CAMERA_NORMAL_RADIUS_NUM;
}


//�ʏ폈��
void PlayerCamera::Step(VECTOR focus,  float lock_rad, bool is_dash) {

	//�}�E�X�ړ��ʎ擾
	Input::GetMouseNum(&mouseX, &mouseY);

	//�}�E�X�̃J�������ړ�
	if (lock_rad == -1) {
		float mouse_num_x;
		mouse_num_x = (float)mouseX;
		if (mouse_num_x != 0) {
			cameraRot.y += mouse_num_x / MOUSE_SENSITIVITY;
		}
	}

	//�}�E�X�̃J�����c�ړ�
	float mouse_num_y;
	mouse_num_y = (float)mouseY;
	if (mouse_num_y != 0) {
		cameraRot.x += (int)mouse_num_y / MOUSE_SENSITIVITY;
	}
	
	//�R���g���[���[�̃J�����ړ�
	if (lock_rad == -1) {
		cameraRot.x -= (float)PadInput::GetRY() / PAD_SENSITIVITY;
		cameraRot.y += (float)PadInput::GetRX() / PAD_SENSITIVITY;
	}

	
	//�����Ă���Έ�l�̂�
	if (is_dash) {
		maxRadius = PLAYER_CAMERA_DASH_RADIUS_NUM;
	}
	else {
		maxRadius = PLAYER_CAMERA_NORMAL_RADIUS_NUM;
	}
	
	//�J�����̋����ύX
	if (radius < maxRadius) {
		radius += PLAYER_CAMERA_RADIUS_CHANGE_NUM;
	}
	if (radius > maxRadius) {
		radius -= PLAYER_CAMERA_RADIUS_CHANGE_NUM;
	}

	//���b�N�I��
	if (lock_rad != -1) {
		if (lock_rad > cameraRot.y + MyLib::GetRadian(180)) {
			lock_rad -= MyLib::GetRadian(360);
		}
		if (lock_rad < cameraRot.y - MyLib::GetRadian(180)) {
			lock_rad += MyLib::GetRadian(360);
		}

		if (cameraRot.y < lock_rad) {
			cameraRot.y += PLAYER_CAMERA_LICK_ROT_Y_NUM;
			if (cameraRot.y >= lock_rad) {
				cameraRot.y = lock_rad;
			}
		}
		if (cameraRot.y > lock_rad) {
			cameraRot.y -= PLAYER_CAMERA_LICK_ROT_Y_NUM;
			if (cameraRot.y <= lock_rad) {
				cameraRot.y = lock_rad;
			}
		}
	}
	
	//�p�x�̐���
	float max_rot_x;
	float min_rot_x;

	if (is_dash) {//�_�b�V�����Ă��鎞��X�p�x����
		max_rot_x = PLAYER_CAMERA_MAX_DASH_ROT_X;
		if (cameraRot.x > MyLib::GetRadian(max_rot_x)) {
			cameraRot.x = MyLib::GetRadian(max_rot_x);
		}

		min_rot_x = PLAYER_CAMERA_MIN_DASH_ROT_X;
		if (cameraRot.x < MyLib::GetRadian(min_rot_x)) {
			cameraRot.x = MyLib::GetRadian(min_rot_x);
		}
	}
	else {//�_�b�V�����Ă��Ȃ����̊p�x����
		max_rot_x = PLAYER_CAMERA_MAX_NORMAL_ROT_X;
		if (cameraRot.x > MyLib::GetRadian(max_rot_x)) {
			cameraRot.x = MyLib::GetRadian(max_rot_x);
		}

		min_rot_x = PLAYER_CAMERA_MIN_NORMAL_ROT_X;
		if (cameraRot.x < MyLib::GetRadian(min_rot_x)) {
			cameraRot.x = MyLib::GetRadian(min_rot_x);
		}
	}

	//Y��]�̐���
	if (cameraRot.y > MyLib::GetRadian(360)) {
		cameraRot.y -= MyLib::GetRadian(360);
	}
	if (cameraRot.y < MyLib::GetRadian(0)) {
		cameraRot.y += MyLib::GetRadian(360);
	}

	

	focus.y += PLAYER_CAMERA_ADD_FOCUS_NUM;
		
	//�J�������W���X�V
	cameraPos = MyLib::Get3DCircle(focus, -cameraRot.x, cameraRot.y, radius);

	//���f�������W���J�����ɃZ�b�g
	SetCameraPositionAndTargetAndUpVec(cameraPos, focus, cameraUp);
}