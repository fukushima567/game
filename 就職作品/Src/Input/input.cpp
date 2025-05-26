#include "DxLib.h"
#include "input.h"

#define KEY_BUF_LEN (256)

#define MOUSE_BUF (2)

char preKeyBuf[KEY_BUF_LEN] = { 0 };

char currentKeyBuf[KEY_BUF_LEN] = { 0 };

char preMouseBuf[MOUSE_BUF] = { 0 };

char currentMouseBuf[MOUSE_BUF] = { 0 };

//マウス取得変数
int mouseX;
int mouseY;


//初期化
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


//インプット処理の更新(シーン管理の前に呼ぶ必要あり)
void Input::Step() {

	//キーの入力を更新
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}
	GetHitKeyStateAll(currentKeyBuf);


	//マウスの入力を更新
	memcpy(preMouseBuf, currentMouseBuf, sizeof(char[MOUSE_BUF]));
	memset(currentMouseBuf, 0, sizeof(char[MOUSE_BUF]));

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		currentMouseBuf[MOUSE_LEFT] = 1;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		currentMouseBuf[MOUSE_RIGHT] = 1;
	}

	//マウス移動量更新
	GetMousePoint(&mouseX, &mouseY);
	SetMousePoint(MOUSE_NUM, MOUSE_NUM);
}


//今押された
bool Input::Push(int key_code){
	//前フレで押されていないかつ、現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		//押されていないので false
		return false;
	}
}


//押され続けている
bool Input::Keep(int key_code) {
	//現フレで押されている
	if (currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//離された
bool Input::Release(int key_code) {
	//前フレで押されているかつ、現フレで押されていない。
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0) {
		return true;
	}
	else {
		return false;
	}
}


//マウスクリック今押された
bool Input::PushMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 1&& preMouseBuf[mouse_code]==0) {
		return true;
	}
	return false;

}


//マウスクリック押されている
bool Input::KeepMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 1) {
		return true;
	}
	return false;

}


//マウスクリック離された
bool Input::ReleaseMouse(int mouse_code){

	if (currentMouseBuf[mouse_code] == 0 && preMouseBuf[mouse_code] == 1) {
		return true;
	}
	return false;

}


//マウスの移動量を得る
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
