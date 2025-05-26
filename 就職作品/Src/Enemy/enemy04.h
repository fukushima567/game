#pragma once
#include "../Common.h"
#include "enemy.h"


constexpr float	ENEMY_04_POINT = 60.0f;							//�G4�̃|�C���g
constexpr float ENEMY_04_MOVE_SPEED = 0.5f;
constexpr float ENEMY_04_ATTACK_RADIUS = -10.0f;				//�U���ʒu�ƓG4�ʒu�̋���
constexpr float ENEMY_04_ATTACK_SIZE = 12.0f;					//�G4�U���̃T�C�Y
constexpr float ENEMY_04_ATTACK_DAMAGE_START_TIME = 18.0f;		//�G4�̍U���_���[�W�����A�j������
constexpr float ENEMY_04_ATTACK_DAMAGE_FIN_TIME = 105.0f;		//�G4�̍U���_���[�W�I���A�j������



//�G04�N���X
class Enemy04 :public Enemy {
private:


public:

	Enemy04();
	~Enemy04() {};

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

public:

	//�A�j���[�V����
	void Animation();

	//�U���̍Œ���
	bool GetAttack();

	//�X�|�[������
	void spawn(VECTOR spawn_pos);
};