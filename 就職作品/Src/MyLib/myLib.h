#pragma once
#include <math.h>
#include "../Common.h"


//個人的によく使う機能をまとめたもの
class MyLib{

public:

	//入力された角度（度）のラジアンを得る
	static float GetRadian(float degree);

	//入力されたラジアンの角度を得る
	static float GetDegree(float radian);

	//指定された円のラジアン位置のX座標を得る
	static float GetCircleX(float PosX, float radius, float radian);

	//指定された円のラジアン位置のY座標を得る
	static float GetCircleY(float PosY, float radius, float radian);

	//3D空間で指定回転角で移動
	static VECTOR Get3DCircle(VECTOR pos, float x_rot, float y_rot, float radius);

	//２点間の距離を得る
	static float GetLine(float pos_x, float pos_y, float pos2_x, float pos2_y);

	//3D空間で2点間の距離を得る
	static float Get3DLine(VECTOR pos_1, VECTOR pos_2);

	//２点間のラジアン角を得る
	static float GetPosRadian(float pos_x, float pos_y, float pos2_x, float pos2_y);

	//3D空間で2点間のラジアン角を得る
	static VECTOR Get3DRadian(VECTOR pos_1, VECTOR pos_2);

	//外積の計算
	static float CalcCross(VECTOR pos1, float rot, VECTOR pos2);

	//立方体を描画する 引数1:座標 引数2:直径 引数3:塗りつぶすかどうか
	static void Draw3DBox(VECTOR pos, VECTOR size, bool surface = false, int color = 255);

	//床に画像を描画
	static void Draw3DImageGround(int handle, VECTOR pos,float w_size,float h_size);
};