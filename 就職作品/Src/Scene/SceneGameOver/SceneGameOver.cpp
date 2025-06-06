#include "SceneGameOver.h"


//初期化
void SceneGameOver::Init() {

	fin = false;
	LoadDivGraph("Data/Image/GameOver/gmo.png", 2, 1, 2, 1920, 1080, handle);
	
	change = false;
	screenEffect.Init();
	Sound::Play(O_BGM, true);
}


//通常処理
void SceneGameOver::Step() {

	//押されたらシーン遷移開始
	if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
		
		change = true;
	}
}


//描画処理
void SceneGameOver::Draw() {

	if (!PadInput::connectPad) {
		DrawGraph(0, 0, handle[0], true);
	}
	else {
		DrawGraph(0, 0, handle[1], true);
	}

	if (!change) {
		screenEffect.FadeIn(true);
	}
	else {
		if (screenEffect.FadeOut(true)) {
			GameData::GetInstance()->SetSceneID(TITLE);
			Delete();
		}
	}
}


//破棄処理
void SceneGameOver::Delete() {

	fin = true;
	DeleteGraph(handle[0]);
	DeleteGraph(handle[1]);
}