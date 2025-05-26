#include "SceneGameOver.h"


void SceneGameOver::Init() {

	fin = false;
	LoadDivGraph("Data/Image/GameOver/gmo.png", 2, 1, 2, 1920, 1080, handle);
	
	change = false;
	screenEffect.Init();
	Sound::Play(O_BGM, true);
}


void SceneGameOver::Step() {

	if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
		
		change = true;
	}
}

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

void SceneGameOver::Delete() {

	fin = true;
	DeleteGraph(handle[0]);
	DeleteGraph(handle[1]);
}