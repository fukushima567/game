#pragma once
#include "../Common.h"
#include "enemy.h"


//�{�X�̊�{
constexpr VECTOR BOSS_FIRST_POS = { 0.0f,0.0f,800.0f };		//�{�X�̏������W
constexpr int	BOSS_MAX_HP = 15;							//�{�X�̗̑�
constexpr int	BOSS_MAX_DAMAGE_COUNT = 40;					//�{�X�̃_���[�W�d������
constexpr float BOSS_SIZE = 35.0f;							//�{�X�̃T�C�Y
constexpr float BOSS_MOVE_SPEED = 1.0f;						//�{�X�̈ړ����x


//�ߋ����U���֌W
constexpr int	BOSS_ATTACK_POWER_NORMAL = 20;				//�{�X�̋ߐڍU����
constexpr float BOSS_ATTACK_RANGE = 70.0f;					//�ߐڍU�����J�n�����͈�
constexpr float BOSS_ATTACK_SIZE = 60.0f;					//�ߐڍU���̃T�C�Y
constexpr float BOSS_ATTACK_RADIUS = -10.0f;				//�ߐڍU���ƃ{�X�̋���
constexpr float BOSS_ATTACK_1_DAMAGE_TIME = 140.0f;			//�ߋ����U��1�̃_���[�W�����A�j������
constexpr float BOSS_ATTACK_2_DAMAGE_START_TIME = 155.0f;	//�ߋ����U��2�̃_���[�W�����A�j������
constexpr float BOSS_ATTACK_2_DAMAGE_FIN_TIME = 218.0f;		//�ߋ����U��2�̃_���[�W�I���A�j������
constexpr float BOSS_ATTACK_2_DAMAGE_LAST_TIME = 250.0f;	//�ߋ����U��2�̍ŏI�_���[�W�����A�j������


//�e�֌W
constexpr int	BOSS_ATTACK_POWER_BULLET = 10;				//�{�X�̒e�U����
constexpr int	BOSS_SPAWN_BULLET_TIME = 240;				//�{�X�̒e���o������܂ł̎���
constexpr float BOSS_BULLET_SIZE = 50.0f;					//�{�X�e�̃T�C�Y
constexpr float BOSS_BULLET_MOVE_SPEED = 20.0f;				//�{�X�e�ړ����x
constexpr float BOSS_BULLET_SPAWN_Y_POS = 250.0f;			//�{�X�̒e�o��Y���W
constexpr float BOSS_AOE_DRAW_TIME = 50.0f;					//AOE���\�������A�j������
constexpr float BOSS_BULLET_START_MOVE_TIME = 180.0f;		//�{�X�̒e�ړ��J�n�A�j������
constexpr float BOSS_BULLET_DELETE_TIME = 80.0f;			//�{�X�e�̏��ŃA�j������
constexpr float BOSS_BULLET_SUB_ALPHA = 0.01f;				//�{�X�̒e�A���t�@�l������



//�U���̎��
enum BOSS_ATTACK_TYPE {
	BOSS_ATTACK_NONE,			//�U�����Ă��Ȃ�
	BOSS_ATTACK_NORMAL_1,		//�ߋ����U��1
	BOSS_ATTACK_NORMAL_2,		//�ߋ����U��2
	BOSS_ATTACK_BULLET,			//�������U��
	BOSS_ATTACK_NUM				//�U����ޑ���
};


//�{�X�̃A�j���[�V�����̎��
enum BOSS_ANIMATION {
	BOSS_IDLE,			//�ҋ@
	BOSS_WALK,			//�ړ�
	BOSS_ATTACK_1,		//�U��1
	BOSS_ATTACK_2,		//�U��2
	BOSS_ATTACK_3,		//�U��3
	BOSS_DOWN,			//��_���[�W

	BOSS_ANIMATION_NUM	//�A�j���[�V��������
};


//�{�X�N���X
class EnemyBoss :public Enemy {
private:

	int AoE;				//�U���͈͉̔摜
	int attackType;			//�U���̎��
	float bulletAlpha;		//�e�̓����x

	bool down;				//�_�E�����Ă��邩

	//�֐�
public:

	EnemyBoss();
	~EnemyBoss(){};

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

	//�e�̏���
	void Bullet();

	//�A�j���[�V����
	void Animation();

public:
	
	//�U���̍Œ���
	bool GetAttack();

	//�X�|�[������
	void spawn(VECTOR spawn_pos) { 
		pos = spawn_pos;
		HP = 2;
		damage = false;
		alive = true;
	}
};