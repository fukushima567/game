#pragma once
#include "DxLib.h"


//画像種類
enum KEY_IMAGE_TYPE {

	IMAGE_MOUSE_LEFT,	//左クリック
	IMAGE_MOUSE_RIGHT,	//右クリック
	IMAGE_KEY_E,		//Eキー
	IMAGE_KEY_ESC,		//エスケープキー
	IMAGE_KEY_A,		//Aキー
	IMAGE_KEY_S,		//Sキー
	IMAGE_KEY_D,		//Dキー
	IMAGE_KEY_NONE,		//キーなし
	IMAGE_BUTTON_A,		//Aボタン
	IMAGE_BUTTON_B,		//Bボタン
	IMAGE_BUTTON_Y,		//Yボタン
	IMAGE_BUTTON_RB,	//RBボタン
	IMAGE_BUTTON_START,	//STARTボタン
	IMAGE_STICK_LEFT,	//Lステック左
	IMAGE_STICK_BACK,	//Lステック後
	IMAGE_STICK_RIGHT,	//Lステック右

	IMAGE_KEY_NUM		//キー画像総数
};


//キー画像
class KeyUI {

private:
	static int keyImageHandle[IMAGE_KEY_NUM];

public:
	//初期化
	static void Init();

	//描画
	static void Draw(KEY_IMAGE_TYPE image_type,int x, int y);
};