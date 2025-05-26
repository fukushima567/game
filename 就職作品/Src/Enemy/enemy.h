#pragma once
#include "../Character/character.h"


//敵
constexpr int	ENEMY_MAX_HP = 2;					//敵の最大HP
constexpr int	ENEMY_MAX_MOVE_INTERVAL = 180;		//敵の移動間隔
constexpr float ENEMY_SIZE = 8.0f;					//敵サイズ
constexpr float ENEMY_KILL_Y = -200.0f;				//敵最小Y座標

//ノックバック関係
constexpr float ENEMY_KNOCK_BACK_RAD = 0.7f;		//ノックバック角度
constexpr float ENEMY_KNOCK_BACK_MAX_NUM = 15.0f;	//ノックバック最大値
constexpr float ENEMY_KNOCK_BACK_SUB_NUM = 0.5f;	//ノックバック値減少量


//弾関係
constexpr int	ENEMY_MAX_BULLET = 12;				//弾最大数
constexpr int	ENEMY_ATTACK_POWER = 5;				//敵攻撃力
constexpr int	ENEMY_MAX_DAMAGE_COUNT = 60;		//敵のダメージ硬直時間
constexpr float ENEMY_MOVE_RANGE = 150.0f;			//敵の移動できる距離



//敵のアニメーションの種類
enum ENEMY_ANIMATION {
	ENEMY_IDLE,			//待機
	ENEMY_WALK,			//移動
	ENEMY_ATTACK,		//攻撃
	ENEMY_DAMAGE,		//被ダメージ

	ENEMY_ANIMATION_NUM	//アニメーション総数
};


//敵基底クラス
class Enemy :public Character {
protected:

	VECTOR playerPos;						//プレイヤー座標
	VECTOR spawnPos;						//スポーン座標
	VECTOR rot;								//回転

	//移動関係
	bool moveFlag;							//移動中か
	int moveInterval;						//移動のインターバル
	int moveIntervalCount;					//移動のインターバルカウント

	//プレイヤー関係
	float playerRadian;						//プレイヤーの角度
	bool  hitStop;							//プレイヤーのヒットストップ
	bool lock;								//通常時ロックオンフラグ
	bool lock2;								//ダッシュ時ロックオンフラグ

	bool returnFlag;						//初期位置へ戻るフラグ
	bool ground;							//地面にいるか
	bool attack;							//攻撃中か
	bool alive;								//生存フラグ
	float  point;							//ポイント

	//弾関係
	int bulletHandle;						//弾モデルのハンドル
	VECTOR bulletPos[ENEMY_MAX_BULLET];		//弾の座標
	float bulletSize;						//弾のサイズ
	bool bulletUse;							//弾を使用するか
	bool bulletActive[ENEMY_MAX_BULLET];	//弾が出ているか
	int bulletInterval;						//弾のインターバル

	//ダメージ関係
	bool  damage;							//ダメージを受けているか
	int	  damageCount;						//ダメージのインターバル
	int	  damageNum;						//ダメージ量
	
	//ノックバック関係
	bool knockBackFlag;						//ノックバックフラグ
	float knockBackNum;						//ノックバック量
	float knockBackRad;						//ノックバックの方向

public:

	Enemy();
	~Enemy(){};

	//初期化
	virtual void Init() = 0;

	//通常処理
	virtual void Step() = 0;

	//描画
	virtual void Draw() = 0;

	//破棄
	virtual void Delete() = 0;

	//スポーン処理
	virtual void spawn(VECTOR spawn_pos) = 0;

	//ダメージを受ける
	void Damage(int damage_num);

protected:

	//ダメージを更新
	void UpdateDamage(int max_count);

	//ノックバック処理
	void knockBack();

	//毎フレーム行う敵共通の処理
	void TickEnemy();

	//敵の巡回移動処理
	void PatrolMove(float patroll_speed);

	//敵の初期位置への移動処理
	void ReturnMove(float return_speed);

	//敵のプレイヤー追従
	void FollowMove(float follow_speed);

public:

	//取得関係
	//攻撃の最中か
	virtual bool GetAttack() = 0;

	//ダメージを受けた瞬間を得る
	bool GetDamageHit();

	//ダメージを受けた瞬間を得る(ボス)
	bool GetDamageHit2();

	//ダメージを受けたかを得る
	bool GetDamage() { return damage; }

	//生存状況を得る
	bool GetAlive() { return alive; }

	//ロックオンされているか
	bool GetLock() { return lock; }

	//ダッシュ中にロックオンされているか
	bool GetLock2() { return lock2; }

	//弾を使用するか得る
	bool GetBulletUse() { return bulletUse; }

	//弾の使用状態を得る
	bool GetBulletActive(int index) { return bulletActive[index]; }

	//弾の座標を得る
	VECTOR GetBulletPos(int index) { return bulletPos[index]; }

	//弾のサイズを得る
	float GetBulletSize() { return bulletSize; }

	//被ダメージ量を得る
	int GetDamageNum() { return damageNum; }
	
	//ポイント量を得る
	float GetPoint() { return point; }

	//セット関係
	//生存状態をセット
	void SetAlive(bool state = false) { alive = state; }

	//床についた際の処理
	void Ground() { ground = true; }

	//通常時ロックオン状態をセット
	void SetLock(bool is_lock) { lock = is_lock; }

	//ダッシュ中ロックオン状態をセット
	void SetLock2(bool is_lock) { lock2 = is_lock; }

	//プレイヤー座標をセット
	void SetPlayerPos(VECTOR player_pos) { playerPos = player_pos; }

	//ノックバックの方向をセット
	void SetKnockBackRad(float rad) { knockBackRad = rad; }

	//プレイヤーのヒットストップをセット
	void SetHitStop(bool flag) { hitStop = flag; }
};