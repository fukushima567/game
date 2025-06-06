#ifndef __COLLISION_H__
#define __COLLISION_H__



class Collision {
public:

	/*2Dの当たり判定*/

	//矩形と矩形の当たり判定
	static bool Rect(float X1, float Y1, float Xw1, float Yh1, float X2, float Y2, float Xw2, float Yh2);

	//円と円の当たり判定
	static bool Circle(float X1, float Y1, float radius1, float X2, float Y2, float radius2);

	//円と矩形の当たり判定
	static bool RectAndCircle(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_size_x, float rect_size_y);


	/*3Dの当たり判定*/

	//直方体と直方体の当たり判定
	static bool Box(VECTOR box, VECTOR size, VECTOR box2, VECTOR size2);


	//球と球の当たり判定
	static bool Sphere(VECTOR sphere, VECTOR sphere2, float radius, float radius2);


	//球と球の押し戻し
	static VECTOR SpherePush(VECTOR sphere, VECTOR sphere2, float radius, float radius2);

};


#endif