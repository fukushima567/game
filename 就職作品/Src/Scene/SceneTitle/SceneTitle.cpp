#include "SceneTitle.h"
#include "../../Collision/Collision.h"


char NameBuffer[10][64];    // フォント十個分


//タイトルシーン
void SceneTitle::Init() {

	cursor.Init();
	screenEffect.Init();

	handle[TITLE_IMAGE_STAGE] = LoadGraph("Data/Image/Title/stage.png");
	handle[TITLE_IMAGE_PLAYER] = LoadGraph("Data/Image/Title/player.png");
	handle[TITLE_IMAGE_ENEMY] = LoadGraph("Data/Image/Title/enemy.png");
	handle[TITLE_IMAGE_BOSS] = LoadGraph("Data/Image/Title/boss.png");

	handle[TITLE_IMAGE_START] = LoadGraph("Data/Image/Title/start.png");
	handle[TITLE_IMAGE_NAME] = LoadGraph("Data/Image/Title/titleName.png");


	pos = { SCREEN_SIZE_X / 2 ,SCREEN_SIZE_Y / 2 + 250,0 };
	scale = 1.0f;
	radian = 0.0f;
	select = false;
	Sound::Play(T_BGM, true);

	change = false;

	fin = false;
	EnumFontName(&NameBuffer[0][0], 10);
}


//タイトル通常処理
void SceneTitle::Step() {
	
	if (change) { return; }

	cursor.Step();
	
	//選択されている際の処理
	if (Collision::RectAndCircle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), pos.x- START_UI_X_SIZE /2, pos.y- START_UI_Y_SIZE /2, START_UI_X_SIZE, START_UI_Y_SIZE)) {
		cursor.Select();
		scale += 0.05f;
		if (scale >= 1.3f) {
			scale = 1.3f;
		}
		if (!select) {
			Sound::Play(C_SE_SELECT, false);
			select = true;
		}
			
		if (Input::PushMouse(MOUSE_LEFT)||PadInput::Push(XINPUT_BUTTON_A)) {
			Sound::Play(C_SE_DECIDE, false);
			change = true;
		}
	}
	else {
		scale -= 0.05f;
		if (scale <= 1.0f) {
			scale = 1.0f;
		}
		select = false;
	}

	radian += 0.1f;
}


//描画処理
void SceneTitle::Draw() {

	DrawGraph(0,0,handle[TITLE_IMAGE_STAGE],true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, 700, 2.0, 0.0f, handle[TITLE_IMAGE_BOSS], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, 0, 0, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawRotaGraph(150, (int)MyLib::GetCircleY(760, 10, radian*1.1f), 1.0, 0.0f, handle[TITLE_IMAGE_PLAYER], true);
	DrawRotaGraph(1700, (int)MyLib::GetCircleY(740, 10, radian/2.0f), 1.0, 0.0f, handle[TITLE_IMAGE_ENEMY], true);

	DrawRotaGraph((int)pos.x, (int)pos.y,scale ,0.0f, handle[TITLE_IMAGE_START],true);

	DrawGraph(0, (int)MyLib::GetCircleY(0,10, radian), handle[TITLE_IMAGE_NAME], true);

	cursor.Draw();


	if (!change) {
		screenEffect.FadeIn();
	}
	else {
		if (screenEffect.FadeOut()) {
			GameData::GetInstance()->SetSceneID(SELECT);
			Delete();
		}
	}
}


//破棄処理
void SceneTitle::Delete() {
	
	for (int index = 0; index < TITLE_IMAGE_NUM; index++) {
		DeleteGraph(handle[index]);
	}
	cursor.Delete();
	fin = true;

}