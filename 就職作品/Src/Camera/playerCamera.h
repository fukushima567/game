#pragma once
#include "DxLib.h"


//共通
constexpr VECTOR PLAYER_CAMERA_UP = { 0.0f,1.0f,0.0f };			//カメラの上方向
constexpr float	 PLAYER_CAMERA_ADD_FOCUS_NUM = 18.0f;			//注視点を上に向ける量
constexpr float	 PLAYER_CAMERA_RADIUS_CHANGE_NUM = 5.0f;		//注視点との距離の変化量
constexpr float	 PAD_SENSITIVITY = 300000.0f;					//コントローラー感度
constexpr float	 MOUSE_SENSITIVITY = 200.0f;					//マウス感度


//通常時
constexpr float PLAYER_CAMERA_NORMAL_RADIUS_NUM = -55.0f;		//通常時のカメラと注視点の距離
constexpr float PLAYER_CAMERA_MAX_NORMAL_ROT_X = 70.0f;			//通常時時のカメラ最大Ｘ
constexpr float PLAYER_CAMERA_MIN_NORMAL_ROT_X = -60.0f;		//通常時時のカメラ最小Ｘ


//ダッシュ
constexpr float PLAYER_CAMERA_DASH_RADIUS_NUM = -1.0f;			//ダッシュ時の注視点との距離
constexpr float PLAYER_CAMERA_MAX_DASH_ROT_X = 10.0f;			//ダッシュ時のカメラ最大Ｘ
constexpr float PLAYER_CAMERA_MIN_DASH_ROT_X = -10.0f;			//ダッシュ時のカメラ最小Ｘ
constexpr float PLAYER_CAMERA_LICK_ROT_Y_NUM = 0.06f;			//ロックオン変更時のカメラ回転量



//プレイヤーカメラ
class PlayerCamera {
private:

	VECTOR cameraPos;		//カメラの位置
	VECTOR cameraFocus;		//カメラの注視点
	VECTOR cameraUp;		//カメラの上方向
	VECTOR cameraRot;		//カメラの回転

	int mouseX;				//マウスの移動量X
	int mouseY;				//マウスの移動量Y

	float radius;			//注視点との距離
	float maxRadius;		//注視点との最大距離

public:

	PlayerCamera();
	~PlayerCamera(){}

	//初期化処理
	void Init();

	//通常処理
	void Step(VECTOR focus,float lock_rad, bool is_dash);
	
	//取得関係
	//カメラの回転を得る
	VECTOR GetRot() { return cameraRot; }

	//カメラと注視点の距離を得る
	float GetRadius() { return radius; }
};