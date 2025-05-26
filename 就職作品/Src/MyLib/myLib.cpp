#include "myLib.h"



//入力された角度（度）のラジアンを得る
float MyLib::GetRadian(float degree) {

	return degree * DX_PI_F/180;
}


//入力されたラジアンの角度を得る
float MyLib::GetDegree(float radian) {

	return radian * 180 / DX_PI_F;
}


//指定された円のラジアン位置のX座標を得る
float MyLib::GetCircleX(float PosX,float radius,float radian) {

	return PosX + radius * (float)cos(radian);
}


//指定された円のラジアン位置のY座標を得る
float MyLib::GetCircleY(float PosY, float radius, float radian) {

	return PosY + radius * (float)sin(radian);
}


//3D空間で指定回転角で移動
VECTOR MyLib::Get3DCircle(VECTOR pos, float x_rot, float y_rot, float radius) {

	pos.z = pos.z + radius * (cosf(y_rot) * cosf(x_rot));
	pos.x = pos.x + radius * (sinf(y_rot) * cosf(x_rot));
	pos.y = pos.y + radius * sinf(x_rot);

	return pos;
}


//２点間の距離を得る
float MyLib::GetLine(float pos_x, float pos_y, float pos2_x, float pos2_y) {

	return sqrtf((pos_x - pos2_x) * (pos_x - pos2_x) + (pos_y - pos2_y) * (pos_y - pos2_y));
}


//3D空間で2点間の距離を得る
float MyLib::Get3DLine(VECTOR pos_1, VECTOR pos_2) {

	return sqrtf((pos_1.x - pos_2.x) * (pos_1.x - pos_2.y) + (pos_1.y - pos_2.y) * (pos_1.y - pos_2.y)+ (pos_1.z - pos_2.z) * (pos_1.z - pos_2.z));
}


//２点間のラジアン角を得る
float MyLib::GetPosRadian(float pos_x, float pos_y, float pos2_x, float pos2_y) {

	return (float)atan2(pos2_y - pos_y, pos2_x - pos_x);
}


//3D空間で2点間のラジアン角を得る
 VECTOR MyLib::Get3DRadian(VECTOR pos_1, VECTOR pos_2) {
	VECTOR rot = {0,0,0};
	rot.y=atan2f(pos_2.x - pos_1.x, pos_2.z - pos_1.z);
	float line=GetLine(pos_1.x, pos_1.z, pos_2.x, pos_2.z);
	rot.x= -atan2f(pos_2.y - pos_1.y, line);
	return rot;
}


 //2D外積の計算
 float MyLib::CalcCross(VECTOR pos1,float rot, VECTOR pos2) {

	 VECTOR v1;
	 v1.x = pos2.x - pos1.x;
	 v1.y = 0;
	 v1.z = pos2.z - pos1.z;

	 VECTOR v_spd;
	 v_spd.x = sinf(rot);
	 v_spd.y = 0.0f;
	 v_spd.z = cosf(rot);
	 return v1.z * v_spd.x - v1.x * v_spd.z;

 }


