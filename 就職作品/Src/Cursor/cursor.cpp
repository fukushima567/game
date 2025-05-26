#include "cursor.h"


//コンストラクタ
Cursor::Cursor() {

	handle = 0;

	memset(&pos,0,sizeof(VECTOR));
	
	radian = 0.0f;
	radius = 0.0f;

	select = false;
}


//初期化
void Cursor::Init() {

	//画像読み込み
	handle = LoadGraph(CURSOR_PATH);

	//座標セット
	pos = {SCREEN_SIZE_X/2,SCREEN_SIZE_Y/2,0};
	
	radius = CURSOR_RADIUS;
}


//通常処理
void Cursor::Step() {

	int mouse_x = 0;
	int mouse_y = 0;

	//マウス移動量取得
	Input::GetMouseNum(&mouse_x, &mouse_y);

	pos.x += mouse_x;
	pos.y += mouse_y;

	//コントローラー移動量取得
	pos.x += (float)PadInput::GetLX()/ CURSOR_PAD_SPEED;
	pos.y -= (float)PadInput::GetLY() / CURSOR_PAD_SPEED;

	//画面外にいかないようにする
	if (pos.x < 0) {//X
		pos.x = 0;
	}
	if (pos.x > SCREEN_SIZE_X) {
		pos.x = SCREEN_SIZE_X;
	}

	if (pos.y < 0) {//Y
		pos.y = 0;
	}
	if (pos.y > SCREEN_SIZE_Y) {
		pos.y = SCREEN_SIZE_Y;
	}

	//選択されていたらカーソル画像回転
	if (select) {
		radian += CURSOR_RAD_ADD_NUM;
	}
	else {
		radian = 0.0f;
	}
	select = false;
}


//描画
void Cursor::Draw() {

	//キーの画像
	if (PadInput::connectPad) {//コントローラー
		KeyUI::Draw(IMAGE_BUTTON_A, (int)CURSOR_KEY_POS.x, (int)CURSOR_KEY_POS.y);
	}
	else {//キーボード
		KeyUI::Draw(IMAGE_MOUSE_LEFT, (int)CURSOR_KEY_POS.x, (int)CURSOR_KEY_POS.y);
	}

	//カーソル画像
	DrawRotaGraph((int)pos.x,(int)pos.y, CURSOR_SCALE, radian,handle,true);
}


//破棄
void Cursor::Delete() {

	DeleteGraph(handle);
}