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

	//������
	virtual void Init()=0;

	//�ʏ폈��
	virtual void Step() = 0;
	
	//�`�揈��
	virtual void Draw() = 0;
	
	//�j������
	virtual void Delete() = 0;
	
	bool GetFin() { return fin; }
};