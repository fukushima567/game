#include "boss.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//コンストラクタ
EnemyBoss::EnemyBoss() {

	AoE = 0;
	attackType = 0;
	bulletAlpha = 0.0f;
	down = false;
}


//初期化
void EnemyBoss::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/boss.mv1");
	bulletHandle = MV1LoadModel("data/Image/Play/Enemy/bossBullet.mv1");
	AoE=LoadGraph("data/Image/Play/Enemy/AoE.png");

	pos = BOSS_FIRST_POS;
	size = BOSS_SIZE;

	bulletUse = true;
	bulletSize = BOSS_BULLET_SIZE;

	HP = BOSS_MAX_HP;
	alive = true;

	//アニメーション関係初期化
	InitAnim(BOSS_ANIMATION_NUM);
}


//通常処理
void EnemyBoss::Step() {

	if (HP <= 0) { 
		down = true;
		HP = BOSS_MAX_HP;
	}

	//生きていたら実行
	if (playerPos.y != -1&&HP > 0&&!damage) {
		Move();
		Attack();
		Bullet();
	}

	UpdateDamage(BOSS_MAX_DAMAGE_COUNT);

	Animation();

	lock2 = false;

	pos.y = 0;
}


//描画
void EnemyBoss::Draw() {

	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);

	MV1DrawModel(modelHandle);

	//遠距離攻撃発動時、弾を描画
	if (curAnim == BOSS_ATTACK_3) {
		for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
			if (animCount > 0 && animCount < BOSS_AOE_DRAW_TIME) {
				MyLib::Draw3DImageGround(AoE, bulletPos[index], BOSS_BULLET_SIZE, BOSS_BULLET_SIZE);
			}
			MV1SetPosition(bulletHandle, bulletPos[index]);

			MV1SetOpacityRate(bulletHandle, bulletAlpha);
			MV1DrawModel(bulletHandle);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
}


//破棄	
void EnemyBoss::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(bulletHandle);
	DeleteGraph(AoE);
}


//ボスの移動
void EnemyBoss::Move() {

	playerRadian = 0.0f;
	speed = 0.0f;


	//攻撃中でなければ実行
	if (attackType == BOSS_ATTACK_NONE) {

		//移動
		playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
		speed = BOSS_MOVE_SPEED;
		rot.y = playerRadian + MyLib::GetRadian(180);
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//攻撃
void EnemyBoss::Attack() {
	
	//攻撃中でなければ実行
	if (attackType == BOSS_ATTACK_NONE) {

		//近距離攻撃
		if (Collision::Circle(playerPos.x, playerPos.z, 1.0f, pos.x, pos.z, BOSS_ATTACK_RANGE)) {
			playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
			speed = 0.0f;
			rot.y = playerRadian + MyLib::GetRadian(180);
			attackType = GetRand(BOSS_ATTACK_NORMAL_2);
			attackPos.x = MyLib::GetCircleY(pos.x, BOSS_ATTACK_RADIUS, rot.y);
			attackPos.y = pos.y;
			attackPos.z = MyLib::GetCircleX(pos.z, BOSS_ATTACK_RADIUS, rot.y);
			attackSize = BOSS_ATTACK_SIZE;
			attackPower = BOSS_ATTACK_POWER_NORMAL;

		}//遠距離攻撃
		else if (bulletInterval > BOSS_SPAWN_BULLET_TIME) {
			attackType = BOSS_ATTACK_BULLET;
			bulletInterval = 0;
			bulletAlpha = 1.0f;
			attackPower = BOSS_ATTACK_POWER_BULLET;
			
			//弾の出現
			for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
				bulletPos[index].x = (float)GetRand(600) - 200;
				bulletPos[index].y = BOSS_BULLET_SPAWN_Y_POS;
				bulletPos[index].z = (float)GetRand(1000) - 100;
				bulletActive[index] = true;
			}
		}
	}
}


//弾の処理
void EnemyBoss::Bullet() {

	//インターバルを加算
	bulletInterval++;

	//弾の移動
	if (curAnim == BOSS_ATTACK_3 && animCount > BOSS_AOE_DRAW_TIME) {
		for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
			bulletPos[index].y -= BOSS_BULLET_MOVE_SPEED;
			if (bulletPos[index].y < 0) {
				bulletPos[index].y = 0;
			}
			if (bulletInterval > BOSS_BULLET_START_MOVE_TIME) {
				bulletAlpha -= BOSS_BULLET_SUB_ALPHA;
				if (bulletAlpha < 0) {
					bulletAlpha = 0;
				}
			}
		}
	}
	
	//弾消滅処理
	if (animCount > BOSS_BULLET_DELETE_TIME) {
		for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
			bulletActive[index] = false;
		}
	}
}


//アニメーション
void EnemyBoss::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (down) {//ダウン
			if (curAnim != BOSS_DOWN) {
				ChangeAnim(BOSS_DOWN);
			}
		}
		else if (attackType == 1) {//攻撃1
			if (curAnim != BOSS_ATTACK_1) {
				ChangeAnim(BOSS_ATTACK_1);
			}
		}
		else if (attackType == 2) {//攻撃２
			if (curAnim != BOSS_ATTACK_2) {
				ChangeAnim(BOSS_ATTACK_2);
			}
		}
		else if (attackType == 3) {//攻撃3
			if (curAnim != BOSS_ATTACK_3) {
				ChangeAnim(BOSS_ATTACK_3);
			}
		}
		else if (speed != 0) {//歩き
			if (curAnim != BOSS_WALK) {
				ChangeAnim(BOSS_WALK);
			}
		}
		else {//待機
			if (curAnim != BOSS_IDLE) {
				ChangeAnim(BOSS_IDLE);
			}
		}
	}

	//アニメーション更新
	UpdateAnim();

	//アニメーションを再生し終えたら最初に戻す
	if (animCount >= animAllTime) {
		if (curAnim == BOSS_ATTACK_1|| curAnim == BOSS_ATTACK_2 || curAnim == BOSS_ATTACK_3) { attackType = 0; }
		down = false;
		animCount = 0;
	}
}


//攻撃の最中か
bool EnemyBoss::GetAttack() {

	if (animCount == BOSS_ATTACK_1_DAMAGE_TIME && curAnim == BOSS_ATTACK_1||
		curAnim == BOSS_ATTACK_2 && animCount > BOSS_ATTACK_2_DAMAGE_START_TIME && animCount < BOSS_ATTACK_2_DAMAGE_FIN_TIME ||
		curAnim == BOSS_ATTACK_2 && animCount == BOSS_ATTACK_2_DAMAGE_LAST_TIME) {
		return true;
	}
	return false;
}