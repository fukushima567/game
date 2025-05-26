#pragma once
#include "../Character/character.h"


//��{
constexpr VECTOR FIRST_POS = { 0.0f,10.0f,0.0f };		//�v���C���[�������W
constexpr int	PLAYER_SPHERE = 5;						//�v���C���[�����蔻��T�C�Y
constexpr int	MAX_HP = 100;							//�v���C���[�ő�HP
constexpr int	SUB_HP = 20;							//��������HP������
constexpr int	MAX_STAMINA_GAUGE = 6000;				//�X�^�~�i�ő�l
constexpr int	STAMINA_ADD_NUM = 30;					//�X�^�~�i������
constexpr int	STAMINA_SUB_NUM = 15;					//�X�^�~�i������
constexpr int	DAMAGE_INTERVAL = 36;					//�_���[�W���󂯂�܂ł̃C���^�[�o��
constexpr int	AVOID_INVINCIBLE = 30;					//������̖��G����
constexpr int	COMBO_TIME = 320;						//�R���{��������
constexpr float MAX_AVOID_COUNT = 10.0f;				//����̃J�E���g
constexpr float SUB_AVOID_COUNT = 0.45f;				//����J�E���g�̌�����
constexpr float PLAYER_MIN_Y = -150.0f;					//�v���C���[�̓�����Œ�Y���W


//�ړ��֌W
constexpr float WALK_SPEED = 1.5f;						//�������x
constexpr float DASH_SPEED = 2.5f;						//�����b���x
constexpr float ADD_DASH_SPEED = 0.2f;					//���葬�x������
constexpr float SUB_DASH_SPEED = 80.0f;					//���葬�x������
constexpr float MAX_DASH_SPEED_NUM = 3.0f;				//���茻�݂̍ő呬�x����p
constexpr float SP_DASH_ATTACK_SPEED = 7.7f;			//������ԍU�����̑��x
constexpr float MAX_SPEED = 7.5f;						//�v���C���[���x���
constexpr float WALK_ANIM_COUNT_1 = 4.0f;				//1���ڕ����T�E���h�Đ��J�n�J�E���g
constexpr float WALK_ANIM_COUNT_2 = 14.0f;				//2���ڕ����T�E���h�Đ��J�n�J�E���g
constexpr float DASH_ANIM_COUNT_1 = 3.0f;				//1���ڑ���T�E���h�Đ��J�n�J�E���g
constexpr float DASH_ANIM_COUNT_2 = 9.0f;				//2���ڑ���T�E���h�Đ��J�n�J�E���g


//�U���֌W
constexpr int	NOMAL_ATTACK_POWER = 1;					//�ʏ�U���̍U����
constexpr int	NOMAL_DASH_ATTACK_POWER = 2;			//�_�b�V���U����b�U����
constexpr int	HIT_STOP_NORMAL = 1;					//�ʏ�U���̃q�b�g�X�g�b�v
constexpr int	HIT_STOP_DASH = 20;						//�_�b�V���U���̃q�b�g�X�g�b�v
constexpr int	HIT_STOP_CLEAR = 50;					//�N���A���̃q�b�g�X�g�b�v
constexpr float ATTACK_SIZE_1 = 10.0f;					//�U���̃T�C�Y
constexpr float ATTACK_RANGE = 10.0f;					//�v���C���[�ƍU���̋���
constexpr float ATTACK_DASH_MIN = 2.0f;					//�_�b�V���U�������J�E���g
constexpr float ATTACK_DASH_MAX = 6.0f;					//�_�b�V���U���I���J�E���g
constexpr float ATTACK_MISS_TIME = 15.0f;				//�_�b�V���U���~�X�̃m�b�N�o�b�N����
constexpr float ATTACK_MISS_NUM = -1.0f;				//�_�b�V���U���~�X�̃m�b�N�o�b�N��
constexpr float ATTACK_NORMAL_MIN = 3.0f;				//�ʏ�U�������J�E���g


