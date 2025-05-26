#pragma once
#include "../../MyLib/myLib.h"
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


constexpr int TITLE_IMAGE_NUM=6;

class SceneTitle :public SceneBase {
private:

	int handle[TITLE_IMAGE_NUM];
	VECTOR pos;
	VECTOR size;
	float scale;

	float radian;

	bool select;

	Cursor cursor;

public:
	
	void Init();
	void Step();
	void Draw();
	void Delete();
};