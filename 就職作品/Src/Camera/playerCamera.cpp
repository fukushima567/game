#include "playerCamera.h"
#include "../MyLib/myLib.h"
#include "../Common.h"
#include "../GameData/gameData.h"


//コンストラクタ
PlayerCamera::PlayerCamera() {

	memset(&cameraPos,0,sizeof(VECTOR));
	memset(&cameraFocus, 0, sizeof(VECTOR));
	memset(&cameraUp, 0, sizeof(VECTOR));
	memset(&cameraRot, 0, sizeof(VECTOR));

	mouseX = 0;
	mouseY = 0;
	radius = 0.0f;
	maxRadius = 0.0f;
}


//初期化処理
void PlayerCamera::Init() {

	cameraUp = PLAYER_CAMERA_UP;
	radius = PLAYER_CAMERA_NORMAL_RADIUS_NUM;
}


//通常処理
void PlayerCamera::Step(VECTOR focus,  float lock_rad, bool is_dash) {

	//マウス移動量取得
	Input::GetMouseNum(&mouseX, &mouseY);

	//マウスのカメラ横移動
	if (lock_rad == -1) {
		float mouse_num_x;
		mouse_num_x = (float)mouseX;
		if (mouse_num_x != 0) {
			cameraRot.y += mouse_num_x / MOUSE_SENSITIVITY;
		}
	}

	//マウスのカメラ縦移動
	float mouse_num_y;
	mouse_num_y = (float)mouseY;
	if (mouse_num_y != 0) {
		cameraRot.x += (int)mouse_num_y / MOUSE_SENSITIVITY;
	}
	
	//コントローラーのカメラ移動
	if (lock_rad == -1) {
		cameraRot.x -= (float)PadInput::GetRY() / PAD_SENSITIVITY;
		cameraRot.y += (float)PadInput::GetRX() / PAD_SENSITIVITY;
	}

	
	//走っていれば一人称に
	if (is_dash) {
		maxRadius = PLAYER_CAMERA_DASH_RADIUS_NUM;
	}
	else {
		maxRadius = PLAYER_CAMERA_NORMAL_RADIUS_NUM;
	}
	
	//カメラの距離変更
	if (radius < maxRadius) {
		radius += PLAYER_CAMERA_RADIUS_CHANGE_NUM;
	}
	if (radius > maxRadius) {
		radius -= PLAYER_CAMERA_RADIUS_CHANGE_NUM;
	}

	//ロックオン
	if (lock_rad != -1) {
		if (lock_rad > cameraRot.y + MyLib::GetRadian(180)) {
			lock_rad -= MyLib::GetRadian(360);
		}
		if (lock_rad < cameraRot.y - MyLib::GetRadian(180)) {
			lock_rad += MyLib::GetRadian(360);
		}

		if (cameraRot.y < lock_rad) {
			cameraRot.y += PLAYER_CAMERA_LICK_ROT_Y_NUM;
			if (cameraRot.y >= lock_rad) {
				cameraRot.y = lock_rad;
			}
		}
		if (cameraRot.y > lock_rad) {
			cameraRot.y -= PLAYER_CAMERA_LICK_ROT_Y_NUM;
			if (cameraRot.y <= lock_rad) {
				cameraRot.y = lock_rad;
			}
		}
	}
	
	//角度の制限
	float max_rot_x;
	float min_rot_x;

	if (is_dash) {//ダッシュしている時のX角度制限
		max_rot_x = PLAYER_CAMERA_MAX_DASH_ROT_X;
		if (cameraRot.x > MyLib::GetRadian(max_rot_x)) {
			cameraRot.x = MyLib::GetRadian(max_rot_x);
		}

		min_rot_x = PLAYER_CAMERA_MIN_DASH_ROT_X;
		if (cameraRot.x < MyLib::GetRadian(min_rot_x)) {
			cameraRot.x = MyLib::GetRadian(min_rot_x);
		}
	}
	else {//ダッシュしていない時の角度制限
		max_rot_x = PLAYER_CAMERA_MAX_NORMAL_ROT_X;
		if (cameraRot.x > MyLib::GetRadian(max_rot_x)) {
			cameraRot.x = MyLib::GetRadian(max_rot_x);
		}

		min_rot_x = PLAYER_CAMERA_MIN_NORMAL_ROT_X;
		if (cameraRot.x < MyLib::GetRadian(min_rot_x)) {
			cameraRot.x = MyLib::GetRadian(min_rot_x);
		}
	}

	//Y回転の制限
	if (cameraRot.y > MyLib::GetRadian(360)) {
		cameraRot.y -= MyLib::GetRadian(360);
	}
	if (cameraRot.y < MyLib::GetRadian(0)) {
		cameraRot.y += MyLib::GetRadian(360);
	}

	

	focus.y += PLAYER_CAMERA_ADD_FOCUS_NUM;
		
	//カメラ座標を更新
	cameraPos = MyLib::Get3DCircle(focus, -cameraRot.x, cameraRot.y, radius);

	//反映した座標をカメラにセット
	SetCameraPositionAndTargetAndUpVec(cameraPos, focus, cameraUp);
}