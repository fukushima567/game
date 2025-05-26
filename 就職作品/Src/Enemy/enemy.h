#pragma once
#include "../Character/character.h"


//�G
constexpr int	ENEMY_MAX_HP = 2;					//�G�̍ő�HP
constexpr int	ENEMY_MAX_MOVE_INTERVAL = 180;		//�G�̈ړ��Ԋu
constexpr float ENEMY_SIZE = 8.0f;					//�G�T�C�Y
constexpr float ENEMY_KILL_Y = -200.0f;				//�G�ŏ�Y���W

//�m�b�N�o�b�N�֌W
constexpr float ENEMY_KNOCK_BACK_RAD = 0.7f;		//�m�b�N�o�b�N�p�x
constexpr float ENEMY_KNOCK_BACK_MAX_NUM = 15.0f;	//�m�b�N�o�b�N�ő�l
constexpr float ENEMY_KNOCK_BACK_SUB_NUM = 0.5f;	//�m�b�N�o�b�N�l������


//�e�֌W
constexpr int	ENEMY_MAX_BULLET = 12;				//�e�ő吔
constexpr int	ENEMY_ATTACK_POWER = 5;				//�G�U����
constexpr int	ENEMY_MAX_DAMAGE_COUNT = 60;		//�G�̃_���[�W�d������
constexpr float ENEMY_MOVE_RANGE = 150.0f;			//�G�̈ړ��ł��鋗��



//�G�̃A�j���[�V�����̎��
enum ENEMY_ANIMATION {
	ENEMY_IDLE,			//�ҋ@
	ENEMY_WALK,			//�ړ�
	ENEMY_ATTACK,		//�U��
	ENEMY_DAMAGE,		//��_���[�W

	ENEMY_ANIMATION_NUM	//�A�j���[�V��������
};


//�G���N���X
class Enemy :public Character {
protected:

	VECTOR playerPos;						//�v���C���[���W
	VECTOR spawnPos;						//�X�|�[�����W
	VECTOR rot;								//��]

	//�ړ��֌W
	bool moveFlag;							//�ړ�����
	int moveInterval;						//�ړ��̃C���^�[�o��
	int moveIntervalCount;					//�ړ��̃C���^�[�o���J�E���g

	//�v���C���[�֌W
	float playerRadian;						//�v���C���[�̊p�x
	bool  hitStop;							//�v���C���[�̃q�b�g�X�g�b�v
	bool lock;								//�ʏ펞���b�N�I���t���O
	bool lock2;								//�_�b�V�������b�N�I���t���O

	bool returnFlag;						//�����ʒu�֖߂�t���O
	bool ground;							//�n�ʂɂ��邩
	bool attack;							//�U������
	bool alive;								//�����t���O
	float  point;							//�|�C���g

	//�e�֌W
	int bulletHandle;						//�e���f���̃n���h��
	VECTOR bulletPos[ENEMY_MAX_BULLET];		//�e�̍��W
	float bulletSize;						//�e�̃T�C�Y
	bool bulletUse;							//�e���g�p���邩
	bool bulletActive[ENEMY_MAX_BULLET];	//�e���o�Ă��邩
	int bulletInterval;						//�e�̃C���^�[�o��

	//�_���[�W�֌W
	bool  damage;							//�_���[�W���󂯂Ă��邩
	int	  damageCount;						//�_���[�W�̃C���^�[�o��
	int	  damageNum;						//�_���[�W��
	
	//�m�b�N�o�b�N�֌W
	bool knockBackFlag;						//�m�b�N�o�b�N�t���O
	float knockBackNum;						//�m�b�N�o�b�N��
	float knockBackRad;						//�m�b�N�o�b�N�̕���

public:

	Enemy();
	~Enemy(){};

	//������
	virtual void Init() = 0;

	//�ʏ폈��
	virtual void Step() = 0;

	//�`��
	virtual void Draw() = 0;

	//�j��
	virtual void Delete() = 0;

	//�X�|�[������
	virtual void spawn(VECTOR spawn_pos) = 0;

	//�_���[�W���󂯂�
	void Damage(int damage_num);

protected:

	//�_���[�W���X�V
	void UpdateDamage(int max_count);

	//�m�b�N�o�b�N����
	void knockBack();

	//���t���[���s���G���ʂ̏���
	void TickEnemy();

	//�G�̏���ړ�����
	void PatrolMove(float patroll_speed);

	//�G�̏����ʒu�ւ̈ړ�����
	void ReturnMove(float return_speed);

	//�G�̃v���C���[�Ǐ]
	void FollowMove(float follow_speed);

public:

	//�擾�֌W
	//�U���̍Œ���
	virtual bool GetAttack() = 0;

	//�_���[�W���󂯂��u�Ԃ𓾂�
	bool GetDamageHit();

	//�_���[�W���󂯂��u�Ԃ𓾂�(�{�X)
	bool GetDamageHit2();

	//�_���[�W���󂯂����𓾂�
	bool GetDamage() { return damage; }

	//�����󋵂𓾂�
	bool GetAlive() { return alive; }

	//���b�N�I������Ă��邩
	bool GetLock() { return lock; }

	//�_�b�V�����Ƀ��b�N�I������Ă��邩
	bool GetLock2() { return lock2; }

	//�e���g�p���邩����
	bool GetBulletUse() { return bulletUse; }

	//�e�̎g�p��Ԃ𓾂�
	bool GetBulletActive(int index) { return bulletActive[index]; }

	//�e�̍��W�𓾂�
	VECTOR GetBulletPos(int index) { return bulletPos[index]; }

	//�e�̃T�C�Y�𓾂�
	float GetBulletSize() { return bulletSize; }

	//��_���[�W�ʂ𓾂�
	int GetDamageNum() { return damageNum; }
	
	//�|�C���g�ʂ𓾂�
	float GetPoint() { return point; }

	//�Z�b�g�֌W
	//������Ԃ��Z�b�g
	void SetAlive(bool state = false) { alive = state; }

	//���ɂ����ۂ̏���
	void Ground() { ground = true; }

	//�ʏ펞���b�N�I����Ԃ��Z�b�g
	void SetLock(bool is_lock) { lock = is_lock; }

	//�_�b�V�������b�N�I����Ԃ��Z�b�g
	void SetLock2(bool is_lock) { lock2 = is_lock; }

	//�v���C���[���W���Z�b�g
	void SetPlayerPos(VECTOR player_pos) { playerPos = player_pos; }

	//�m�b�N�o�b�N�̕������Z�b�g
	void SetKnockBackRad(float rad) { knockBackRad = rad; }

	//�v���C���[�̃q�b�g�X�g�b�v���Z�b�g
	void SetHitStop(bool flag) { hitStop = flag; }
};