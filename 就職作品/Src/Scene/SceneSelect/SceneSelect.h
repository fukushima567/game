#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


constexpr char STAGE_TEXT[STAGE_NUM][512]{
	"�ŏ��̃X�e�[�W�ł��B\n�_�b�V�����̍U���𓖂Ă�ƃR���{���������܂��B\n�R���{���q���Ȃ���G��|�����Ƃ�\n�l���X�R�A�������܂��B\n�X�R�A�����܂ŏ㏸������ƃN���A�ɂȂ�܂��B",
	"�N���A�����͓����ł��B\n�������U�������Ă���G���o�ꂵ�܂��B\n������g���A�U��������܂��傤�B\n�|�����Ƃ��ł���΂�葽���X�R�A���l���ł��܂��B\n�R���{���q���ăN���A��ڎw���܂��傤�B",
	"�}�O�}�ɗ�����ƃ_���[�W���󂯂܂��B\n�����Ȃ��悤�ɋC������K�v������܂��B\n�V�����G���o�ꂵ�܂��B\n�^�[�Q�b�g�؂�ւ��������g���A\n������G�̍U��������čU���𓖂Ă܂��傤�B",
	"�V�����G���o�ꂵ�܂��B\n�̗͂������A�|���̂���ςȕ��A\n�l���X�R�A�������Ȃ��Ă��܂��B",
	"�Ō�̃X�e�[�W�ł��B\n�{�X���o�ꂵ�܂��B\n�{�X�͍U�������ہA���݂̃R���{���ɉ����ăX�R�A��\n�㏸���܂��B���͂̓G�ŃR���{���q���܂��傤�B",
};


//�Z���N�g�V�[��
class SceneSelect :public SceneBase {
private:
	
	Cursor cursor;

	int selectIndex;

	int BackGroundHandle;
	int BackGroundPos[2];

	int stageBoxHandle[STAGE_NUM];
	VECTOR stageBoxPos[STAGE_NUM];
	VECTOR stageBoxSize[STAGE_NUM];
	float stageBoxScale[STAGE_NUM];

	int stageScreenHandle[STAGE_NUM];
	VECTOR stageScreenPos;
	VECTOR stageScreenSize;
	
public:
	
	void Init();
	void Step();
	void Draw();
	void Delete();
};
