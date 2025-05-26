#pragma once
#include "../Common.h"
#include "enemy.h"


constexpr float	ENEMY_04_POINT = 60.0f;							//敵4のポイント
constexpr float ENEMY_04_MOVE_SPEED = 0.5f;
constexpr float ENEMY_04_ATTACK_RADIUS = -10.0f;				//攻撃位置と敵4位置の距離
constexpr float ENEMY_04_ATTACK_SIZE = 12.0f;					//敵4攻撃のサイズ
constexpr float ENEMY_04_ATTACK_DAMAGE_START_TIME = 18.0f;		//敵4の攻撃ダメージ発生アニメ時間
constexpr float ENEMY_04_ATTACK_DAMAGE_FIN_TIME = 105.0f;		//敵4の攻撃ダメージ終了アニメ時間



//敵04クラス
class Enemy04 :public Enemy {
private:


public:

	Enemy04();
	~Enemy04() {};

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄	
	void Delete();

private:

	//移動処理
	void Move();

	//攻撃処理
	void Attack();

public:

	//アニメーション
	void Animation();

	//攻撃の最中か
	bool GetAttack();

	//スポーン処理
	void spawn(VECTOR spawn_pos);
};