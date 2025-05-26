#pragma once
#include "../Common.h"
#include "enemy.h"


//敵関係
constexpr float	ENEMY_03_POINT = 40.0f;							//敵３のポイント
constexpr float ENEMY_03_ATTACK_SIZE = 30.0f;					//敵3攻撃のサイズ
constexpr float ENEMY_03_MOVE_SPEED = 0.8f;						//敵3移動速度
constexpr float ENEMY_03_ATTACK_DAMAGE_START_TIME = 25.0f;		//敵3の攻撃ダメージ発生アニメ時間
constexpr float ENEMY_03_ATTACK_DAMAGE_FIN_TIME = 40.0f;		//敵3の攻撃ダメージ終了アニメ時間


//敵02クラス
class Enemy03 :public Enemy {
private:


public:

	Enemy03();
	~Enemy03(){};

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

	//アニメーション
	void Animation();

public:

	//攻撃の最中か
	bool GetAttack();

	//スポーン処理
	void spawn(VECTOR spawn_pos);
};