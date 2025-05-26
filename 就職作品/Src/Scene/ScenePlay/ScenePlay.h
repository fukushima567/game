#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../StageObject/stage.h"
#include "../../Enemy/enemyManager.h"
#include "../../Collision/SceneCollision.h"
#include "../../UI/playUI.h"


//�v���C�V�[���̏��
enum SCENE_PLAY_STATE {
	SCENE_PLAY_START,		//�J�n��
	SCENE_PLAY_GAME,		//�Q�[����	
	SCENE_PLAY_CLEAR,		//�N���A��
	SCENE_PLAY_GAME_OVER,	//�Q�[���I�[�o�[��
	SCENE_PLAY_NUM
};


//�v���C�V�[���N���X
class ScenePlay :public SceneBase {
private:

	//�v���C�V�[���摜
	int startHandle[2];				//�J�n�O�摜
	int tutorialHandle[6];			//�`���[�g���A���摜
	int clearHandle[2];				//�N���A�摜
	
	//�`���[�g���A���֌W
	bool tutorial;					//�`���[�g���A���\���t���O
	int page;						//�`���[�g���A���̌��y�[�W��

	//�N���X
	Player player;					//�v���C���[
	CameraManager cameraManager;	//�J�����}�l�[�W���[
	Stage stage;					//�X�e�[�W
	Gauge gauge;					//�Q�[�W
	EnemyManager enemyManager;		//�G�}�l�[�W���[
	SceneCollision sceneCollision;	//�R���W����
	PlayUI ui;
	
	bool pause;						//�|�[�Y�t���O
	bool fade;						//�t�F�[�h�t���O
	int sceneState;					//�V�[���̏��
	int sceneStateCount;			//�V�[���J�ڃJ�E���g

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
