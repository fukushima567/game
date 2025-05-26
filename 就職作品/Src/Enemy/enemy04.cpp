#include "enemy04.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//コンストラクタ
Enemy04::Enemy04() {

}


//初期化
void Enemy04::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/enemy4.mv1");
	size = ENEMY_SIZE;
	attackPower = ENEMY_ATTACK_POWER;
	point = ENEMY_04_POINT;

	//アニメーション関係初期化
	InitAnim(ENEMY_ANIMATION_NUM);
}


//通常処理
void Enemy04::Step() {

	if(playerPos.y != -1 && HP > 0) {
		UpdateDamage(ENEMY_MAX_DAMAGE_COUNT);
		Move();
		Attack();
	}

	knockBack();

	TickEnemy();

	Animation();
}


//描画
void Enemy04::Draw() {
	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);
	MV1DrawModel(modelHandle);
}


//破棄	
void Enemy04::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
}


//移動処理
void Enemy04::Move() {

	speed = 0;

	if (!attack) {
		
		//範囲外に出ると戻るフラグをオン
		if (!Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
			returnFlag = true;
		}
		if (!returnFlag) {//プレイヤー位置へ移動
			if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
				FollowMove(ENEMY_04_MOVE_SPEED);
			}
			else {//自由な移動
				PatrolMove(ENEMY_04_MOVE_SPEED);
			}
		}
		else {//戻るフラグがオンなら元の位置へ
			ReturnMove(ENEMY_04_MOVE_SPEED);
			if (Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, 1)) {
				returnFlag = false;
			}
		}
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//攻撃処理
void Enemy04::Attack() {

	if (!attack) {
		//プレイヤーの目の前で攻撃
		if (curAnim != ENEMY_ATTACK) {
			if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_04_ATTACK_SIZE) || lock2) {
				playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
				speed = 0.0f;
				rot.y = playerRadian + MyLib::GetRadian(180);
				attack = true;
			}
		}
	}
}


//アニメーション
void Enemy04::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (damage) {//被ダメージ
			if (curAnim != ENEMY_DAMAGE) {
				ChangeAnim(ENEMY_DAMAGE);
			}
		}
		else if (attack) {//攻撃
			if (curAnim != ENEMY_ATTACK) {
				ChangeAnim(ENEMY_ATTACK);
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
bool Enemy04::GetAttack() {

	if (animCount >= ENEMY_04_ATTACK_DAMAGE_START_TIME && animCount <= ENEMY_04_ATTACK_DAMAGE_FIN_TIME && curAnim == ENEMY_ATTACK) {
		attackPos.x = MyLib::GetCircleY(pos.x, ENEMY_04_ATTACK_RADIUS, rot.y);
		attackPos.y = pos.y;
		attackPos.z = MyLib::GetCircleX(pos.z, ENEMY_04_ATTACK_RADIUS, rot.y);
		attackSize = ENEMY_04_ATTACK_SIZE;
		return true;
	}
	return false;
}


//スポーン処理
void Enemy04::spawn(VECTOR spawn_pos) {
	pos = spawn_pos;
	spawnPos = spawn_pos;
	HP = ENEMY_MAX_HP*2;
	damage = false;
	alive = true;
}