#include "SceneTest.h"

int jh;

void SceneTest::Init() {

	fin = false;
	
}


void SceneTest::Step() {

	DrawFormatString(100, 0, GetColor(255, 0, 0), "�e�X�g");
	/*����ĂԂƃV�[�����I���܂��B���̎��A�ړ����sceneID���Ă�ł����Ă�������
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