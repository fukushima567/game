#include "cameraManager.h"
#include "../Input/input.h"


void CameraManager::Init(){

	//カメラ初期化
	startCamera.Init();
	playerCamera.Init();
	clearCamera.Init();
}


//カメラマネージャー通常処理
void CameraManager::Step(VECTOR focus, float rot,bool num) {

	//カメラタイプによって処理を変える
	switch (cameraType) {

		//開始時カメラ
	case CAMERA_TYPE_START:
		startCamera.Step();
		break;


		//プレイヤーカメラ
	case CAMERA_TYPE_PLAYER:
		playerCamera.Step(focus, rot, num);
		break;

		//クリア時カメラ
	case CAMERA_TYPE_CLEAR:
		clearCamera.Step();
		break;
	}
}


//画面の描画範囲を設定
void CameraManager::SetNearFar(float camera_near, float camera_far) {

	SetCameraNearFar(camera_near, camera_far);
}


//カメラの回転を得る
VECTOR CameraManager::GetRot() {
	switch (cameraType) {
	case CAMERA_TYPE_START:
		return startCamera.GetRot();
		break;

	case CAMERA_TYPE_PLAYER:
		return playerCamera.GetRot();
		break;

	default:
		return clearCamera.GetRot();
		break;
	}
}