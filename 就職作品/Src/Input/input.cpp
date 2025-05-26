#include "DxLib.h"
#include "input.h"

#define KEY_BUF_LEN (256)

#define MOUSE_BUF (2)

char preKeyBuf[KEY_BUF_LEN] = { 0 };

char currentKeyBuf[KEY_BUF_LEN] = { 0 };

char preMouseBuf[MOUSE_BUF] = { 0 };

char currentMouseBuf[MOUSE_BUF] = { 0 };

//�}�E�X�擾�ϐ�
int mouseX;
int mouseY;


//������
void Input::Init(){

	for(int index = 0; index < KEY_BUF_LEN; index++) {
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
	preMouseBuf[MOUSE_LEFT] = '\0';
	preMouseBuf[MOUSE_RIGHT] = '\0';
	currentMouseBuf[MOUSE_LEFT] = '\0';
	currentMouseBuf[MOUSE_RIGHT] = '\0';
	mouseX = 0;
	mouseY = 0;
	SetMousePoint(MOUSE_NUM, MOUSE_NUM);
}


//�C���v�b�g�����̍X�V(�V�[���Ǘ��̑O�ɌĂԕK�v����)
void Input::Step() {

	//�L�[�̓��͂��X�V
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}
	GetHitKeyStateAll(currentKeyBuf);


	//�}�E�X�̓��͂��X�V
	memcpy(preMouseBuf, currentMouseBuf, sizeof(char[MOUSE_BUF]));
	memset(currentMouseBuf, 0, sizeof(char[MOUSE_BUF]));

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		currentMouseBuf[MOUSE_LEFT] = 1;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		currentMouseBuf[MOUSE_RIGHT] = 1;
	}

	//�}�E�X�ړ��ʍX�V
	GetMousePoint(&mouseX, &mouseY);
	SetMousePoint(MOUSE_NUM, MOUSE_NUM);
}


//�������ꂽ
bool Input::Push(int key_code){
	//�O�t���ŉ�����Ă��Ȃ����A���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		//������Ă��Ȃ��̂� false
		return false;
	}
}


//�����ꑱ���Ă���
bool Input::Keep(int key_code) {
	//���t���ŉ�����Ă���
	if (currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//�����ꂽ
bool Input::Release(int key_code) {
	//�O�t���ŉ�����Ă��邩�A���t���ŉ�����Ă��Ȃ��B
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0) {
		return true;
	}
	else {
		return false;
	}
}


//�}�E�X�N���b�N�������ꂽ
bool Input::PushMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 1&& preMouseBuf[mouse_code]==0) {
		return true;
	}
	return false;

}


//�}�E�X�N���b�N������Ă���
bool Input::KeepMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 1) {
		return true;
	}
	return false;

}


//�}�E�X�N���b�N�����ꂽ
bool Input::ReleaseMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 0 && preMouseBuf[mouse_code] == 1) {
		return true;
	}
	return false;

}


//�}�E�X�̈ړ��ʂ𓾂�
void Input::GetMouseNum(int* x, int* y) {

	*x = (mouseX - MOUSE_NUM);

	*y = (mouseY - MOUSE_NUM);

	if (*x == -1) {
		*x = 0;
	}
	if (*y == -1) {
		*y = 0;
	}
}
