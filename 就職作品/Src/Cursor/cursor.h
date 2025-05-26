#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


constexpr char CURSOR_PATH[128] = { "data/image/cursor.png" };	//カーソル画像のパス

constexpr float CURSOR_RADIUS = 16.0f;							//カーソルの半径
constexpr float CURSOR_SCALE = 2.0f;							//カーソルのスケール
constexpr float CURSOR_RAD_ADD_NUM = 0.05f;						//カーソル回転値増加量

constexpr int CURSOR_PAD_SPEED = 1000;							//コントローラーのカーソルの移動速度

constexpr VECTOR CURSOR_KEY_POS = { 1800.0f, 1000.0f,0.0f };	//カーソルキーの画像座標


//カーソルクラス
class Cursor{
private:

	int handle;			//カーソル画像

	VECTOR pos;			//カーソル座標

	float radian;		//回転角度
	float radius;		//カーソル半径
	bool select;		//選択フラグ

	//関数
public:
	Cursor();
	~Cursor(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄
	void Delete();

	//取得関係
	//カーソル半径を得る
	float GetRadius() { return radius; }

	//カーソル座標を得る
	VECTOR GetPos() { return pos; }

	//セット関係
	//選択状態をセット
	void Select() { select = true; }
};

