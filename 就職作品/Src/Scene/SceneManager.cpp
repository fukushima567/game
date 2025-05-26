#include "SceneManager.h"
#include "../Scene/SceneTitle/SceneTitle.h"
#include "../Scene/SceneSelect/SceneSelect.h"
#include "../Scene/ScenePlay/ScenePlay.h"
#include "../Scene/SceneGameOver/SceneGameOver.h"
#include "../Scene/SceneTest/SceneTest.h"



//シーンマネージャーの初期化
void SceneManager::Init() {

	GameData::GetInstance()->SetFontHandle(CreateFontToHandle(NULL, 40, -1, DX_FONTTYPE_ANTIALIASING));

	Sound::Init();
	Sound::LoadCommonSound();

	loadImageHandle = LoadGraph("Data/Image/load.png");

	KeyUI::Init();
	
	//ここを変えると初期のシーンが変わります。
	GameData::GetInstance()->SetSceneID(TITLE);
	
	sceneState = INIT;
	sceneBase = nullptr;
}


//シーンマネージャーの通常処理
void SceneManager::Step() {
	
	//初期化処理
	if (sceneState == INIT) {

		//もしnewしていたら破棄
		if (sceneBase != nullptr) {
			delete sceneBase;
			sceneBase = nullptr;
		}
		
		//シーンごとのnew
		switch (GameData::GetInstance()->GetSceneID()) {

		case TITLE://タイトル
			sceneBase = new SceneTitle;
			break;

		case SELECT://セレクト
			sceneBase = new SceneSelect;
			break;

		case PLAY://プレイ
			sceneBase = new ScenePlay;
			break;

		case OVER://ゲームオーバー
			sceneBase = new SceneGameOver;
			break;

		case TEST://テスト用シーン
			sceneBase = new SceneTest;
			break;

		}
		//シーンの初期化
		Sound::LoadSound(GameData::GetInstance()->GetSceneID());
		sceneBase->Init();
		//ループ処理に移動
		sceneState =LOOP;
	}


	//通常処理
	if (sceneState == LOOP) {

		//通常処理
		sceneBase->Step();
		//描画処理
		sceneBase->Draw();

		//各シーンでfinがtrueになったらinitへ
		if (sceneBase->GetFin()) {
			Sound::Delete();
			sceneState = INIT;
			DrawGraph(0,0,loadImageHandle,true);
		}
	}
}