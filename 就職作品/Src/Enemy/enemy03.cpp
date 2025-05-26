#include "enemy03.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//コンストラクタ
Enemy03::Enemy03() {

}


//初期化
void Enemy03::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/enemy3.mv1");
	size = ENEMY_SIZE;
	attackPower = ENEMY_ATTACK_POWER;

	point = ENEMY_03_POINT;

	//アニメーション関係初期化
	InitAnim(ENEMY_ANIMATION_NUM);
}


//通常処理
void Enemy03::Step() {

	if (playerPos.y != -1 && HP > 0) {
		UpdateDamage(ENEMY_MAX_DAMAGE_COUNT);
		Move();
		Attack();
	}

	knockBack();

	TickEnemy();

	Animation();
}


//描画
void Enemy03::Draw() {
	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);
	MV1DrawModel(modelHandle);
}


//破棄	
void Enemy03::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
}


//移動処理
void Enemy03::Move() {

	speed = 0;


	if (!attack) {

		//範囲外に出ると戻るフラグをオン
		if (!Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
			returnFlag = true;
		}
		if (!returnFlag) {//プレイヤー位置へ移動
			if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
				FollowMove(ENEMY_03_MOVE_SPEED);
			}
			else {//自由な移動
				PatrolMove(ENEMY_03_MOVE_SPEED);
			}
		}
		else {//戻るフラグがオンなら元の位置へ
			ReturnMove(ENEMY_03_MOVE_SPEED);
			if (Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, 1)) {
				returnFlag = false;
			}
		}
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//攻撃処理
void Enemy03::Attack() {

	if (!attack) {
	//プレイヤーの目の前で攻撃
		if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_03_ATTACK_SIZE) || lock2) {
			playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
			speed = 0.0f;
			rot.y = playerRadian + MyLib::GetRadian(180);
			attack = true;
		}
	}
}


//アニメーション
void Enemy03::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (damage) {//被ダメージ
			if (curAnim != ENEMY_DAMAGE) {
				ChangeAnim(ENEMY_DAMAGE);
			}
		}
		else if (attack) {//攻撃
			if (curAnim != ENEMY_ATTACK) {
				ChangeAnim(ENEMY_ATTACK);
				if (GetRand(1) == 0) {
					animCount = 10;
				}
			}
		}
		else if (speed != 0) {//歩き
			if (curAnim != ENEMY_WALK) {
				ChangeAnim(ENEMY_WALK);
			}
		}
		else {
			if (curAnim != ENEMY_IDLE) {//待機
				ChangeAnim(ENEMY_IDLE);
			}
		}
	}


	//アニメーション更新
	UpdateAnim();


	//アニメーションを再生し終えたら最初に戻す
	if (animCount >= animAllTime) {
		if (attack) { attack = false; }

		animCount = 0;
		if (HP <= 0) { alive = false; }
	}
}


//攻撃の最中か
bool Enemy03::GetAttack() {

	if (animCount >= ENEMY_03_ATTACK_DAMAGE_START_TIME && animCount <= ENEMY_03_ATTACK_DAMAGE_FIN_TIME && curAnim == ENEMY_ATTACK) {
		attackPos.x = pos.x;
		attackPos.y = pos.y;
		attackPos.z = pos.z;
		attackSize = ENEMY_03_ATTACK_SIZE;
		return true;
	}
	return false;
}


//スポーン処理
void Enemy03::spawn(VECTOR spawn_pos) {
	pos = spawn_pos;
	spawnPos = spawn_pos;
	HP = ENEMY_MAX_HP;
	damage = false;
	alive = true;
}