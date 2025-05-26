#pragma once
#include "../SceneBase/SceneBase.h"

class SceneGameOver :public SceneBase {
private:

	int handle[2];

public:
	
	//‰Šú‰»
	void Init();

	//’Êíˆ—
	void Step();

	//•`‰æˆ—
	void Draw();

	//”jŠüˆ—
	void Delete();
};
