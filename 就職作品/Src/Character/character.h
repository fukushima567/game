#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


constexpr float ANIM_BLEND_NUM = 0.2f;	//�A�j���[�V�����u�����h�ω���
constexpr float ANIM_MAX_BLRND = 1.0f;	//�A�j���[�V�����u�����h�̍ő�l
constexpr float ANIM_COUNT = 0.5f;		//�A�j���[�V�������Ԃ̒ʏ푝����


//�L�����N�^�[�N���X
class Character {
protected:

	int modelHandle;	//���f���n���h��

	VECTOR pos;			//���W
	float size;			//�T�C�Y

	int HP;				//�̗�
	float speed;		//�ړ����x

	//�U���֌W
	VECTOR attackPos;	//�U���̍��W
	int attackPower;	//�U����
	float attackSize;	//�U���̃T�C�Y

	//�A�j���[�V�����֌W
	int* animIndex;		//�A�j���[�V�����̃A�^�b�`�ԍ�
	int curAnim;		//���݂̃A�j���[�V����
	int preAnim;		//�O�̃A�j���[�V����
	float* animBlend;	//�A�j���[�V�����u�����h��
	float animNum;		//�A�j���[�V�����J�E���g������
	float animCount;	//�A�j���[�V�����J�E���g
	float animAllTime;	//�A�j���[�V����������

public:

	Character();
	~Character(){}

	//������
	virtual void Init() = 0;

	//�ʏ폈��
	virtual void Step() = 0;

	//�`��
	virtual void Draw() = 0;

	//�j��
	virtual void Delete() = 0;

	//�A�j���[�V����
	virtual void Animation() = 0;

	//�A�j���[�V�����̏�����
	void InitAnim(int anim_num);

	//�A�j���[�V�����ύX
	void ChangeAnim(int anim_type);

	//�A�j���[�V�����̍X�V
	void UpdateAnim();

	//�A�j���[�V�����j��
	void DeleteAnim();

	//���W�𓾂�
	VECTOR GetPos() { return pos; }

	//�T�C�Y�𓾂�
	float GetSize() { return size; }

	//�U���̍��W�𓾂�
	VECTOR GetAttackPos() { return attackPos; }

	//�U���̃T�C�Y�𓾂�
	float GetAttackSize() { return attackSize; }

	//�U���͂𓾂�
	int GetAttackPower() { return attackPower; }

	//HP�𓾂�
	int GetHP() { return HP; }

	//���W���Z�b�g
	void SetPos(VECTOR set_pos) { pos = set_pos; }
};