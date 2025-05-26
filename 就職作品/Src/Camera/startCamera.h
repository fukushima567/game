#pragma once
#include "DxLib.h"


//カメラ1度目の移動
constexpr VECTOR START_CAMERA_POS_1 = { 0.0f,50.0f,500.0f };	//カメラの座標1
constexpr VECTOR START_CAMERA_ROT_1 = { 0.349f,0.0f,0.0f };		//カメラの回転1
constexpr float  START_CAMERA_MIN_Z = -10.0f;					//カメラの最小ｚ座標

//カメラ2度目の移動
constexpr VECTOR START_CAMERA_POS_2 = { -200.0f,70.0f,250.0f };	//カメラの座標2
constexpr VECTOR START_CAMERA_ROT_2 = { 0.349f,1.396f, 0.0f };	//カメラの回転2

//カメラ3度目の移動
constexpr VECTOR START_CAMERA_POS_3 = { 500.0f,20.0f,250.0f };	//カメラの座標3
constexpr VECTOR START_CAMERA_ROT_3 = { 0.523f, 5.235f, 0.0f };	//カメラの回転3
constexpr VECTOR START_CAMERA_UP = { 0.0f,1.0f,0.0f };			//カメラの上方向

constexpr float START_CAMERA_ROT_NUM = 0.002f;					//カメラのロット変化量


//視点移動の種類
enum VIEW_POINT_STATE {
	VIEW_MOVE,		//後ろに動く
	VIEW_SIDE,		//横回転		
	VIEW_UP			//上に回転
};

//開始時カメラ
class StartCamera {
private:

	VECTOR cameraPos;		//カメラの位置
	VECTOR cameraRot;		//カメラの角度
	int viewPointState;		//視点の状態


public:

	StartCamera();
	~StartCamera(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//取得関係
	//カメラの回転を得る
	VECTOR GetRot() { return cameraRot; }
};