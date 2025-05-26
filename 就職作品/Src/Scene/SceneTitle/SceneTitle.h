#pragma once
#include "../../MyLib/myLib.h"
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


//タイトル画面の画像
enum TITLE_IMAGE_TYPE {
	TITLE_IMAGE_STAGE,		//ステージ画像
	TITLE_IMAGE_PLAYER,		//プレイヤー画像
	TITLE_IMAGE_ENEMY,		//敵画像
	TITLE_IMAGE_BOSS,		//ボス画像
	TITLE_IMAGE_START,		//スタートボタン画像
	TITLE_IMAGE_NAME,		//タイトル名画像

	TITLE_IMAGE_NUM			//画像の総数
};


constexpr float START_UI_X_SIZE = 512.0f;		//スタートボタンXサイズ
constexpr float START_UI_Y_SIZE = 256.0f;		//スタートボタンYサイズ


//タイトルシーン
class SceneTitle :public SceneBase {
private:

	int handle[TITLE_IMAGE_NUM];	//タイトル画像
	VECTOR pos;						//タイトルUI座標
	float scale;					//タイトルUIおおきさ

	float radian;					//タイトル画像移動用ラジアン

	bool select;					//選択フラグ

	Cursor cursor;					//カーソル

public:
	
	//初期化
	void Init();
	
	//通常処理
	void Step();

	//描画処理
	void Draw();

	//破棄処理
	void Delete();
};