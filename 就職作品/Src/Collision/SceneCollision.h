#pragma once

#include "../Player/player.h"
#include "../Enemy/enemyManager.h"
#include "../StageObject/gauge.h"
#include "../StageObject/stage.h"
#include "../Camera/cameraManager.h"


constexpr int LOCK_CAST_TIME = 20;		//ロックオン切り替えのクールタイム


//プレイシーンの当たり判定
class SceneCollision {

private:

	int lockChangeCount;	//ロックオン切り替えカウント

public:

	SceneCollision();
	~SceneCollision(){}

	//プレイヤーとステージの当たり判定
	void PlayerAndStage(Player* player, Stage* stage);

	//敵とステージの当たり判定
	void EnemyAndStage(EnemyManager* enemyManager,Stage* stage);

	//敵同士の当たり判定
	void EnemyAndEnemy(EnemyManager* enemyManager);

	//プレイヤーと敵の当たり判定
	void PlayerAndEnemy(Player *player,EnemyManager *enemyManager);

	//プレイヤーのロックオン判定
	void LockOn(Player* player, EnemyManager* enemyManager ,Stage* stage,bool is_lock);

	//プレイヤーの攻撃と敵の当たり判定
	void PlayerAttackAndEnemy(Player* player, EnemyManager* enemyManager, Gauge* gauge);

	//プレイヤーと敵の攻撃の当たり判定
	void PlayerAndEnemyAttack(Player* player, EnemyManager* enemyManager);

	//プレイヤーと敵弾の当たり判定
	void PlayerAndEnemyBullet(Player* player, EnemyManager* enemyManager);
};