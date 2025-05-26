#pragma once
#include "../../MyLib/myLib.h"
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


//�^�C�g����ʂ̉摜
enum TITLE_IMAGE_TYPE {
	TITLE_IMAGE_STAGE,		//�X�e�[�W�摜
	TITLE_IMAGE_PLAYER,		//�v���C���[�摜
	TITLE_IMAGE_ENEMY,		//�G�摜
	TITLE_IMAGE_BOSS,		//�{�X�摜
	TITLE_IMAGE_START,		//�X�^�[�g�{�^���摜
	TITLE_IMAGE_NAME,		//�^�C�g�����摜

	TITLE_IMAGE_NUM			//�摜�̑���
};


constexpr float START_UI_X_SIZE = 512.0f;		//�X�^�[�g�{�^��X�T�C�Y
constexpr float START_UI_Y_SIZE = 256.0f;		//�X�^�[�g�{�^��Y�T�C�Y


//�^�C�g���V�[��
class SceneTitle :public SceneBase {
private:

	int handle[TITLE_IMAGE_NUM];	//�^�C�g���摜
	VECTOR pos;						//�^�C�g��UI���W
	float scale;					//�^�C�g��UI��������

	float radian;					//�^�C�g���摜�ړ��p���W�A��

	bool select;					//�I���t���O

	Cursor cursor;					//�J�[�\��

public:
	
	//������
	void Init();
	
	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�j������
	void Delete();
};