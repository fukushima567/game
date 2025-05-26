#include "stage.h"
#include "../MyLib/MyLib.h"


//�R���X�g���N�^
Stage::Stage() {

	skyHandle = 0;
	memset(&skyPos, 0, sizeof(VECTOR));

	stageHandle = 0;
}


//������
void Stage::Init() {

	//�X�e�[�W�̃��[�h
	switch (GameData::GetInstance()->GetStageType()) {
	
	case STAGE_0:
		skyHandle = MV1LoadModel("data/Image/Play/stage/skyDome.x");
		MV1SetScale(skyHandle, SKY_DOME_SIZE[GameData::GetInstance()->GetStageType()]);
		SetFogEnable(false);
		break;

	case STAGE_1:
		skyHandle = MV1LoadModel("data/Image/Play/stage/skyDome.x");
		MV1SetScale(skyHandle, SKY_DOME_SIZE[GameData::GetInstance()->GetStageType()]);
		SetFogEnable(true);
		SetFogStartEnd(0, 2500);
		SetFogColor(200, 200, 240);
		break;

	case STAGE_2:
		SetFogEnable(true);
		SetFogStartEnd(0, 2500);
		SetFogColor(255, 200, 200);
		break;

	case STAGE_3:
		skyHandle = MV1LoadModel("data/Image/Play/stage/skyDome.x");
		MV1SetScale(skyHandle, SKY_DOME_SIZE[GameData::GetInstance()->GetStageType()]);
		SetFogEnable(true);
		SetFogStartEnd(0, 2500);
		SetFogColor(200, 200, 240);
		break;
		
	case STAGE_4:
		skyHandle = MV1LoadModel("data/Image/Play/stage/skyDome.x");
		SetFogEnable(true);
		SetFogStartEnd(0, 2500);
		SetFogColor(200, 200, 230);
		break;
	}
	
	stageHandle = MV1LoadModel(STAGE_PATH[GameData::GetInstance()->GetStageType()]);
	MV1SetupCollInfo(stageHandle);
}


//�ʏ폈��
void Stage::Step() {

	
	
}


//�`��
void Stage::Draw() {
	
	MV1SetPosition(skyHandle, skyPos);
	MV1DrawModel(skyHandle);
	MV1SetPosition(stageHandle, { 0,0,0 });
	MV1DrawModel(stageHandle);
}


//�j��
void Stage::Delete() {
	MV1DeleteModel(skyHandle);
	MV1DeleteModel(stageHandle);
}


