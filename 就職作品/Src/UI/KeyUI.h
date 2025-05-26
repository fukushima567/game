#pragma once
#include "DxLib.h"


//�摜���
enum KEY_IMAGE_TYPE {

	IMAGE_MOUSE_LEFT,	//���N���b�N
	IMAGE_MOUSE_RIGHT,	//�E�N���b�N
	IMAGE_KEY_E,		//E�L�[
	IMAGE_KEY_ESC,		//�G�X�P�[�v�L�[
	IMAGE_KEY_A,		//A�L�[
	IMAGE_KEY_S,		//S�L�[
	IMAGE_KEY_D,		//D�L�[
	IMAGE_KEY_NONE,		//�L�[�Ȃ�
	IMAGE_BUTTON_A,		//A�{�^��
	IMAGE_BUTTON_B,		//B�{�^��
	IMAGE_BUTTON_Y,		//Y�{�^��
	IMAGE_BUTTON_RB,	//RB�{�^��
	IMAGE_BUTTON_START,	//START�{�^��
	IMAGE_STICK_LEFT,	//L�X�e�b�N��
	IMAGE_STICK_BACK,	//L�X�e�b�N��
	IMAGE_STICK_RIGHT,	//L�X�e�b�N�E

	IMAGE_KEY_NUM		//�L�[�摜����
};


//�L�[�摜
class KeyUI {

private:
	static int keyImageHandle[IMAGE_KEY_NUM];

public:
	//������
	static void Init();

	//�`��
	static void Draw(KEY_IMAGE_TYPE image_type,int x, int y);
};