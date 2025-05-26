#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


//�X�e�[�W�̃p�X
constexpr char STAGE_PATH[STAGE_NUM][256] = {
	"data/Image/Play/stage/stage0.mv1",
	"data/Image/Play/stage/stage1.mv1",
	"data/Image/Play/stage/stage2.mv1",
	"data/Image/Play/stage/stage3.mv1",
	"data/Image/Play/stage/stage4.mv1",
};


//�X�J�C�h�[���̃T�C�Y
constexpr VECTOR SKY_DOME_SIZE[STAGE_NUM] = {
	1.5f,1.5f,1.5f,
	1.5f,1.5f,1.5f,
	1.0f,1.0f,1.0f,
	1.2f,1.2f,1.2f,
	1.0f,1.0f,1.0f
};


//�X�e�[�W�N���X
class Stage{
private:

	int skyHandle;		//�X�J�C�h�[���̃n���h��
	VECTOR skyPos;		//�X�J�C�h�[���̍��W

	int stageHandle;	//�X�e�[�W�̃n���h��
	
public:

	Stage();
	~Stage(){};

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��
	void Delete();

	//�X�e�[�W���𓾂�
	int GetStageHandle() {return stageHandle;}

	//�X�J�C�h�[���̍��W���Z�b�g
	void SetPos(VECTOR pos) { skyPos = pos; }
};