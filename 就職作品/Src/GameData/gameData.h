#pragma once
#include "../Input/input.h"
#include "../Input/PadInput.h"
#include "../UI/KeyUI.h"
#include "../lib/effekseer.h"
#include "../Sound/sound.h"
#include "../debug/debug.h"


//�Q�[���̎���
constexpr int NORMAL_TIME = 1;	//�ʏ�̎���
constexpr int SLOW_TIME = 10;	//�X���E�̎���

//�f�t�H���g�̃t�H���g�F
constexpr int BASE_FONT_COLOR = 0;

//�d��
constexpr float GRAVITY = 4.0f;


//�V�[��
enum SCENE_ID {
	TITLE,		//�^�C�g��
	SELECT,		//�Z���N�g
	PLAY,		//�v���C
	OVER,		//�Q�[���I�[�o�[
	TEST,		//�e�X�g

	SCENE_NUM
};



//�X�e�[�W�̎��
enum STAGE_TYPE {
	STAGE_0,	//�`���[�g���A��
	STAGE_1,	//�X
	STAGE_2,	//�}�O�}
	STAGE_3,	//�s�s
	STAGE_4,	//�Ō�

	STAGE_NUM
};



//�Q�[���f�[�^�N���X
class GameData {
private:

	GameData();
	~GameData(){}

	static GameData* instance;	//�C���X�^���X

private:

	int gameTime;				//�Q�[������

	int fontHandle;				//�t�H���g�f�[�^

	SCENE_ID sceneID;			//�V�[��

	STAGE_TYPE stageType;		//�X�e�[�W

public:

	//�C���X�^���X�쐬
	static void Create();

	//�j��
	static void Destroy();

	//�C���X�^���X�擾
	static GameData* GetInstance();

	//�擾�֌W
	//�Q�[���̎��Ԃ��擾
	int GetGameTime() { return gameTime; }

	//�t�H���g�f�[�^���擾
	int GetFontHandle() { return fontHandle; }

	//���݂̃V�[�����擾
	SCENE_ID GetSceneID() { return sceneID; }

	//���݂̃X�e�[�W���擾
	STAGE_TYPE GetStageType() { return stageType; }

	//�Z�b�g�֌W
	//�Q�[���̎��Ԃ��Z�b�g
	void SetGameTime(int game_time) { gameTime = game_time; }

	//�Q�[���̎��Ԃ��Z�b�g
	void SetFontHandle(int font_handle) { fontHandle = font_handle; }

	//�V�[�����Z�b�g
	void SetSceneID(SCENE_ID scene_id) { sceneID = scene_id; }

	//�X�e�[�W���Z�b�g
	void SetStageType(STAGE_TYPE stage_type) { stageType = stage_type; }
};