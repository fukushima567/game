#include "SceneManager.h"
#include "../Scene/SceneTitle/SceneTitle.h"
#include "../Scene/SceneSelect/SceneSelect.h"
#include "../Scene/ScenePlay/ScenePlay.h"
#include "../Scene/SceneGameOver/SceneGameOver.h"
#include "../Scene/SceneTest/SceneTest.h"



//�V�[���}�l�[�W���[�̏�����
void SceneManager::Init() {

	GameData::GetInstance()->SetFontHandle(CreateFontToHandle(NULL, 40, -1, DX_FONTTYPE_ANTIALIASING));

	Sound::Init();
	Sound::LoadCommonSound();

	loadImageHandle = LoadGraph("Data/Image/load.png");

	KeyUI::Init();
	
	//������ς���Ə����̃V�[�����ς��܂��B
	GameData::GetInstance()->SetSceneID(TITLE);
	
	sceneState = INIT;
	sceneBase = nullptr;
}


//�V�[���}�l�[�W���[�̒ʏ폈��
void SceneManager::Step() {
	
	//����������
	if (sceneState == INIT) {

		//����new���Ă�����j��
		if (sceneBase != nullptr) {
			delete sceneBase;
			sceneBase = nullptr;
		}
		
		//�V�[�����Ƃ�new
		switch (GameData::GetInstance()->GetSceneID()) {

		case TITLE://�^�C�g��
			sceneBase = new SceneTitle;
			break;

		case SELECT://�Z���N�g
			sceneBase = new SceneSelect;
			break;

		case PLAY://�v���C
			sceneBase = new ScenePlay;
			break;

		case OVER://�Q�[���I�[�o�[
			sceneBase = new SceneGameOver;
			break;

		case TEST://�e�X�g�p�V�[��
			sceneBase = new SceneTest;
			break;

		}
		//�V�[���̏�����
		Sound::LoadSound(GameData::GetInstance()->GetSceneID());
		sceneBase->Init();
		//���[�v�����Ɉړ�
		sceneState =LOOP;
	}


	//�ʏ폈��
	if (sceneState == LOOP) {

		//�ʏ폈��
		sceneBase->Step();
		//�`�揈��
		sceneBase->Draw();

		//�e�V�[����fin��true�ɂȂ�����init��
		if (sceneBase->GetFin()) {
			Sound::Delete();
			sceneState = INIT;
			DrawGraph(0,0,loadImageHandle,true);
		}
	}
}