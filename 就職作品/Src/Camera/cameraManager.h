#pragma once
#include "startCamera.h"
#include "playerCamera.h"
#include "clearCamera.h"



//�J�����}�l�[�W���[
class CameraManager {
public:
	//�J�����̎��
	enum CameraType {
		CAMERA_TYPE_START,	//�J�n���J����
		CAMERA_TYPE_PLAYER,	//�v���C���[�J����
		CAMERA_TYPE_CLEAR,	//�N���A���J����
		CAMERA_TYPE_NUM
	};

private:
	
	//�X�^�[�g�J����
	StartCamera startCamera;

	//�v���C���[�J����
	PlayerCamera playerCamera;

	//�N���A�J����
	ClearCamera clearCamera;

	//�J�����̎��
	CameraType cameraType;
	

public:

	//������
	void Init();

	//�J��������
	void Step(VECTOR focus, float rot,bool num);

	//�J�����^�C�v�𓾂�
	CameraType GetCameraType() { return cameraType; }

	//�J�����̉�]�𓾂�
	VECTOR GetRot();

	//�����_�Ƃ̋����𓾂�
	float GetRadius() { return playerCamera.GetRadius(); }

	//�J�����^�C�v��ύX
	void SetCameraType(CameraType camera_type) { cameraType = camera_type; }

	//�j�A�[�ƃt�@�[���Z�b�g
	void SetNearFar(float camera_near, float camera_far);
};