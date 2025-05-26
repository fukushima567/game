#include "enemy.h"
#include "../MyLib/myLib.h"


//�R���X�g���N�^
Enemy::Enemy() {

	memset(&playerPos, 0, sizeof(VECTOR));
	memset(&spawnPos, 0, sizeof(VECTOR));
	memset(&rot, 0, sizeof(VECTOR));

	moveFlag = false;
	moveInterval = 0;
	moveIntervalCount = 0;

	playerRadian = 0.0f;
	hitStop = false;

	returnFlag = false;
	ground = false;
	attack = false;
	alive = false;
	point = 0.0f;

	lock = false;
	lock2 = false;

	bulletHandle = 0;
	memset(&bulletPos, 0, sizeof(VECTOR[ENEMY_MAX_BULLET]));
	memset(&bulletActive, 0, sizeof(bool[ENEMY_MAX_BULLET]));
	bulletSize = 0.0f;
	bulletUse = false;
	bulletInterval = 0;

	damage = false;
	damageCount = 0;
	damageNum = 0;

	knockBackFlag = false;
	knockBackNum=0.0f;
	knockBackRad=0.0f;
}


//�_���[�W���󂯂�
void Enemy::Damage(int damage_num) {
	damage = true;
	damageCount = 0;
	HP -= damage_num;
	damageNum = damage_num;
	attack = false;
	if (damage_num != 1) {
		knockBackFlag = true;
		knockBackNum = ENEMY_KNOCK_BACK_MAX_NUM;
	}
}


//�_���[�W�C���^�[�o�����X�V
void Enemy::UpdateDamage(int max_count) {

	if (damage) {
		damageCount++;
		if (damageCount > max_count) {
			damage = false;
		}
	}
}


//�m�b�N�o�b�N����
void Enemy::knockBack() {
	if (knockBackFlag&& !hitStop) {
		pos = MyLib::Get3DCircle(pos, ENEMY_KNOCK_BACK_RAD, knockBackRad, knockBackNum);
		knockBackNum -= ENEMY_KNOCK_BACK_SUB_NUM;
		if (knockBackNum < 0) {
			knockBackFlag = false;
		}
	}
}


//���t���[���s���G���ʂ̏���
void Enemy::TickEnemy() {

	//�d�͂����Z
	if (!ground) {
		pos.y -= GRAVITY;
	}

	if (pos.y < ENEMY_KILL_Y) {
		alive = false;
	}
	moveIntervalCount++;
	ground = false;
	lock2 = false;
}


//�_���[�W���󂯂��u�Ԃ𓾂�
bool Enemy::GetDamageHit() {
	if (damage && animCount == 1 && curAnim == ENEMY_DAMAGE) {
		return true;
	}
	else {
		return false;
	}
}


//�G�̏���ړ�����
void Enemy::PatrolMove(float patroll_speed) {

	patroll_speed = patroll_speed / 3;

	if (moveIntervalCount > moveInterval) {
		moveIntervalCount = 0;
		moveInterval = GetRand(ENEMY_MAX_MOVE_INTERVAL);
		if (moveFlag) {
			moveFlag = false;
		}
		else {
			moveFlag = true;
			playerRadian = MyLib::GetRadian((float)GetRand(360));
			rot.y = playerRadian + MyLib::GetRadian(180);
		}
	}
	if (moveFlag) {
		speed = patroll_speed;
	}
}


//�G�̏����ʒu�ւ̈ړ�����
void Enemy::ReturnMove(float return_speed) {

	playerRadian = MyLib::GetPosRadian(pos.z, pos.x, spawnPos.z, spawnPos.x);
	speed = return_speed;
	rot.y = playerRadian + MyLib::GetRadian(180);

}


//�G�̃v���C���[�Ǐ]
void Enemy::FollowMove(float follow_speed) {

	playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
	speed = follow_speed;
	rot.y = playerRadian + MyLib::GetRadian(180);
}


//�_���[�W���󂯂��u�Ԃ𓾂�(�{�X)
bool Enemy::GetDamageHit2() {
	if (damageCount == 2) {
		return true;
	}
	return false;
}