#pragma once
#include "../SceneBase/SceneBase.h"

class SceneGameOver :public SceneBase {
private:

	int handle[2];

public:
	
	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//破棄処理
	void Delete();
};
