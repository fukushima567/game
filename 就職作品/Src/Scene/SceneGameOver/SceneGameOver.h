#pragma once
#include "../SceneBase/SceneBase.h"

class SceneGameOver :public SceneBase {
private:

	int handle[2];

public:
	
	void Init();
	void Step();
	void Draw();
	void Delete();
};
