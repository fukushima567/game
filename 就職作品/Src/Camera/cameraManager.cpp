#include "cameraManager.h"
#include "../Input/input.h"


void CameraManager::Init(){

	//�J����������
	startCamera.Init();
	playerCamera.Init();
	clearCamera.Init();
}


//�J�����}�l�[�W���[�ʏ폈��
void CameraManager::Step(VECTOR focus, float rot,bool num) {

	//�J�����^�C�v�ɂ���ď�����ς���
	switch (cameraType) {

		//�J�n���J����
	case CAMERA_TYPE_START:
		startCamera.Step();
		break;


		//�v���C���[�J����
	case CAMERA_TYPE_PLAYER:
		playerCamera.Step(focus, rot, num);
		break;

		//�N���A���J����
	case CAMERA_TYPE_CLEAR:
		clearCamera.Step();
		break;
	}
}


//��ʂ̕`��͈͂�ݒ�
void CameraManager::SetNearFar(float camera_near, float camera_far) {

	SetCameraNearFar(camera_near, camera_far);
}


//�J�����̉�]�𓾂�
VECTOR CameraManager::GetRot() {
	switch (cameraType) {
	case CAMERA_TYPE_START:
		return startCamera.GetRot();
		break;

	case CAMERA_TYPE_PLAYER:
		return playerCamera.GetRot();
		break;

	default:
		return clearCamera.GetRot();
		break;
	}
}