//3D空間に直方体を描画
void MyLib::Draw3DBox(VECTOR pos, VECTOR size,bool surface,int color) {
	pos.x -= size.x / 2;
	
	pos.z -= size.z / 2;

	//立方体の面
	if (surface) {
		
		DrawTriangle3D({ pos.x + size.x,pos.y,pos.z }, pos, { pos.x,pos.y+size.y,pos.z }, color, true);
		DrawTriangle3D({ pos.x + size.x,pos.y,pos.z }, { pos.x,pos.y + size.y,pos.z }, { pos.x + size.x, pos.y + size.y, pos.z }, color, true);

		DrawTriangle3D({ pos.x,pos.y,pos.z+size.z }, pos, { pos.x,pos.y + size.y,pos.z }, color, true);
		DrawTriangle3D({ pos.x ,pos.y,pos.z+size.z }, { pos.x,pos.y + size.y,pos.z }, { pos.x , pos.y + size.y, pos.z+size.z }, color, true);
		
		DrawTriangle3D({ pos.x+size.x,pos.y,pos.z }, pos, { pos.x,pos.y,pos.z+size.z }, color, true);
		DrawTriangle3D({ pos.x+size.x,pos.y,pos.z+size.z }, { pos.x+size.x,pos.y ,pos.z }, { pos.x , pos.y, pos.z + size.z }, color, true);
	
		DrawTriangle3D({ pos.x + size.x,pos.y + size.y,pos.z }, { pos.x,pos.y+size.y,pos.z }, { pos.x,pos.y + size.y,pos.z + size.z }, color, true);
		DrawTriangle3D({ pos.x + size.x,pos.y+size.y,pos.z + size.z }, { pos.x + size.x,pos.y+size.y ,pos.z }, { pos.x , pos.y+size.y, pos.z + size.z }, color, true);
	
		DrawTriangle3D({ pos.x + size.x,pos.y,pos.z + size.z }, { pos.x,pos.y,pos.z + size.z }, { pos.x,pos.y + size.y,pos.z + size.z }, color, true);
		DrawTriangle3D({ pos.x + size.x,pos.y,pos.z + size.z }, { pos.x,pos.y + size.y,pos.z + size.z }, { pos.x + size.x, pos.y + size.y, pos.z + size.z }, color, true);
	
		DrawTriangle3D({ pos.x + size.x,pos.y,pos.z + size.z }, { pos.x + size.x,pos.y,pos.z }, { pos.x + size.x,pos.y + size.y,pos.z }, color, true);
		DrawTriangle3D({ pos.x+size.x ,pos.y,pos.z + size.z }, { pos.x+size.x,pos.y + size.y,pos.z }, { pos.x+size.x , pos.y + size.y, pos.z + size.z }, color, true);
	}

	//立方体の線
	DrawLine3D({ pos.x+size.x,pos.y,pos.z },pos,0);
	DrawLine3D({ pos.x,pos.y+size.y,pos.z }, pos, 0);
	DrawLine3D({ pos.x,pos.y,pos.z+size.z }, pos, 0);
	DrawLine3D({ pos.x + size.x,pos.y + size.y,pos.z }, { pos.x,pos.y+size.y,pos.z }, 0);
	DrawLine3D({ pos.x,pos.y + size.y,pos.z }, { pos.x,pos.y + size.y,pos.z+size.z }, 0);
	DrawLine3D({ pos.x+size.x ,pos.y + size.y,pos.z }, { pos.x+size.x,pos.y,pos.z }, 0);
	DrawLine3D({ pos.x+size.x ,pos.y,pos.z }, { pos.x+size.x,pos.y,pos.z+size.z }, 0);
	DrawLine3D({ pos.x + size.x ,pos.y+size.y,pos.z }, { pos.x + size.x,pos.y+size.y,pos.z + size.z }, 0);
	DrawLine3D({ pos.x + size.x ,pos.y,pos.z+size.z }, { pos.x + size.x,pos.y + size.y,pos.z + size.z }, 0);
	DrawLine3D({ pos.x ,pos.y + size.y,pos.z+size.z }, { pos.x ,pos.y,pos.z+size.z }, 0);
	DrawLine3D({ pos.x + size.x ,pos.y,pos.z + size.z }, { pos.x ,pos.y,pos.z + size.z }, 0);
	DrawLine3D({ pos.x + size.x ,pos.y+size.y,pos.z + size.z }, { pos.x ,pos.y+size.y,pos.z + size.z }, 0);
}


//床に画像を描画
void MyLib::Draw3DImageGround(int handle, VECTOR pos, float w_size, float h_size) {

	VERTEX3D Vertex[6];

	// ２ポリゴン分の頂点のデータをセット
	Vertex[0].pos = VGet(pos.x - w_size, 0.01f, pos.z - h_size);
	Vertex[0].norm = VGet(0.0f, 1, 0);
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(pos.x + w_size, 0.01f, pos.z - h_size);
	Vertex[1].norm = VGet(0.0f, 1, 0);
	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(pos.x - w_size, 0.01f, pos.z + h_size);
	Vertex[2].norm = VGet(0.0f, 1, 0);
	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].pos = VGet(pos.x + w_size, 0.01f, pos.z + h_size);
	Vertex[3].norm = VGet(0.0f, 1, 0);
	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1;
	Vertex[3].v = 1;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4].pos = VGet(pos.x + w_size, 0.01f, pos.z - h_size);
	Vertex[4].norm = VGet(0.0f, 1, 0);
	Vertex[4].dif = GetColorU8(255, 255, 255, 255);
	Vertex[4].spc = GetColorU8(0, 0, 0, 0);
	Vertex[4].u = 1;
	Vertex[4].v = 0.0f;
	Vertex[4].su = 0.0f;
	Vertex[4].sv = 0.0f;

	Vertex[5].pos = VGet(pos.x - w_size, 0.01f, pos.z + h_size);
	Vertex[5].norm = VGet(0.0f, 1, 0);
	Vertex[5].dif = GetColorU8(255, 255, 255, 255);
	Vertex[5].spc = GetColorU8(0, 0, 0, 0);
	Vertex[5].u = 0.0f;
	Vertex[5].v = 1;
	Vertex[5].su = 0.0f;
	Vertex[5].sv = 0.0f;

	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, handle, true);
}