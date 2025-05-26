#pragma once
#include "../SceneBase/SceneBase.h"

class SceneTest :public SceneBase {
private:
	XINPUT_STATE a;
public:

	void Init();
	void Step();
	void Draw();
	void Delete();
};
