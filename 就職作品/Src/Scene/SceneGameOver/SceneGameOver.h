#pragma once
#include "../SceneBase/SceneBase.h"

class SceneGameOver :public SceneBase {
private:

	int handle[2];

public:
	
	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�j������
	void Delete();
};
