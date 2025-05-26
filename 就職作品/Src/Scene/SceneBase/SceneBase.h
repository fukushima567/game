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

	//‰Šú‰»
	virtual void Init()=0;

	//’Êíˆ—
	virtual void Step() = 0;
	
	//•`‰æˆ—
	virtual void Draw() = 0;
	
	//”jŠüˆ—
	virtual void Delete() = 0;
	
	bool GetFin() { return fin; }
};