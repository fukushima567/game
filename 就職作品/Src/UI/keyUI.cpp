#include "KeyUI.h"

int KeyUI::keyImageHandle[IMAGE_KEY_NUM];


//‰æ‘œ‰Šú‰»
void KeyUI::Init() {

	LoadDivGraph("Data/Image/key.png", IMAGE_KEY_NUM, IMAGE_KEY_NUM/2, 2, 48, 48, keyImageHandle);
 }


//ƒL[‰æ‘œ‚Ì•`‰æ
void KeyUI::Draw(KEY_IMAGE_TYPE image_type,int x,int y) {

	DrawGraph(x, y, keyImageHandle[image_type], true);
}