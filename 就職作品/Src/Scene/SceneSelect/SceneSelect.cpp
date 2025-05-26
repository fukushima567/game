#include "SceneSelect.h"
#include "../../MyLib/myLib.h"
#include "../../Collision/Collision.h"


//�Z���N�g�V�[��������
void SceneSelect::Init() {

	cursor.Init();

	screenEffect.Init();
	change=false;
	
	LoadDivGraph("Data/Image/Select/stage.png", STAGE_NUM,1, STAGE_NUM,500,100, stageBoxHandle);
	
	backGroundHandle[0] = LoadGraph("Data/Image/Select/selectBackGround.png");
	backGroundHandle[1]= LoadGraph("Data/Image/Select/Box.png");
	backGroundPos[0] = 0;
	backGroundPos[1] = -SCREEN_SIZE_Y;

	stageScreenHandle[STAGE_0] = LoadGraph("Data/Image/Select/st0_screen.png");
	stageScreenHandle[STAGE_1] = LoadGraph("Data/Image/Select/st1_screen.png");
	stageScreenHandle[STAGE_2] = LoadGraph("Data/Image/Select/st2_screen.png");
	stageScreenHandle[STAGE_3] = LoadGraph("Data/Image/Select/st3_screen.png");
	stageScreenHandle[STAGE_4] = LoadGraph("Data/Image/Select/st4_screen.png");

	for (int index = 0; index < STAGE_NUM; index++) {

		stageBoxPos[index].x = 355;
		stageBoxPos[index].y = (float)250 + (index * 150);
		stageBoxSize[index] = { 500,100,0 };
		stageBoxScale[index] = 0.0f;
	}

	selectIndex = -1;

	Sound::Play(S_BGM,true);

	stageScreenPos = {800,SCREEN_SIZE_Y / 2 - 400 ,0};
	stageScreenSize = { 1000,500,800 };
	fin = false;
}


//�Z���N�g�ʏ폈��
void SceneSelect::Step() {

	if (change) { return; }


	cursor.Step();

	//�w�i�̃X�N���[��
	for (int index = 0;index < 2;index++) {
		backGroundPos[index] += 2;
		if (backGroundPos[index] >= SCREEN_SIZE_Y) {
			backGroundPos[index] = -SCREEN_SIZE_Y;
		}
	}

	//�G�X�P�[�v�L�[���X�^�[�g�{�^���Ń^�C�g���֖߂�
	if (Input::Push(KEY_INPUT_ESCAPE) || PadInput::Push(XINPUT_BUTTON_START)) {
		Delete();
		GameData::GetInstance()->SetSceneID(TITLE);
	}


	bool select = false;

	//�X�e�[�W�I���̏���
	for (int index = 0; index < STAGE_NUM; index++) {

		//�I�����ꂽUI�̏���
		if (Collision::RectAndCircle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), stageBoxPos[index].x- stageBoxSize[index].x/2, stageBoxPos[index].y - stageBoxSize[index].y / 2, stageBoxSize[index].x, stageBoxSize[index].y)) {
			cursor.Select();
			//�I�����ꂽ��񂾂�SE
			select = true;
			if (selectIndex != index) {
				Sound::Play(C_SE_SELECT, false);
				selectIndex = index;
			}

			//�I��������UI���傫���Ȃ�
			stageBoxScale[index] += 0.05f;
			if (stageBoxScale[index] >= 1.3f) {
				stageBoxScale[index] = 1.3f;
			}

			//�{�^�����������ƃX�e�[�W������
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				Sound::Play(C_SE_DECIDE, false);
				change = true;
				GameData::GetInstance()->SetStageType((STAGE_TYPE)index);
			}
		}
		else {//�I������Ă��Ȃ�UI�͌��̑傫����
			stageBoxScale[index] -= 0.05f;
			if (stageBoxScale[index] <= 1.0f) {
				stageBoxScale[index] = 1.0f;
			}
		}	
	}

	if (!select) {
		selectIndex = -1;
	}
}


//�Z���N�g�`��
void SceneSelect::Draw() {

	for (int index = 0;index < 2;index++) {
		DrawGraph(0, backGroundPos[index], backGroundHandle[0], true);
	}
	
	DrawBox((int)stageScreenPos.x, (int)stageScreenPos.y, (int)(stageScreenPos.x+ stageScreenSize.x), (int)(stageScreenPos.y + stageScreenSize.z), GetColor(255, 255, 255), true);
	
	if (selectIndex != -1) {
		DrawExtendGraph((int)stageScreenPos.x, (int)stageScreenPos.y, (int)(stageScreenPos.x + stageScreenSize.x), (int)(stageScreenPos.y + stageScreenSize.y), stageScreenHandle[selectIndex], true);
		DrawFormatStringToHandle((int)stageScreenPos.x, (int)(stageScreenPos.y + stageScreenSize.y), BASE_FONT_COLOR, GameData::GetInstance()->GetFontHandle(), "%s", STAGE_TEXT[selectIndex]);
	}

	for (int index = 0; index < STAGE_NUM; index++) {
		DrawRotaGraph((int)stageBoxPos[index].x, (int)stageBoxPos[index].y, stageBoxScale[index], 0.0, stageBoxHandle[index], true);
	}


	DrawGraph((int)stageScreenPos.x, (int)stageScreenPos.y,backGroundHandle[1],true);


	cursor.Draw();


	if (!change) {
		screenEffect.FadeIn();
	}
	else {
		if (screenEffect.FadeOut()) {
			GameData::GetInstance()->SetSceneID(PLAY);
			Delete();
		}
	}
}


//�Z���N�g�j��
void SceneSelect::Delete() {
	for (int index = 0; index < STAGE_NUM; index++) {
		DeleteGraph(stageBoxHandle[index]);
		DeleteGraph(stageScreenHandle[index]);
	}
	DeleteGraph(backGroundHandle[0]);
	DeleteGraph(backGroundHandle[1]);
	cursor.Delete();
	fin = true;
}