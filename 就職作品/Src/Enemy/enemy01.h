#pragma once
#include "../Common.h"
#include "enemy.h"


constexpr float ENEMY_01_MOVE_SPEED = 0.5f;						//�G1�ړ����x
constexpr float ENEMY_01_ATTACK_SIZE = 20.0f;					//�G1�U���̃T�C�Y
constexpr float ENEMY_01_ATTACK_DAMAGE_TIME = 38.0f;			//�G1�U���̃_���[�W�����A�j������
constexpr float ENEMY_01_ATTACK_RADIUS = -10.0f;				//�U���ʒu�ƓG1�ʒu�̋���
constexpr float	ENEMY_01_POINT = 10.0f;							//�G�P�̃|�C���g

//�G01�N���X
class Enemy01 :public Enemy {
private:


public:

	Enemy01();
	~Enemy01(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��	
	void Delete();
	
private:

	//�ړ�
	void Move();

	//�U��
	void Attack();

	//�A�j���[�V����
	void Animation();

public:

	//�U���̍Œ���
	bool GetAttack();

	//�X�|�[������
	void spawn(VECTOR spawn_pos);
};