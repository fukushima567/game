#include "clearCamera.h"
#include "../MyLib/myLib.h"
#include "../Common.h"


//�R���X�g���N�^
ClearCamera::ClearCamera() {

	memset(&cameraPos, 0, sizeof(VECTOR));
	memset(&cameraFocus, 0, sizeof(VECTOR));
	memset(&cameraUp, 0, sizeof(VECTOR));
	memset(&cameraRot, 0, sizeof(VECTOR));

	frameCount = 0;
}


//������
void ClearCamera::Init() {

	cameraPos = CLEAR_CAMERA_FIRST_POS;
	cameraFocus = CLEAR_CAMERA_FIRST_FOCUS;
	cameraUp = CLEAR_CAMERA_UP;
}


//�ʏ폈��
void ClearCamera::Step() {

	frameCount++;
	//���ڂ̃J�����ړ�
	if (frameCount >= CLEAR_CAMERA_MOVE_FRAME_1) {
		cameraPos.z++;
		if (cameraPos.z > CLEAR_CAMERA_MAX_POS_Z) {
			cameraPos.z = CLEAR_CAMERA_MAX_POS_Z;
		}
		cameraPos.y-= CLEAR_CAMERA_MOVE_NUM;
		if (cameraPos.y < CLEAR_CAMERA_MIN_POS_Y) {
			cameraPos.y = CLEAR_CAMERA_MIN_POS_Y;
		}
	}

	//���ڂ̃J�����ړ�
	if (frameCount >= CLEAR_CAMERA_MOVE_FRAME_2) {
		cameraFocus.x += CLEAR_CAMERA_MOVE_NUM;
		if (cameraFocus.x > CLEAR_CAMERA_MAX_FOCUS_X) {
			cameraFocus.x = CLEAR_CAMERA_MAX_FOCUS_X;
		}
	}

	//���f�������W���J�����ɃZ�b�g
	SetCameraPositionAndTargetAndUpVec(cameraPos, cameraFocus, cameraUp);
}