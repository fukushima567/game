#pragma once
#include "enemy01.h"
#include "enemy02.h"
#include "enemy03.h"
#include "enemy04.h"
#include "boss.h"


constexpr int MAX_ENEMY_NUM = 20;			//敵最大のスポーン数
constexpr int ENEMY_SPAWN_TIME = 240;		//敵スポーンまでの時間


//敵スポーンデータパス名
constexpr char SPAWN_PATH[5][256] = {
	"data/spawn_s0.bin",
	"data/spawn_s1.bin",
	"data/spawn_s2.bin",
	"data/spawn_s3.bin",
	"data/spawn_s4.bin",
};


//敵マネージャークラス
class EnemyManager {
public:

	Enemy* enemy[MAX_ENEMY_NUM+1];		//敵ベースクラス
	
private:

	VECTOR spawnPos[MAX_ENEMY_NUM];		//スポーン座標

	int enemyEffect;					//敵のエフェクト
	int spawnCount[MAX_ENEMY_NUM];		//スポーン時間

	bool edit;							//スポーンデータ作成フラグ
	int editIndex;						//スポーンデータ選択中添え字

public:

	EnemyManager();
	~EnemyManager(){}

	//初期化
	void Init();

	//通常処理
	void Step(VECTOR player_pos, bool is_spawn,bool is_stop);

	//描画処理
	void Draw();

	//破棄処理
	void Delete();
	
private:

	//スポーンデータの読み込み
	void RoadSpawnData();

	//スポーンデータの作成
	void SpawnEditor();

};