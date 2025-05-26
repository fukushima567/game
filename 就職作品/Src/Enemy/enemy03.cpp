#include "enemy03.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//�R���X�g���N�^
Enemy03::Enemy03() {

}


//������
void Enemy03::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/enemy3.mv1");
	size = ENEMY_SIZE;
	attackPower = ENEMY_ATTACK_POWER;

	point = ENEMY_03_POINT;

	//�A�j���[�V�����֌W������
	InitAnim(ENEMY_ANIMATION_NUM);
}


//�ʏ폈��
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


//�`��
void Enemy03::Draw() {
	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);
	MV1DrawModel(modelHandle);
}


//�j��	
void Enemy03::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
}


//�ړ�����
void Enemy03::Move() {

	speed = 0;


	if (!attack) {

		//�͈͊O�ɏo��Ɩ߂�t���O���I��
		if (!Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
			returnFlag = true;
		}
		if (!returnFlag) {//�v���C���[�ʒu�ֈړ�
			if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
				FollowMove(ENEMY_03_MOVE_SPEED);
			}
			else {//���R�Ȉړ�
				PatrolMove(ENEMY_03_MOVE_SPEED);
			}
		}
		else {//�߂�t���O���I���Ȃ猳�̈ʒu��
			ReturnMove(ENEMY_03_MOVE_SPEED);
			if (Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, 1)) {
				returnFlag = false;
			}
		}
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//�U������
void Enemy03::Attack() {

	if (!attack) {
	//�v���C���[�̖ڂ̑O�ōU��
		if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_03_ATTACK_SIZE) || lock2) {
			playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
			speed = 0.0f;
			rot.y = playerRadian + MyLib::GetRadian(180);
			attack = true;
		}
	}
}


//�A�j���[�V����
void Enemy03::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (damage) {//��_���[�W
			if (curAnim != ENEMY_DAMAGE) {
				ChangeAnim(ENEMY_DAMAGE);
			}
		}
		else if (attack) {//�U��
			if (curAnim != ENEMY_ATTACK) {
				ChangeAnim(ENEMY_ATTACK);
				if (GetRand(1) == 0) {
					animCount = 10;
				}
			}
		}
		else if (speed != 0) {//����
			if (curAnim != ENEMY_WALK) {
				ChangeAnim(ENEMY_WALK);
			}
		}
		else {
			if (curAnim != ENEMY_IDLE) {//�ҋ@
				ChangeAnim(ENEMY_IDLE);
			}
		}
	}


	//�A�j���[�V�����X�V
	UpdateAnim();


	//�A�j���[�V�������Đ����I������ŏ��ɖ߂�
	if (animCount >= animAllTime) {
		if (attack) { attack = false; }

		animCount = 0;
		if (HP <= 0) { alive = false; }
	}
}


//�U���̍Œ���
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


//�X�|�[������
void Enemy03::spawn(VECTOR spawn_pos) {
	pos = spawn_pos;
	spawnPos = spawn_pos;
	HP = ENEMY_MAX_HP;
	damage = false;
	alive = true;
}