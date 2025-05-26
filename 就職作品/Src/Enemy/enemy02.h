#pragma once
#include "../Common.h"
#include "enemy.h"


//敵関係
constexpr float	ENEMY_02_POINT = 30.0f;					//敵2のポイント

//弾関係
constexpr int	ENEMY_02_MAX_BULLET = 3;				//敵2の弾最大数
constexpr int	ENEMY_02_BULLET_INTERVAL = 10;			//敵2の弾インターバル
constexpr float ENEMY_02_BULLET_SIZE = 20.0f;			//敵2弾のサイズ
constexpr float ENEMY_02_BULLET_MOVE_SPEED = 5.0f;		//敵2弾移動速度
constexpr float ENEMY_02_BULLET_Y_POS = 16.0f;			//敵2弾Y座標
constexpr float ENEMY_02_BULLET_START_TIME = 40.0f;		//敵2弾発射アニメ時間
constexpr float ENEMY_02_BULLET_FIN_TIME = 30.0f;		//敵2弾消滅アニメ時間(1つ前の攻撃)



//敵02クラス
class Enemy02 :public Enemy {
private:

	float bulletRadian;

	
public:

	Enemy02();
	~Enemy02(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄	
	void Delete();

private:

	//攻撃処理
	void Attack();

	//弾の処理
	void Bullet();

	//アニメーション
	void Animation();

public:

	//攻撃の最中か
	bool GetAttack();

	//スポーン処理
	void spawn(VECTOR spawn_pos);
};