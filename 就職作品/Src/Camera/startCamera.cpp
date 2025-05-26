#include "startCamera.h"
#include "../MyLib/MyLib.h"
#include "../Common.h"


//コンストラクタ
StartCamera::StartCamera() {

	memset(&cameraPos,0,sizeof(VECTOR));
	memset(&cameraRot, 0, sizeof(VECTOR));
	viewPointState = 0;
}


//初期化
void StartCamera::Init() {

	cameraPos = START_CAMERA_POS_1;
	cameraRot = START_CAMERA_ROT_1;
	viewPointState = VIEW_MOVE;
}


//通常処理
void StartCamera::Step() {

	//カメラ処理
	switch (viewPointState) {

		//移動
	case VIEW_MOVE:
		cameraPos.z--;
		if (cameraPos.z <= -10) {
			viewPointState = VIEW_SIDE;
			cameraPos = START_CAMERA_POS_2;
			cameraRot = START_CAMERA_ROT_2;
		}
		break;

		//横に回転
	case VIEW_SIDE:
		cameraRot.y -= START_CAMERA_ROT_NUM;
		if (cameraRot.y < MyLib::GetRadian(40)) {
			viewPointState = VIEW_UP;
			cameraPos = START_CAMERA_POS_3;
			cameraRot = START_CAMERA_ROT_3;
		}
		break;

		//上に回転
	case VIEW_UP:
		cameraRot.x -= START_CAMERA_ROT_NUM;
		if (cameraRot.x < MyLib::GetRadian(-10)) {
			viewPointState = VIEW_MOVE;
			cameraPos = START_CAMERA_POS_1;
			cameraRot = START_CAMERA_ROT_1;
		}
		break;
	}

	//カメラにセット
	SetCameraPositionAndAngle(cameraPos, cameraRot.x, cameraRot.y, cameraRot.z);
}