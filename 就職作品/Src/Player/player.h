#pragma once
#include "../Character/character.h"


//基本
constexpr VECTOR FIRST_POS = { 0.0f,10.0f,0.0f };		//プレイヤー初期座標
constexpr int	PLAYER_SPHERE = 5;						//プレイヤー当たり判定サイズ
constexpr int	MAX_HP = 100;							//プレイヤー最大HP
constexpr int	SUB_HP = 20;							//落下時のHP減少量
constexpr int	MAX_STAMINA_GAUGE = 6000;				//スタミナ最大値
constexpr int	STAMINA_ADD_NUM = 30;					//スタミナ増加量
constexpr int	STAMINA_SUB_NUM = 15;					//スタミナ減少量
constexpr int	DAMAGE_INTERVAL = 36;					//ダメージを受けるまでのインターバル
constexpr int	AVOID_INVINCIBLE = 30;					//回避時の無敵時間
constexpr int	COMBO_TIME = 320;						//コンボ持続時間
constexpr float MAX_AVOID_COUNT = 10.0f;				//回避のカウント
constexpr float SUB_AVOID_COUNT = 0.45f;				//回避カウントの減少量
constexpr float PLAYER_MIN_Y = -150.0f;					//プレイヤーの動ける最低Y座標


//移動関係
constexpr float WALK_SPEED = 1.5f;						//歩き速度
constexpr float DASH_SPEED = 2.5f;						//走り基礎速度
constexpr float ADD_DASH_SPEED = 0.2f;					//走り速度増加量
constexpr float SUB_DASH_SPEED = 80.0f;					//走り速度減少量
constexpr float MAX_DASH_SPEED_NUM = 3.0f;				//走り現在の最大速度決定用
constexpr float SP_DASH_ATTACK_SPEED = 7.7f;			//強化状態攻撃時の速度
constexpr float MAX_SPEED = 7.5f;						//プレイヤー速度上限
constexpr float WALK_ANIM_COUNT_1 = 4.0f;				//1歩目歩きサウンド再生開始カウント
constexpr float WALK_ANIM_COUNT_2 = 14.0f;				//2歩目歩きサウンド再生開始カウント
constexpr float DASH_ANIM_COUNT_1 = 3.0f;				//1歩目走りサウンド再生開始カウント
constexpr float DASH_ANIM_COUNT_2 = 9.0f;				//2歩目走りサウンド再生開始カウント


//攻撃関係
constexpr int	NOMAL_ATTACK_POWER = 1;					//通常攻撃の攻撃力
constexpr int	NOMAL_DASH_ATTACK_POWER = 2;			//ダッシュ攻撃基礎攻撃力
constexpr int	HIT_STOP_NORMAL = 1;					//通常攻撃のヒットストップ
constexpr int	HIT_STOP_DASH = 20;						//ダッシュ攻撃のヒットストップ
constexpr int	HIT_STOP_CLEAR = 50;					//クリア時のヒットストップ
constexpr float ATTACK_SIZE_1 = 10.0f;					//攻撃のサイズ
constexpr float ATTACK_RANGE = 10.0f;					//プレイヤーと攻撃の距離
constexpr float ATTACK_DASH_MIN = 2.0f;					//ダッシュ攻撃発生カウント
constexpr float ATTACK_DASH_MAX = 6.0f;					//ダッシュ攻撃終了カウント
constexpr float ATTACK_MISS_TIME = 15.0f;				//ダッシュ攻撃ミスのノックバック時間
constexpr float ATTACK_MISS_NUM = -1.0f;				//ダッシュ攻撃ミスのノックバック量
constexpr float ATTACK_NORMAL_MIN = 3.0f;				//通常攻撃発生カウント


//必殺技関係
constexpr int MAX_SP_GAUGE = 400;						//必殺技の時間
constexpr int DASH_ATTACK_COUNT_SP_1 = 10;				//必殺技1に必要なダッシュ攻撃数
constexpr int DASH_ATTACK_COUNT_SP_2 = 20;				//必殺技2に必要なダッシュ攻撃数
constexpr int DASH_ATTACK_COUNT_SP_3 = 30;				//必殺技3に必要なダッシュ攻撃数
constexpr int HIT_STOP_SPECIAL = 1;						//必殺技のヒットストップ


//マテリアル関係
constexpr COLOR_F COLOR_NONE = { 0.0f,0.0f,0.0f,0.0f };	//発光なし
constexpr COLOR_F COLOR_RED = { 0.7f,0.0f,0.0f,1.0f };	//必殺技の発光色
constexpr int	PLAYER_MATERIAL_NUM = 4;				//プレイヤーのマテリアル数
constexpr int	SWORD_MATERIAL_NUM = 3;					//武器のマテリアル数
constexpr float	MAX_SWORD_COLOR = 10.0f;				//武器の最大発光



//回避のタイプ
enum AVOID_TYPE {
	AVOID_NONE,		//回避していない
	AVOID_LEFT,		//左回避
	AVOID_RIGHT,	//右回避
	AVOID_BACK		//後ろ回避
};


//攻撃の種類
enum PLAYER_ATTACK_TYPE {
	PLAYER_ATTACK_NONE,		//攻撃していない
	PLAYER_ATTACK_NORMAL,	//通常攻撃
	PLAYER_ATTACK_DASH,		//ダッシュ攻撃
	PLAYER_ATTACK_SPECIAL	//必殺技攻撃
};


//必殺技の状態
enum SPECIAL_STATE {
	SPECIAL_NONE,	//必殺技未発動
	SPECIAL_READY,	//必殺技予備動作
	SPECIAL_ACTIVE,	//必殺技発動
	SPECIAL_FINISH	//必殺技終了
};


