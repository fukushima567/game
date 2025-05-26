#pragma once
#include "../Common.h"
#include "enemy.h"


//ボスの基本
constexpr VECTOR BOSS_FIRST_POS = { 0.0f,0.0f,800.0f };		//ボスの初期座標
constexpr int	BOSS_MAX_HP = 15;							//ボスの体力
constexpr int	BOSS_MAX_DAMAGE_COUNT = 40;					//ボスのダメージ硬直時間
constexpr float BOSS_SIZE = 35.0f;							//ボスのサイズ
constexpr float BOSS_MOVE_SPEED = 1.0f;						//ボスの移動速度


//近距離攻撃関係
constexpr int	BOSS_ATTACK_POWER_NORMAL = 20;				//ボスの近接攻撃力
constexpr float BOSS_ATTACK_RANGE = 70.0f;					//近接攻撃が開始される範囲
constexpr float BOSS_ATTACK_SIZE = 60.0f;					//近接攻撃のサイズ
constexpr float BOSS_ATTACK_RADIUS = -10.0f;				//近接攻撃とボスの距離
constexpr float BOSS_ATTACK_1_DAMAGE_TIME = 140.0f;			//近距離攻撃1のダメージ発生アニメ時間
constexpr float BOSS_ATTACK_2_DAMAGE_START_TIME = 155.0f;	//近距離攻撃2のダメージ発生アニメ時間
constexpr float BOSS_ATTACK_2_DAMAGE_FIN_TIME = 218.0f;		//近距離攻撃2のダメージ終了アニメ時間
constexpr float BOSS_ATTACK_2_DAMAGE_LAST_TIME = 250.0f;	//近距離攻撃2の最終ダメージ発生アニメ時間


//弾関係
constexpr int	BOSS_ATTACK_POWER_BULLET = 10;				//ボスの弾攻撃力
constexpr int	BOSS_SPAWN_BULLET_TIME = 240;				//ボスの弾が出現するまでの時間
constexpr float BOSS_BULLET_SIZE = 50.0f;					//ボス弾のサイズ
constexpr float BOSS_BULLET_MOVE_SPEED = 20.0f;				//ボス弾移動速度
constexpr float BOSS_BULLET_SPAWN_Y_POS = 250.0f;			//ボスの弾出現Y座標
constexpr float BOSS_AOE_DRAW_TIME = 50.0f;					//AOEが表示されるアニメ時間
constexpr float BOSS_BULLET_START_MOVE_TIME = 180.0f;		//ボスの弾移動開始アニメ時間
constexpr float BOSS_BULLET_DELETE_TIME = 80.0f;			//ボス弾の消滅アニメ時間
constexpr float BOSS_BULLET_SUB_ALPHA = 0.01f;				//ボスの弾アルファ値減少量



//攻撃の種類
enum BOSS_ATTACK_TYPE {
	BOSS_ATTACK_NONE,			//攻撃していない
	BOSS_ATTACK_NORMAL_1,		//近距離攻撃1
	BOSS_ATTACK_NORMAL_2,		//近距離攻撃2
	BOSS_ATTACK_BULLET,			//遠距離攻撃
	BOSS_ATTACK_NUM				//攻撃種類総数
};


//ボスのアニメーションの種類
enum BOSS_ANIMATION {
	BOSS_IDLE,			//待機
	BOSS_WALK,			//移動
	BOSS_ATTACK_1,		//攻撃1
	BOSS_ATTACK_2,		//攻撃2
	BOSS_ATTACK_3,		//攻撃3
	BOSS_DOWN,			//被ダメージ

	BOSS_ANIMATION_NUM	//アニメーション総数
};


//ボスクラス
class EnemyBoss :public Enemy {
private:

	int AoE;				//攻撃の範囲画像
	int attackType;			//攻撃の種類
	float bulletAlpha;		//弾の透明度

	bool down;				//ダウンしているか

	//関数
public:

	EnemyBoss();
	~EnemyBoss(){};

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

	//弾の処理
	void Bullet();

	//アニメーション
	void Animation();

public:
	
	//攻撃の最中か
	bool GetAttack();

	//スポーン処理
	void spawn(VECTOR spawn_pos) { 
		pos = spawn_pos;
		HP = 2;
		damage = false;
		alive = true;
	}
};