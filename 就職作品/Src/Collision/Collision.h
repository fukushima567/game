#ifndef __COLLISION_H__
#define __COLLISION_H__



class Collision {
public:

	/*2D‚Ì“–‚½‚è”»’è*/

	//‹éŒ`‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
	static bool Rect(float X1, float Y1, float Xw1, float Yh1, float X2, float Y2, float Xw2, float Yh2);

	//‰~‚Æ‰~‚Ì“–‚½‚è”»’è
	static bool Circle(float X1, float Y1, float radius1, float X2, float Y2, float radius2);

	//‰~‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
	static bool RectAndCircle(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_size_x, float rect_size_y);


	/*3D‚Ì“–‚½‚è”»’è*/

	//’¼•û‘Ì‚Æ’¼•û‘Ì‚Ì“–‚½‚è”»’è
	static bool Box(VECTOR box, VECTOR size, VECTOR box2, VECTOR size2);


	//‹…‚Æ‹…‚Ì“–‚½‚è”»’è
	static bool Sphere(VECTOR sphere, VECTOR sphere2, float radius, float radius2);


	//‹…‚Æ‹…‚Ì‰Ÿ‚µ–ß‚µ
	static VECTOR SpherePush(VECTOR sphere, VECTOR sphere2, float radius, float radius2);

};


#endif