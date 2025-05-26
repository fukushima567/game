#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../StageObject/stage.h"
#include "../../Enemy/enemyManager.h"
#include "../../Collision/SceneCollision.h"
#include "../../UI/playUI.h"


//プレイシーンの状態
enum SCENE_PLAY_STATE {
	SCENE_PLAY_START,		//開始時
	SCENE_PLAY_GAME,		//ゲーム中	
	SCENE_PLAY_CLEAR,		//クリア時
	SCENE_PLAY_GAME_OVER,	//ゲームオーバー時
	SCENE_PLAY_NUM
};


//プレイシーンクラス
class ScenePlay :public SceneBase {
private:

	//プレイシーン画像
	int startHandle[2];				//開始前画像
	int tutorialHandle[6];			//チュートリアル画像
	int clearHandle[2];				//クリア画像
	
	//チュートリアル関係
	bool tutorial;					//チュートリアル表示フラグ
	int page;						//チュートリアルの現ページ数

	//クラス
	Player player;					//プレイヤー
	CameraManager cameraManager;	//カメラマネージャー
	Stage stage;					//ステージ
	Gauge gauge;					//ゲージ
	EnemyManager enemyManager;		//敵マネージャー
	SceneCollision sceneCollision;	//コリジョン
	PlayUI ui;
	
	bool pause;						//ポーズフラグ
	bool fade;						//フェードフラグ
	int sceneState;					//シーンの状態
	int sceneStateCount;			//シーン遷移カウント

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
