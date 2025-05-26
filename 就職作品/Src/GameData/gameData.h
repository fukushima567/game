#pragma once
#include "../Input/input.h"
#include "../Input/PadInput.h"
#include "../UI/KeyUI.h"
#include "../lib/effekseer.h"
#include "../Sound/sound.h"
#include "../debug/debug.h"


//ゲームの時間
constexpr int NORMAL_TIME = 1;	//通常の時間
constexpr int SLOW_TIME = 10;	//スロウの時間

//デフォルトのフォント色
constexpr int BASE_FONT_COLOR = 0;

//重力
constexpr float GRAVITY = 4.0f;


//シーン
enum SCENE_ID {
	TITLE,		//タイトル
	SELECT,		//セレクト
	PLAY,		//プレイ
	OVER,		//ゲームオーバー
	TEST,		//テスト

	SCENE_NUM
};



//ステージの種類
enum STAGE_TYPE {
	STAGE_0,	//チュートリアル
	STAGE_1,	//森
	STAGE_2,	//マグマ
	STAGE_3,	//都市
	STAGE_4,	//最後

	STAGE_NUM
};



//ゲームデータクラス
class GameData {
private:

	GameData();
	~GameData(){}

	static GameData* instance;	//インスタンス

private:

	int gameTime;				//ゲーム時間

	int fontHandle;				//フォントデータ

	SCENE_ID sceneID;			//シーン

	STAGE_TYPE stageType;		//ステージ

public:

	//インスタンス作成
	static void Create();

	//破棄
	static void Destroy();

	//インスタンス取得
	static GameData* GetInstance();

	//取得関係
	//ゲームの時間を取得
	int GetGameTime() { return gameTime; }

	//フォントデータを取得
	int GetFontHandle() { return fontHandle; }

	//現在のシーンを取得
	SCENE_ID GetSceneID() { return sceneID; }

	//現在のステージを取得
	STAGE_TYPE GetStageType() { return stageType; }

	//セット関係
	//ゲームの時間をセット
	void SetGameTime(int game_time) { gameTime = game_time; }

	//ゲームの時間をセット
	void SetFontHandle(int font_handle) { fontHandle = font_handle; }

	//シーンをセット
	void SetSceneID(SCENE_ID scene_id) { sceneID = scene_id; }

	//ステージをセット
	void SetStageType(STAGE_TYPE stage_type) { stageType = stage_type; }
};