//�K�E�Z�֌W
constexpr int MAX_SP_GAUGE = 400;						//�K�E�Z�̎���
constexpr int DASH_ATTACK_COUNT_SP_1 = 10;				//�K�E�Z1�ɕK�v�ȃ_�b�V���U����
constexpr int DASH_ATTACK_COUNT_SP_2 = 20;				//�K�E�Z2�ɕK�v�ȃ_�b�V���U����
constexpr int DASH_ATTACK_COUNT_SP_3 = 30;				//�K�E�Z3�ɕK�v�ȃ_�b�V���U����
constexpr int HIT_STOP_SPECIAL = 1;						//�K�E�Z�̃q�b�g�X�g�b�v


//�}�e���A���֌W
constexpr COLOR_F COLOR_NONE = { 0.0f,0.0f,0.0f,0.0f };	//�����Ȃ�
constexpr COLOR_F COLOR_RED = { 0.7f,0.0f,0.0f,1.0f };	//�K�E�Z�̔����F
constexpr int	PLAYER_MATERIAL_NUM = 4;				//�v���C���[�̃}�e���A����
constexpr int	SWORD_MATERIAL_NUM = 3;					//����̃}�e���A����
constexpr float	MAX_SWORD_COLOR = 10.0f;				//����̍ő唭��



//����̃^�C�v
enum AVOID_TYPE {
	AVOID_NONE,		//������Ă��Ȃ�
	AVOID_LEFT,		//�����
	AVOID_RIGHT,	//�E���
	AVOID_BACK		//�����
};


//�U���̎��
enum PLAYER_ATTACK_TYPE {
	PLAYER_ATTACK_NONE,		//�U�����Ă��Ȃ�
	PLAYER_ATTACK_NORMAL,	//�ʏ�U��
	PLAYER_ATTACK_DASH,		//�_�b�V���U��
	PLAYER_ATTACK_SPECIAL	//�K�E�Z�U��
};


//�K�E�Z�̏��
enum SPECIAL_STATE {
	SPECIAL_NONE,	//�K�E�Z������
	SPECIAL_READY,	//�K�E�Z�\������
	SPECIAL_ACTIVE,	//�K�E�Z����
	SPECIAL_FINISH	//�K�E�Z�I��
};


//�A�j���[�V�����̎��
enum PLAYER_ANIMATION {
	PLAYER_IDLE,			//�ҋ@
	PLAYER_WALK,			//�ʏ�ړ�
	PLAYER_DASH,			//�_�b�V��
	PLAYER_LEFT_STEP,		//�����
	PLAYER_RIGHT_STEP,		//�E���
	PLAYER_BACK_STEP,		//�����
	PLAYER_NOMAL_ATTACK,	//�ʏ�U��
	PLAYER_DASH_ATTACK,		//�_�b�V���U��
	PLAYER_DASH_AFTER,		//�_�b�V���U����
	PLAYER_DASH_ATTACK_2,	//������Ԏ��̃_�b�V���U��
	PLAYER_SPECIAL,			//������Ԉڍs
	PLAYER_AIR,				//��
	PLAYER_MISS,			//�U�����s�̂�����
	PLAYER_DAMAGE,			//��_���[�W
	PLAYER_DATH,			//����
	PLAYER_CLEAR,			//�N���A

	PLAYER_ANIMATION_NUM	//�A�j���[�V��������
};


//�G�t�F�N�g�̎��
enum PLAYER_EFFECT {
	PLAYER_EFFECT_ATTACK,	//�_�b�V���U��
	PLAYER_EFFECT_SP,		//�K�E�Z������
	PLAYER_EFFECT_SP_ATTACK,//�K�E�Z������

	PLAYER_EFFECT_NUM		//�v���C���[�G�t�F�N�g����
};


//�v���C���[�N���X
class Player :public Character{
private:

	int toolHandle;			//���탂�f���n���h��
	int frameIndex;			//����̃t���[���Y����

	VECTOR rot;				//�v���C���[��]
	VECTOR cameraRot;		//�J�����̉�]
	MATRIX toolPos;			//����̍��W
	
	bool ground;			//�n�ʐڒn�t���O
	bool lockOn;			//���b�N�I���t���O

	int dashAttackCount;	//�_�b�V���U���q�b�g��
	int invincibleCount;	//���G���Ԃ̃J�E���g

	float combo;			//�R���{��
	int	  comboCount;		//�R���{����
	float nearEneRad;		//�߂��ɂ���G�Ƃ̊p�x

