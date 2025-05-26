#pragma once
#include "../Common.h"
#include "enemy.h"


//�G�֌W
constexpr float	ENEMY_03_POINT = 40.0f;							//�G�R�̃|�C���g
constexpr float ENEMY_03_ATTACK_SIZE = 30.0f;					//�G3�U���̃T�C�Y
constexpr float ENEMY_03_MOVE_SPEED = 0.8f;						//�G3�ړ����x
constexpr float ENEMY_03_ATTACK_DAMAGE_START_TIME = 25.0f;		//�G3�̍U���_���[�W�����A�j������
constexpr float ENEMY_03_ATTACK_DAMAGE_FIN_TIME = 40.0f;		//�G3�̍U���_���[�W�I���A�j������


//�G02�N���X
class Enemy03 :public Enemy {
private:


public:

	Enemy03();
	~Enemy03(){};

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��	
	void Delete();

private:

	//�ړ�����
	void Move();

	//�U������
	void Attack();

	//�A�j���[�V����
	void Animation();

public:

	//�U���̍Œ���
	bool GetAttack();

	//�X�|�[������
	void spawn(VECTOR spawn_pos);
};