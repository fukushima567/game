#include "SceneSelect.h"
#include "../../MyLib/myLib.h"
#include "../../Collision/Collision.h"


//セレクトシーン初期化
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


//セレクト通常処理
void SceneSelect::Step() {

	if (change) { return; }


	cursor.Step();

	//背景のスクロール
	for (int index = 0;index < 2;index++) {
		backGroundPos[index] += 2;
		if (backGroundPos[index] >= SCREEN_SIZE_Y) {
			backGroundPos[index] = -SCREEN_SIZE_Y;
		}
	}

	//エスケープキーかスタートボタンでタイトルへ戻る
	if (Input::Push(KEY_INPUT_ESCAPE) || PadInput::Push(XINPUT_BUTTON_START)) {
		Delete();
		GameData::GetInstance()->SetSceneID(TITLE);
	}


	bool select = false;

	//ステージ選択の処理
	for (int index = 0; index < STAGE_NUM; index++) {

		//選択されたUIの処理
		if (Collision::RectAndCircle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), stageBoxPos[index].x- stageBoxSize[index].x/2, stageBoxPos[index].y - stageBoxSize[index].y / 2, stageBoxSize[index].x, stageBoxSize[index].y)) {
			cursor.Select();
			//選択された一回だけSE
			select = true;
			if (selectIndex != index) {
				Sound::Play(C_SE_SELECT, false);
				selectIndex = index;
			}

			//選択されるとUIが大きくなる
			stageBoxScale[index] += 0.05f;
			if (stageBoxScale[index] >= 1.3f) {
				stageBoxScale[index] = 1.3f;
			}

			//ボタンが押されるとステージを決定
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				Sound::Play(C_SE_DECIDE, false);
				change = true;
				GameData::GetInstance()->SetStageType((STAGE_TYPE)index);
			}
		}
		else {//選択されていないUIは元の大きさに
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


//セレクト描画
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


//セレクト破棄
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