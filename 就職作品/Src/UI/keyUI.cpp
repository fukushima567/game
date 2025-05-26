#include "KeyUI.h"

int KeyUI::keyImageHandle[IMAGE_KEY_NUM];


//�摜������
void KeyUI::Init() {

	LoadDivGraph("Data/Image/key.png", IMAGE_KEY_NUM, IMAGE_KEY_NUM/2, 2, 48, 48, keyImageHandle);
 }


//�L�[�摜�̕`��
void KeyUI::Draw(KEY_IMAGE_TYPE image_type,int x,int y) {

	DrawGraph(x, y, keyImageHandle[image_type], true);
}