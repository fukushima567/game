#pragma once
#include "Dxlib.h"
#include "../../Common.h"
#include "../../GameData/gameData.h"
#include "../../ScreenEffect/ScreenEffect.h"

class SceneBase {
protected:

	ScreenEffect screenEffect;

	bool change;
	bool fin;

public:

	SceneBase() {
		change = false;
		fin = false;
	}
	~SceneBase(){}

	//初期化
	virtual void Init()=0;

	//通常処理
	virtual void Step() = 0;
	
	//描画処理
	virtual void Draw() = 0;
	
	//破棄処理
	virtual void Delete() = 0;
	
	bool GetFin() { return fin; }
};