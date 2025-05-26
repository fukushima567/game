#pragma once
#include "../Common.h"
#include "enemy.h"


constexpr float ENEMY_01_MOVE_SPEED = 0.5f;						//敵1移動速度
constexpr float ENEMY_01_ATTACK_SIZE = 20.0f;					//敵1攻撃のサイズ
constexpr float ENEMY_01_ATTACK_DAMAGE_TIME = 38.0f;			//敵1攻撃のダメージ発生アニメ時間
constexpr float ENEMY_01_ATTACK_RADIUS = -10.0f;				//攻撃位置と敵1位置の距離
constexpr float	ENEMY_01_POINT = 10.0f;							//敵１のポイント

//敵01クラス
class Enemy01 :public Enemy {
private:


public:

	Enemy01();
	~Enemy01(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄	
	void Delete();
	
private:

	//移動
	void Move();

	//攻撃
	void Attack();

	//アニメーション
	void Animation();

public:

	//攻撃の最中か
	bool GetAttack();

	//スポーン処理
	void spawn(VECTOR spawn_pos);
};