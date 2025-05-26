#pragma once
#include "SceneBase/SceneBase.h"


//�V�[���̏��
enum SceneState {
	INIT,
	LOOP,
};


//�V�[���}�l�[�W���[�N���X
class SceneManager {
private:

	int loadImageHandle;

	SceneBase* sceneBase;
	
	SceneState sceneState;

public:

	//�V�[���}�l�[�W���[�̏�����
	void Init();

	//�V�[���}�l�[�W���[�̒ʏ폈��
	void Step();
};