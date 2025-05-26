#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


constexpr char CURSOR_PATH[128] = { "data/image/cursor.png" };	//�J�[�\���摜�̃p�X

constexpr float CURSOR_RADIUS = 16.0f;							//�J�[�\���̔��a
constexpr float CURSOR_SCALE = 2.0f;							//�J�[�\���̃X�P�[��
constexpr float CURSOR_RAD_ADD_NUM = 0.05f;						//�J�[�\����]�l������

constexpr int CURSOR_PAD_SPEED = 1000;							//�R���g���[���[�̃J�[�\���̈ړ����x

constexpr VECTOR CURSOR_KEY_POS = { 1800.0f, 1000.0f,0.0f };	//�J�[�\���L�[�̉摜���W


//�J�[�\���N���X
class Cursor{
private:

	int handle;			//�J�[�\���摜

	VECTOR pos;			//�J�[�\�����W

	float radian;		//��]�p�x
	float radius;		//�J�[�\�����a
	bool select;		//�I���t���O

	//�֐�
public:
	Cursor();
	~Cursor(){}

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��
	void Delete();

	//�擾�֌W
	//�J�[�\�����a�𓾂�
	float GetRadius() { return radius; }

	//�J�[�\�����W�𓾂�
	VECTOR GetPos() { return pos; }

	//�Z�b�g�֌W
	//�I����Ԃ��Z�b�g
	void Select() { select = true; }
};

