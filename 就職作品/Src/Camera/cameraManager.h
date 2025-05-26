#pragma once
#include "startCamera.h"
#include "playerCamera.h"
#include "clearCamera.h"



//カメラマネージャー
class CameraManager {
public:
	//カメラの種類
	enum CameraType {
		CAMERA_TYPE_START,	//開始時カメラ
		CAMERA_TYPE_PLAYER,	//プレイヤーカメラ
		CAMERA_TYPE_CLEAR,	//クリア時カメラ
		CAMERA_TYPE_NUM
	};

private:
	
	//スタートカメラ
	StartCamera startCamera;

	//プレイヤーカメラ
	PlayerCamera playerCamera;

	//クリアカメラ
	ClearCamera clearCamera;

	//カメラの種類
	CameraType cameraType;
	

public:

	//初期化
	void Init();

	//カメラ処理
	void Step(VECTOR focus, float rot,bool num);

	//カメラタイプを得る
	CameraType GetCameraType() { return cameraType; }

	//カメラの回転を得る
	VECTOR GetRot();

	//注視点との距離を得る
	float GetRadius() { return playerCamera.GetRadius(); }

	//カメラタイプを変更
	void SetCameraType(CameraType camera_type) { cameraType = camera_type; }

	//ニアーとファーをセット
	void SetNearFar(float camera_near, float camera_far);
};