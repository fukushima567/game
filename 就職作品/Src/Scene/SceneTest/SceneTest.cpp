#include "SceneTest.h"

int jh;

void SceneTest::Init() {

	fin = false;
	
}


void SceneTest::Step() {

	DrawFormatString(100, 0, GetColor(255, 0, 0), "テスト");
	/*これ呼ぶとシーンが終わります。その時、移動先のsceneIDを呼んであげてください
	Delete();
	sceneID=
	*/
	jh=GetJoypadXInputState(DX_INPUT_PAD1, &a);

}

void SceneTest::Draw() {

	DrawFormatString(100, 200, 255, "%d", jh);

}

void SceneTest::Delete() {

	fin = true;

}