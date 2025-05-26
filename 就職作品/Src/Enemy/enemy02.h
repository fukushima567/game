#pragma once
#include "../Common.h"
#include "enemy.h"


//�G�֌W
constexpr float	ENEMY_02_POINT = 30.0f;					//�G2�̃|�C���g

//�e�֌W
constexpr int	ENEMY_02_MAX_BULLET = 3;				//�G2�̒e�ő吔
constexpr int	ENEMY_02_BULLET_INTERVAL = 10;			//�G2�̒e�C���^�[�o��
constexpr float ENEMY_02_BULLET_SIZE = 20.0f;			//�G2�e�̃T�C�Y
constexpr float ENEMY_02_BULLET_MOVE_SPEED = 5.0f;		//�G2�e�ړ����x
constexpr float ENEMY_02_BULLET_Y_POS = 16.0f;			//�G2�eY���W
constexpr float ENEMY_02_BULLET_START_TIME = 40.0f;		//�G2�e���˃A�j������
constexpr float ENEMY_02_BULLET_FIN_TIME = 30.0f;		//�G2�e���ŃA�j������(1�O�̍U��)



//�G02�N���X
class Enemy02 :public Enemy {
private:

	float bulletRadian;

	
public:

	Enemy02();
	~Enemy02(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��	
	void Delete();

private:

	//�U������
	void Attack();

	//�e�̏���
	void Bullet();

	//�A�j���[�V����
	void Animation();

public:

	//�U���̍Œ���
	bool GetAttack();

	//�X�|�[������
	void spawn(VECTOR spawn_pos);
};