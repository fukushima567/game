#include "enemy04.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//�R���X�g���N�^
Enemy04::Enemy04() {

}


//������
void Enemy04::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/enemy4.mv1");
	size = ENEMY_SIZE;
	attackPower = ENEMY_ATTACK_POWER;
	point = ENEMY_04_POINT;

	//�A�j���[�V�����֌W������
	InitAnim(ENEMY_ANIMATION_NUM);
}


//�ʏ폈��
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


//�`��
void Enemy04::Draw() {
	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);
	MV1DrawModel(modelHandle);
}


//�j��	
void Enemy04::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
}


//�ړ�����
void Enemy04::Move() {

	speed = 0;

	if (!attack) {
		
		//�͈͊O�ɏo��Ɩ߂�t���O���I��
		if (!Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
			returnFlag = true;
		}
		if (!returnFlag) {//�v���C���[�ʒu�ֈړ�
			if (Collision::Circle(playerPos.x, playerPos.z, 1, pos.x, pos.z, ENEMY_MOVE_RANGE)) {
				FollowMove(ENEMY_04_MOVE_SPEED);
			}
			else {//���R�Ȉړ�
				PatrolMove(ENEMY_04_MOVE_SPEED);
			}
		}
		else {//�߂�t���O���I���Ȃ猳�̈ʒu��
			ReturnMove(ENEMY_04_MOVE_SPEED);
			if (Collision::Circle(spawnPos.x, spawnPos.z, 1, pos.x, pos.z, 1)) {
				returnFlag = false;
			}
		}
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//�U������
void Enemy04::Attack() {

	if (!attack) {
		//�v���C���[�̖ڂ̑O�ōU��
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


//�A�j���[�V����
void Enemy04::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (damage) {//��_���[�W
			if (curAnim != ENEMY_DAMAGE) {
				ChangeAnim(ENEMY_DAMAGE);
			}
		}
		else if (attack) {//�U��
			if (curAnim != ENEMY_ATTACK) {
				ChangeAnim(ENEMY_ATTACK);
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


//�X�|�[������
void Enemy04::spawn(VECTOR spawn_pos) {
	pos = spawn_pos;
	spawnPos = spawn_pos;
	HP = ENEMY_MAX_HP*2;
	damage = false;
	alive = true;
}