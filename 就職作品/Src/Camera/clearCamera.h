#pragma once
#include "DxLib.h"


constexpr VECTOR CLEAR_CAMERA_FIRST_POS = { 0.0f,18.0f,8.0f };		//カメラの初期座標
constexpr VECTOR CLEAR_CAMERA_FIRST_FOCUS = { 0.0f,18.0f,0.0f };	//カメラの初期注視点
constexpr VECTOR CLEAR_CAMERA_UP = { 0.0f,1.0f,0.0f };				//カメラの上方向

constexpr int CLEAR_CAMERA_MOVE_FRAME_1 = 120;						//カメラが移動するフレーム１
constexpr int CLEAR_CAMERA_MOVE_FRAME_2 = 160;						//カメラが移動するフレーム２

constexpr float CLEAR_CAMERA_MOVE_NUM = 0.5f;						//カメラの移動量
constexpr float CLEAR_CAMERA_MAX_FOCUS_X = 20.0f;					//カメラのX最大注視点
constexpr float CLEAR_CAMERA_MIN_POS_Y= 15.0f;						//カメラのY最大位置
constexpr float CLEAR_CAMERA_MAX_POS_Z = 35.0f;						//カメラのZ最大位置


//クリア時カメラ
class ClearCamera {
private:

	VECTOR cameraPos;		//カメラの位置
	VECTOR cameraFocus;		//カメラの注視点
	VECTOR cameraUp;		//カメラの上方向
	VECTOR cameraRot;		//カメラの回転

	int frameCount;			//フレームのカウント

public:

	ClearCamera();
	~ClearCamera(){}

	//初期化
	void Init();

	//通常処理
	void Step();

	//取得関係
	//カメラの回転を得る
	VECTOR GetRot() { return cameraRot; }
};