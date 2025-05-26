#include "cursor.h"


//�R���X�g���N�^
Cursor::Cursor() {

	handle = 0;

	memset(&pos,0,sizeof(VECTOR));
	
	radian = 0.0f;
	radius = 0.0f;

	select = false;
}


//������
void Cursor::Init() {

	//�摜�ǂݍ���
	handle = LoadGraph(CURSOR_PATH);

	//���W�Z�b�g
	pos = {SCREEN_SIZE_X/2,SCREEN_SIZE_Y/2,0};
	
	radius = CURSOR_RADIUS;
}


//�ʏ폈��
void Cursor::Step() {

	int mouse_x = 0;
	int mouse_y = 0;

	//�}�E�X�ړ��ʎ擾
	Input::GetMouseNum(&mouse_x, &mouse_y);

	pos.x += mouse_x;
	pos.y += mouse_y;

	//�R���g���[���[�ړ��ʎ擾
	pos.x += (float)PadInput::GetLX()/ CURSOR_PAD_SPEED;
	pos.y -= (float)PadInput::GetLY() / CURSOR_PAD_SPEED;

	//��ʊO�ɂ����Ȃ��悤�ɂ���
	if (pos.x < 0) {//X
		pos.x = 0;
	}
	if (pos.x > SCREEN_SIZE_X) {
		pos.x = SCREEN_SIZE_X;
	}

	if (pos.y < 0) {//Y
		pos.y = 0;
	}
	if (pos.y > SCREEN_SIZE_Y) {
		pos.y = SCREEN_SIZE_Y;
	}

	//�I������Ă�����J�[�\���摜��]
	if (select) {
		radian += CURSOR_RAD_ADD_NUM;
	}
	else {
		radian = 0.0f;
	}
	select = false;
}


//�`��
void Cursor::Draw() {

	//�L�[�̉摜
	if (PadInput::connectPad) {//�R���g���[���[
		KeyUI::Draw(IMAGE_BUTTON_A, (int)CURSOR_KEY_POS.x, (int)CURSOR_KEY_POS.y);
	}
	else {//�L�[�{�[�h
		KeyUI::Draw(IMAGE_MOUSE_LEFT, (int)CURSOR_KEY_POS.x, (int)CURSOR_KEY_POS.y);
	}

	//�J�[�\���摜
	DrawRotaGraph((int)pos.x,(int)pos.y, CURSOR_SCALE, radian,handle,true);
}


//�j��
void Cursor::Delete() {

	DeleteGraph(handle);
}