#include "gameData.h"


//�C���X�^���X������
GameData* GameData::instance = nullptr;


//�R���X�g���N�^
GameData::GameData() {
	
	gameTime = NORMAL_TIME;

	fontHandle = 0;

	sceneID = TITLE;

	stageType = STAGE_0;
}


//�C���X�^���X�쐬
void GameData::Create() {
	if (instance == nullptr) {
		instance = new GameData();
	}
}


//�j��
void GameData::Destroy() {
	delete instance;
	instance = nullptr;
}


//�C���X�^���X�擾
GameData* GameData::GetInstance() {

	if (instance == nullptr) {
		Create();
	}
	return instance;
}