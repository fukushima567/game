#include "DxLib.h"
#include "Collision.h"
#include "../MyLib/MyLib.h"


//四角と四角の当たり判定
bool Collision::Rect(float X1, float Y1, float Xw1, float Yh1, float X2, float Y2, float Xw2, float Yh2) {

	if (X1< X2 + Xw2 &&
		X1 + Xw1> X2 &&
		Y1 + Yh1 > +Y2 &&
		Y1 < Y2 + Yh2) {
		return true;
	}
	else {
		return false;
	}
}


//円と円の当たり判定
bool Collision::Circle(float X1, float Y1, float radius1, float X2, float Y2, float radius2) {

	if ((radius1 + radius2) * (radius1 + radius2) > (X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1)) {
		return true;
	}
	return false;
}


//円と矩形の当たり判定
bool Collision::RectAndCircle(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_size_x, float rect_size_y) {

	//円の中心と四角で一番近い点を探す
	float collision_x = 0;
	float collision_y = 0;
	if (circle_x <= rect_x) {
		collision_x = rect_x;
	}
	else if (circle_x >= rect_x + rect_size_x) {
		collision_x = rect_x + rect_size_x;
	}
	else {
		collision_x = circle_x;
	}
	if (circle_y <= rect_y) {
		collision_y = rect_y;
	}
	else if (circle_y >= rect_y + rect_size_y) {
		collision_y = rect_y + rect_size_y;
	}
	else {
		collision_y = circle_y;
	}

	//探した点と円で当たり判定をとる
	if (Collision::Circle(collision_x, collision_y, 0, circle_x, circle_y, radius)) {
		return true;
	}
	return false;
}


//直方体と直方体の当たり判定
bool Collision::Box(VECTOR box, VECTOR size, VECTOR box2, VECTOR size2) {

	VECTOR s = VScale(size, 0.5f);
	box.x -= s.x;
	box.y -= s.y;
	box.z -= s.z;


	s = VScale(size2, 0.5f);
	box2.x -= s.x;
	box2.y -= s.y;
	box2.z -= s.z;


	if (box2.x < box.x + size.x &&
		box2.x + size2.x > box.x &&
		box2.y + size2.y > box.y &&
		box2.y < box.y + size.y &&
		box2.z + size2.z > box.z &&
		box2.z < box.z + size.z) {

		return true;
	}
	return false;
}

	
//球と球の当たり判定
bool Collision::Sphere(VECTOR sphere, VECTOR sphere2, float radius, float radius2) {

	if ((sphere.x - sphere2.x) * (sphere.x - sphere2.x) + (sphere.y - sphere2.y) * (sphere.y - sphere2.y) + (sphere.z - sphere2.z) * (sphere.z - sphere2.z) < (radius + radius2) * (radius + radius2)) {
		return true;
	}
	return false;
}


//球と球の押し戻し
VECTOR Collision::SpherePush(VECTOR sphere, VECTOR sphere2, float radius, float radius2) {

	//めり込み量を計算
	float radi_1 = radius + radius2;
	float radi_2 = (sphere.x - sphere2.x) * (sphere.x - sphere2.x) + (sphere.y - sphere2.y) * (sphere.y - sphere2.y) + (sphere.z - sphere2.z) * (sphere.z - sphere2.z);
	radi_1 = radi_1 - sqrtf(radi_2);

	//押し戻し
	VECTOR new_pos;
	new_pos = VSub(sphere, sphere2);
	new_pos = VNorm(new_pos);
	new_pos = VScale(new_pos, radi_1);
	sphere = VAdd(sphere, new_pos);
	return sphere;
}