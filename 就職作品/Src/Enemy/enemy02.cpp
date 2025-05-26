#include "enemy02.h"
#include "../Collision/Collision.h"
#include "../MyLib/MyLib.h"


//�R���X�g���N�^
Enemy02::Enemy02() {

	bulletRadian = 0.0f;
}


//������
void Enemy02::Init() {

	modelHandle = MV1LoadModel("data/Image/Play/Enemy/enemy2.mv1");
	bulletHandle= MV1LoadModel("data/Image/Play/Enemy/enemy2Bullet.mv1");

	
	bulletSize = ENEMY_02_BULLET_SIZE;
	bulletUse = true;

	attackPower = ENEMY_ATTACK_POWER;
	size = ENEMY_SIZE;
	point = ENEMY_02_POINT;
	

	//�A�j���[�V�����֌W������
	InitAnim(ENEMY_ANIMATION_NUM);
}


//�ʏ폈��
void Enemy02::Step() {

	if (playerPos.y != -1 && HP > 0) {
		UpdateDamage(ENEMY_MAX_DAMAGE_COUNT);
		Attack();
	}

	Bullet();
	
	knockBack();

	TickEnemy();

	Animation();
}


//�`��
void Enemy02::Draw() {
	MV1SetRotationXYZ(modelHandle, rot);
	MV1SetPosition(modelHandle, pos);
	MV1DrawModel(modelHandle);

	for (int index = 0;index < ENEMY_02_MAX_BULLET;index++) {
		if (!bulletActive[index]) { continue; }
		MV1SetRotationXYZ(bulletHandle, {0,bulletRadian,0});
		MV1SetPosition(bulletHandle, bulletPos[index]);
		MV1DrawModel(bulletHandle);
	}
}


//�j��	
void Enemy02::Delete() {
	DeleteAnim();
	MV1DeleteModel(bulletHandle);
	MV1DeleteModel(modelHandle);
}


//�U������
void Enemy02::Attack() {

	playerRadian = 0.0f;

	if (!attack) {

		//���b�N�I�������ƍU��
		if (curAnim != ENEMY_ATTACK) {
			if (lock2) {
				attack = true;
				bulletInterval = 0;
				playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
				rot.y = playerRadian + MyLib::GetRadian(180);
				bulletRadian = -1.0f;
			}
		}
	}
}


//�e�̏���
void Enemy02::Bullet() {

	//���˃^�C�~���O�Ŏ��s
	if (curAnim == ENEMY_ATTACK && animCount > ENEMY_02_BULLET_START_TIME) {

		//�e�̕���������
		if (bulletRadian == -1) {
			playerRadian = MyLib::GetPosRadian(pos.z, pos.x, playerPos.z, playerPos.x);
			rot.y = playerRadian + MyLib::GetRadian(180);
		}

		//�C���^�[�o���I���Œe�𔭎�
		bulletInterval++;
		if (bulletInterval > ENEMY_02_BULLET_INTERVAL) {
			bulletInterval = 0;
			for (int index = 0;index < ENEMY_02_MAX_BULLET;index++) {
				if (bulletActive[index]) { continue; }
				bulletPos[index] = pos;
				bulletPos[index].y = ENEMY_02_BULLET_Y_POS;
				bulletActive[index] = true;
				bulletRadian = rot.y + MyLib::GetRadian(180);
				break;
			}
		}
	}

	//�e�̈ړ�
	for (int index = 0;index < ENEMY_02_MAX_BULLET;index++) {
		if (!bulletActive[index]) { continue; }

		bulletPos[index] = MyLib::Get3DCircle(bulletPos[index], 0.0f, bulletRadian, ENEMY_02_BULLET_MOVE_SPEED);

		//�w��̎��ԂɂȂ�ƑO�̒e������
		if (curAnim == ENEMY_ATTACK && animCount > ENEMY_02_BULLET_FIN_TIME && animCount < ENEMY_02_BULLET_START_TIME) {
			bulletActive[index] = false;
		}
	}


	//HP���Ȃ��Ȃ�ƒe������
	if (HP <= 0) {
		for (int index = 0;index < ENEMY_02_MAX_BULLET;index++) {
			if (!bulletActive[index]) { continue; }

			bulletActive[index] = false;
		}
	}
}


//�A�j���[�V����
void Enemy02::Animation() {

	if (animBlend[curAnim] >= 1.0f) {

		if (damage) {//��_���[�W
			if (curAnim != ENEMY_DAMAGE) {
				ChangeAnim(ENEMY_DAMAGE);
			}
		}
		else if (attack) {//�U��
			if (curAnim != ENEMY_ATTACK) {
				ChangeAnim(ENEMY_ATTACK);
				if (GetRand(1)==0) {
					animCount = 25;
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
bool Enemy02::GetAttack() {

	return false;
}


//�X�|�[������
void Enemy02::spawn(VECTOR spawn_pos) {
	pos = spawn_pos;
	spawnPos = spawn_pos;
	HP = ENEMY_MAX_HP;
	damage = false;
	alive = true;
}