	//�_�b�V���֌W
	bool drawDash;			//�_�b�V���G�t�F�N�g�\���t���O
	bool finishDash;		//�_�b�V���I���t���O
	int	staminaGauge;		//�X�^�~�i
	int avoidType;			//����̎��
	float avoidCount;		//����̎���
	float currentMaxSpeed;	//���݂̉����\�ȍő呬�x
	float dashSub;			//�_�b�V�����x������

	//�U���֌W
	bool attackFlag;		//�U���t���O
	bool attackHit;			//�U�������t���O
	bool attackMiss;		//�U�����s�t���O
	int attackType;			//�U���̎��
	
	//�K�E�Z�֌W
	int specialState;		//�K�E�Z�̏��
	int specialGauge;		//�K�E�Z�̃Q�[�W

	//�q�b�g�X�g�b�v�֌W
	bool hitStop;			//�q�b�g�X�g�b�v�̃t���O
	int hitStopNum;			//�q�b�g�X�g�b�v����
	int hitStopCount;		//�q�b�g�X�g�b�v���Ԃ̃J�E���g

	//��_���[�W�֌W
	bool damageFlag;		//��_���[�W�t���O
	int	damageNum;			//��_���[�W��
	float damageRot;		//�_���[�W���󂯂��p�x

	//�G�t�F�N�g�֌W
	bool effectRequest;						//�G�t�F�N�g���N�G�X�g�t���O
	int	 effectHandle[PLAYER_EFFECT_NUM];	//�G�t�F�N�g�n���h��
	int  effectIndex[PLAYER_EFFECT_NUM];	//�G�t�F�N�g�i���o�[

	//�֐�
public:

	Player();
	~Player(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��	
	void Delete();

private:

	//��������
	void Walk();

	//���菈��
	void Dash();

	//�������
	void Avoid();

	//�K�E�Z����
	void Special();

	//�m�b�N�o�b�N����
	void KnockBack();

	//�U������
	void Attack();

	//�A�j���[�V����
	void Animation();

	//�G�t�F�N�g����
	void Effect();

public:

	//�N���A���̏���
	void clear();

	//�_���[�W���󂯂鏈��
	void Damage(VECTOR enemy_pos, int damage);

	//�R���{����
	void Combo();

	//�_�b�V���U�����s����
	void AttackMiss();

	//���ɂ����ۂ̏���
	void Ground();

	//�擾�֌W
	//�U���t���O�𓾂�
	bool GetAttackFlag() { return attackFlag; }

	//�G�ɍU�������������u�Ԃ�
	bool GetAttackHit() { return attackHit; }

	//���b�N�I������
	bool GetLockOn() { return lockOn; }

	//�q�b�g�X�g�b�v����
	bool GetHitStop() { return hitStop; }

	//�_�b�V���G�t�F�N�g��`�悷�邩
	bool GetDrawScreenEffect() { return drawDash; }

	//�_���[�W���󂯂��u�Ԃ�
	bool GetDamage();

	//�_�b�V����Ԃ�
	bool GetIsDash();

	//�X�^�~�i�𓾂�
	int GetStaminaGauge() { return staminaGauge; }

	//�K�E�Z�̏�Ԃ𓾂�
	int GetSpecialState() { return specialState; }

	//������Ԃ̎��Ԃ𓾂�
	int GetSpecialGauge() { return specialGauge; }

	//�_�b�V���U���𓖂Ă��񐔂𓾂�
	int GetDashAttackCount() { return dashAttackCount; }

	//�R���{���𓾂�
	float GetCombo() { return combo; }

	//�R���{���Ԃ𓾂�
	int GetComboCount() { return comboCount; }

	//��_���[�W�ʂ𓾂�
	int GetDamageNum() { return damageNum; }

	//���݂̈ړ����x�𓾂�
	float GetSpeed() { return speed; }

	//��]�l�𓾂�
	float GetRot() { return rot.y; }

	//��ԋ߂��G�̊p�x�𓾂�
	float GetEneRad();

	//�Z�b�g�֌W
	//�J�����̌����Ă���������Z�b�g
	void SetCameraRad(VECTOR camera_rot) { cameraRot = camera_rot; }

	//��ԋ߂��G�Ƃ̊p�x���Z�b�g
	void SetNearEneRad(float ene_rad);

	//�q�b�g�X�g�b�v���I���ɂ���
	void SetHitStop(bool max = false);
};