#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


constexpr float ANIM_BLEND_NUM = 0.2f;	//アニメーションブレンド変化量
constexpr float ANIM_MAX_BLRND = 1.0f;	//アニメーションブレンドの最大値
constexpr float ANIM_COUNT = 0.5f;		//アニメーション時間の通常増加量


//キャラクタークラス
class Character {
protected:

	int modelHandle;	//モデルハンドル

	VECTOR pos;			//座標
	float size;			//サイズ

	int HP;				//体力
	float speed;		//移動速度

	//攻撃関係
	VECTOR attackPos;	//攻撃の座標
	int attackPower;	//攻撃力
	float attackSize;	//攻撃のサイズ

	//アニメーション関係
	int* animIndex;		//アニメーションのアタッチ番号
	int curAnim;		//現在のアニメーション
	int preAnim;		//前のアニメーション
	float* animBlend;	//アニメーションブレンド率
	float animNum;		//アニメーションカウント増加量
	float animCount;	//アニメーションカウント
	float animAllTime;	//アニメーション総時間

public:

	Character();
	~Character(){}

	//初期化
	virtual void Init() = 0;

	//通常処理
	virtual void Step() = 0;

	//描画
	virtual void Draw() = 0;

	//破棄
	virtual void Delete() = 0;

	//アニメーション
	virtual void Animation() = 0;

	//アニメーションの初期化
	void InitAnim(int anim_num);

	//アニメーション変更
	void ChangeAnim(int anim_type);

	//アニメーションの更新
	void UpdateAnim();

	//アニメーション破棄
	void DeleteAnim();

	//座標を得る
	VECTOR GetPos() { return pos; }

	//サイズを得る
	float GetSize() { return size; }

	//攻撃の座標を得る
	VECTOR GetAttackPos() { return attackPos; }

	//攻撃のサイズを得る
	float GetAttackSize() { return attackSize; }

	//攻撃力を得る
	int GetAttackPower() { return attackPower; }

	//HPを得る
	int GetHP() { return HP; }

	//座標をセット
	void SetPos(VECTOR set_pos) { pos = set_pos; }
};