//アニメーションの種類
enum PLAYER_ANIMATION {
	PLAYER_IDLE,			//待機
	PLAYER_WALK,			//通常移動
	PLAYER_DASH,			//ダッシュ
	PLAYER_LEFT_STEP,		//左回避
	PLAYER_RIGHT_STEP,		//右回避
	PLAYER_BACK_STEP,		//後ろ回避
	PLAYER_NOMAL_ATTACK,	//通常攻撃
	PLAYER_DASH_ATTACK,		//ダッシュ攻撃
	PLAYER_DASH_AFTER,		//ダッシュ攻撃後
	PLAYER_DASH_ATTACK_2,	//強化状態時のダッシュ攻撃
	PLAYER_SPECIAL,			//強化状態移行
	PLAYER_AIR,				//空中
	PLAYER_MISS,			//攻撃失敗のけぞり
	PLAYER_DAMAGE,			//被ダメージ
	PLAYER_DATH,			//やられ
	PLAYER_CLEAR,			//クリア

	PLAYER_ANIMATION_NUM	//アニメーション総数
};


//エフェクトの種類
enum PLAYER_EFFECT {
	PLAYER_EFFECT_ATTACK,	//ダッシュ攻撃
	PLAYER_EFFECT_SP,		//必殺技発動時
	PLAYER_EFFECT_SP_ATTACK,//必殺技発動中

	PLAYER_EFFECT_NUM		//プレイヤーエフェクト総数
};


//プレイヤークラス
class Player :public Character{
private:

	int toolHandle;			//武器モデルハンドル
	int frameIndex;			//武器のフレーム添え字

	VECTOR rot;				//プレイヤー回転
	VECTOR cameraRot;		//カメラの回転
	MATRIX toolPos;			//武器の座標
	
	bool ground;			//地面接地フラグ
	bool lockOn;			//ロックオンフラグ

	int dashAttackCount;	//ダッシュ攻撃ヒット数
	int invincibleCount;	//無敵時間のカウント

	float combo;			//コンボ数
	int	  comboCount;		//コンボ時間
	float nearEneRad;		//近くにいる敵との角度

	//ダッシュ関係
	bool drawDash;			//ダッシュエフェクト表示フラグ
	bool finishDash;		//ダッシュ終了フラグ
	int	staminaGauge;		//スタミナ
	int avoidType;			//回避の種類
	float avoidCount;		//回避の時間
	float currentMaxSpeed;	//現在の加速可能な最大速度
	float dashSub;			//ダッシュ速度減少量

	//攻撃関係
	bool attackFlag;		//攻撃フラグ
	bool attackHit;			//攻撃命中フラグ
	bool attackMiss;		//攻撃失敗フラグ
	int attackType;			//攻撃の種類
	
	//必殺技関係
	int specialState;		//必殺技の状態
	int specialGauge;		//必殺技のゲージ

	//ヒットストップ関係
	bool hitStop;			//ヒットストップのフラグ
	int hitStopNum;			//ヒットストップ時間
	int hitStopCount;		//ヒットストップ時間のカウント

	//被ダメージ関係
	bool damageFlag;		//被ダメージフラグ
	int	damageNum;			//被ダメージ量
	float damageRot;		//ダメージを受けた角度

	//エフェクト関係
	bool effectRequest;						//エフェクトリクエストフラグ
	int	 effectHandle[PLAYER_EFFECT_NUM];	//エフェクトハンドル
	int  effectIndex[PLAYER_EFFECT_NUM];	//エフェクトナンバー

	//関数
public:

	Player();
	~Player(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄	
	void Delete();

private:

	//歩き処理
	void Walk();

	//走り処理
	void Dash();

	//回避処理
	void Avoid();

	//必殺技処理
	void Special();

	//ノックバック処理
	void KnockBack();

	//攻撃処理
	void Attack();

	//アニメーション
	void Animation();

	//エフェクト処理
	void Effect();

public:

	//クリア時の処理
	void clear();

	//ダメージを受ける処理
	void Damage(VECTOR enemy_pos, int damage);

	//コンボ処理
	void Combo();

	//ダッシュ攻撃失敗処理
	void AttackMiss();

	//床についた際の処理
	void Ground();

	//取得関係
	//攻撃フラグを得る
	bool GetAttackFlag() { return attackFlag; }

	//敵に攻撃が当たった瞬間か
	bool GetAttackHit() { return attackHit; }

	//ロックオン中か
	bool GetLockOn() { return lockOn; }

	//ヒットストップ中か
	bool GetHitStop() { return hitStop; }

	//ダッシュエフェクトを描画するか
	bool GetDrawScreenEffect() { return drawDash; }

	//ダメージを受けた瞬間か
	bool GetDamage();

	//ダッシュ状態か
	bool GetIsDash();

	//スタミナを得る
	int GetStaminaGauge() { return staminaGauge; }

	//必殺技の状態を得る
	int GetSpecialState() { return specialState; }

	//強化状態の時間を得る
	int GetSpecialGauge() { return specialGauge; }

	//ダッシュ攻撃を当てた回数を得る
	int GetDashAttackCount() { return dashAttackCount; }

	//コンボ数を得る
	float GetCombo() { return combo; }

	//コンボ時間を得る
	int GetComboCount() { return comboCount; }

	//被ダメージ量を得る
	int GetDamageNum() { return damageNum; }

	//現在の移動速度を得る
	float GetSpeed() { return speed; }

	//回転値を得る
	float GetRot() { return rot.y; }

	//一番近い敵の角度を得る
	float GetEneRad();

	//セット関係
	//カメラの向いている方向をセット
	void SetCameraRad(VECTOR camera_rot) { cameraRot = camera_rot; }

	//一番近い敵との角度をセット
	void SetNearEneRad(float ene_rad);

	//ヒットストップをオンにする
	void SetHitStop(bool max = false);
};