#ifndef __COLLISION_H__
#define __COLLISION_H__



class Collision {
public:

	/*2D�̓����蔻��*/

	//��`�Ƌ�`�̓����蔻��
	static bool Rect(float X1, float Y1, float Xw1, float Yh1, float X2, float Y2, float Xw2, float Yh2);

	//�~�Ɖ~�̓����蔻��
	static bool Circle(float X1, float Y1, float radius1, float X2, float Y2, float radius2);

	//�~�Ƌ�`�̓����蔻��
	static bool RectAndCircle(float circle_x, float circle_y, float radius, float rect_x, float rect_y, float rect_size_x, float rect_size_y);


	/*3D�̓����蔻��*/

	//�����̂ƒ����̂̓����蔻��
	static bool Box(VECTOR box, VECTOR size, VECTOR box2, VECTOR size2);


	//���Ƌ��̓����蔻��
	static bool Sphere(VECTOR sphere, VECTOR sphere2, float radius, float radius2);


	//���Ƌ��̉����߂�
	static VECTOR SpherePush(VECTOR sphere, VECTOR sphere2, float radius, float radius2);

};


#endif