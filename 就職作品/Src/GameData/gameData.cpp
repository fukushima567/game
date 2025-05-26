#include "gameData.h"


//インスタンス初期化
GameData* GameData::instance = nullptr;


//コンストラクタ
GameData::GameData() {
	
	gameTime = NORMAL_TIME;

	fontHandle = 0;

	sceneID = TITLE;

	stageType = STAGE_0;
}


//インスタンス作成
void GameData::Create() {
	if (instance == nullptr) {
		instance = new GameData();
	}
}


//破棄
void GameData::Destroy() {
	delete instance;
	instance = nullptr;
}


//インスタンス取得
GameData* GameData::GetInstance() {

	if (instance == nullptr) {
		Create();
	}
	return instance;
}