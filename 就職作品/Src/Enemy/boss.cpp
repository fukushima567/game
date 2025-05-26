#include "boss.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//�R���X�g���N�^
EnemyBoss::EnemyBoss() {

	AoE = 0;
	attackType = 0;
	bulletAlpha = 0.0f;
	down = false;
}


//������
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

	//�A�j���[�V�����֌W������
	InitAnim(BOSS_ANIMATION_NUM);
}


//�ʏ폈��
void EnemyBoss::Step() {

	if (HP <= 0) { 
		down = true;
		HP = BOSS_MAX_HP;
	}

	//�����Ă�������s
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


//�`��
void EnemyBoss::Draw() {

	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);

	MV1DrawModel(modelHandle);

	//�������U���������A�e��`��
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


//�j��	
void EnemyBoss::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(bulletHandle);
	DeleteGraph(AoE);
}


//�{�X�̈ړ�
void EnemyBoss::Move() {

	playerRadian = 0.0f;
	speed = 0.0f;


	//�U�����łȂ���Ύ��s
	if (attackType == BOSS_ATTACK_NONE) {

		//�ړ�
		playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
		speed = BOSS_MOVE_SPEED;
		rot.y = playerRadian + MyLib::GetRadian(180);
	}
	
	pos.z = MyLib::GetCircleX(pos.z, speed, playerRadian);
	pos.x = MyLib::GetCircleY(pos.x, speed, playerRadian);
}


//�U��
void EnemyBoss::Attack() {
	
	//�U�����łȂ���Ύ��s
	if (attackType == BOSS_ATTACK_NONE) {

		//�ߋ����U��
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

		}//�������U��
		else if (bulletInterval > BOSS_SPAWN_BULLET_TIME) {
			attackType = BOSS_ATTACK_BULLET;
			bulletInterval = 0;
			bulletAlpha = 1.0f;
			attackPower = BOSS_ATTACK_POWER_BULLET;
			
			//�e�̏o��
			for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
				bulletPos[index].x = (float)GetRand(600) - 200;
				bulletPos[index].y = BOSS_BULLET_SPAWN_Y_POS;
				bulletPos[index].z = (float)GetRand(1000) - 100;
				bulletActive[index] = true;
			}
		}
	}
}


//�e�̏���
void EnemyBoss::Bullet() {

	//�C���^�[�o�������Z
	bulletInterval++;

	//�e�̈ړ�
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
	
	//�e���ŏ���
	if (animCount > BOSS_BULLET_DELETE_TIME) {
		for (int index = 0;index < ENEMY_MAX_BULLET;index++) {
			bulletActive[index] = false;
		}
	}
}


//�A�j���[�V����
void EnemyBoss::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (down) {//�_�E��
			if (curAnim != BOSS_DOWN) {
				ChangeAnim(BOSS_DOWN);
			}
		}
		else if (attackType == 1) {//�U��1
			if (curAnim != BOSS_ATTACK_1) {
				ChangeAnim(BOSS_ATTACK_1);
			}
		}
		else if (attackType == 2) {//�U���Q
			if (curAnim != BOSS_ATTACK_2) {
				ChangeAnim(BOSS_ATTACK_2);
			}
		}
		else if (attackType == 3) {//�U��3
			if (curAnim != BOSS_ATTACK_3) {
				ChangeAnim(BOSS_ATTACK_3);
			}
		}
		else if (speed != 0) {//����
			if (curAnim != BOSS_WALK) {
				ChangeAnim(BOSS_WALK);
			}
		}
		else {//�ҋ@
			if (curAnim != BOSS_IDLE) {
				ChangeAnim(BOSS_IDLE);
			}
		}
	}

	//�A�j���[�V�����X�V
	UpdateAnim();

	//�A�j���[�V�������Đ����I������ŏ��ɖ߂�
	if (animCount >= animAllTime) {
		if (curAnim == BOSS_ATTACK_1|| curAnim == BOSS_ATTACK_2 || curAnim == BOSS_ATTACK_3) { attackType = 0; }
		down = false;
		animCount = 0;
	}
}


//�U���̍Œ���
bool EnemyBoss::GetAttack() {

	if (animCount == BOSS_ATTACK_1_DAMAGE_TIME && curAnim == BOSS_ATTACK_1||
		curAnim == BOSS_ATTACK_2 && animCount > BOSS_ATTACK_2_DAMAGE_START_TIME && animCount < BOSS_ATTACK_2_DAMAGE_FIN_TIME ||
		curAnim == BOSS_ATTACK_2 && animCount == BOSS_ATTACK_2_DAMAGE_LAST_TIME) {
		return true;
	}
	return false;
}