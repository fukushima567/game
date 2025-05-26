#pragma once
#include "SceneBase/SceneBase.h"


//シーンの状態
enum SceneState {
	INIT,
	LOOP,
};


//シーンマネージャークラス
class SceneManager {
private:

	int loadImageHandle;

	SceneBase* sceneBase;
	
	SceneState sceneState;

public:

	//シーンマネージャーの初期化
	void Init();

	//シーンマネージャーの通常処理
	void Step();
};