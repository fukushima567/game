#pragma once
#include <math.h>
#include "../Common.h"


//�l�I�ɂ悭�g���@�\���܂Ƃ߂�����
class MyLib{

public:

	//���͂��ꂽ�p�x�i�x�j�̃��W�A���𓾂�
	static float GetRadian(float degree);

	//���͂��ꂽ���W�A���̊p�x�𓾂�
	static float GetDegree(float radian);

	//�w�肳�ꂽ�~�̃��W�A���ʒu��X���W�𓾂�
	static float GetCircleX(float PosX, float radius, float radian);

	//�w�肳�ꂽ�~�̃��W�A���ʒu��Y���W�𓾂�
	static float GetCircleY(float PosY, float radius, float radian);

	//3D��ԂŎw���]�p�ňړ�
	static VECTOR Get3DCircle(VECTOR pos, float x_rot, float y_rot, float radius);

	//�Q�_�Ԃ̋����𓾂�
	static float GetLine(float pos_x, float pos_y, float pos2_x, float pos2_y);

	//3D��Ԃ�2�_�Ԃ̋����𓾂�
	static float Get3DLine(VECTOR pos_1, VECTOR pos_2);

	//�Q�_�Ԃ̃��W�A���p�𓾂�
	static float GetPosRadian(float pos_x, float pos_y, float pos2_x, float pos2_y);

	//3D��Ԃ�2�_�Ԃ̃��W�A���p�𓾂�
	static VECTOR Get3DRadian(VECTOR pos_1, VECTOR pos_2);

	//�O�ς̌v�Z
	static float CalcCross(VECTOR pos1, float rot, VECTOR pos2);

	//�����̂�`�悷�� ����1:���W ����2:���a ����3:�h��Ԃ����ǂ���
	static void Draw3DBox(VECTOR pos, VECTOR size, bool surface = false, int color = 255);

	//���ɉ摜��`��
	static void Draw3DImageGround(int handle, VECTOR pos,float w_size,float h_size);
};