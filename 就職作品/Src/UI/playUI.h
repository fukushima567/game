#pragma once
#include "../Player/player.h"
#include "../StageObject/Gauge.h"
#include "../Enemy/EnemyManager.h"
#include "../../Cursor/cursor.h"


//UI�̎��
enum UI_TYPE {
	UI_PLAYER_STATUS_BASE,				//�v���C���[�̃X�e�[�^�X�o�[�̉�
	UI_PLAYER_STATUS_HP,				//�v���C���[��HP�o�[
	UI_PLAYER_STATUS_STAMINA,			//�v���C���[�̃X�^�~�i�o�[
	UI_PLAYER_STATUS_FRAME,				//�v���C���[�̃X�e�[�^�X�o�[�̘g
	UI_PLAYER_ICON_HP,					//�v���C���[HP�̃A�C�R��
	UI_PLAYER_ICON_STAMINA,				//�v���C���[�X�^�~�i�̃A�C�R��
	UI_PLAYER_ACTION_DASH,				//�v���C���[�_�b�V��UI
	UI_PLAYER_ACTION_NORMAL_ATTACK,		//�v���C���[�ʏ�U��UI
	UI_PLAYER_ACTION_DASH_ATTACK,		//�v���C���[�_�b�V���U��UI
	UI_PLAYER_SPECIAL_LV_0,				//�v���C���[�K�E�Z���܂��Ă��Ȃ�UI
	UI_PLAYER_SPECIAL_LV_1,				//�v���C���[�K�E�ZLV1��UI
	UI_PLAYER_SPECIAL_LV_2,				//�v���C���[�K�E�ZLV2��UI
	UI_PLAYER_SPECIAL_LV_3,				//�v���C���[�K�E�ZLV3��UI
	UI_PLAYER_SPECIAL_GAUGE,			//�v���C���[�K�E�Z�Q�[�W��UI
	UI_LOCK_ON_1,						//��_�b�V�����̃��b�N�I��
	UI_LOCK_ON_2,						//�_�b�V�����̃��b�N�I��
	UI_ENEMY_HP_BOX_BACK,				//�GHP�̉�
	UI_ENEMY_HP_BOX,					//�G��HP�g
	UI_ENEMY_HP,						//�G��HP
	UI_ENEMY_ICON_0,					//�G�̃A�C�R���X�e�[�W�O
	UI_ENEMY_ICON_1,					//�G�̃A�C�R���X�e�[�W�P
	UI_ENEMY_ICON_2,					//�G�̃A�C�R���X�e�[�W�Q
	UI_ENEMY_ICON_3,					//�G�̃A�C�R���X�e�[�W�R
	UI_ENEMY_ICON_4,					//�G�̃A�C�R���X�e�[�W�S

	UI_NUM								//UI����
};


//UI�摜�̃p�X
constexpr char UI_IMAGE_PATH[UI_NUM][128] = {
	"Data/Image/Play/UI/stateBox.png",
	"Data/Image/Play/UI/HP.png",
	"Data/Image/Play/UI/stamina.png",
	"Data/Image/Play/UI/stateBox2.png",
	"Data/Image/Play/UI/hp_icon.png",
	"Data/Image/Play/UI/stamina_icon.png",
	"Data/Image/Play/UI/run.png",
	"Data/Image/Play/UI/attack.png",
	"Data/Image/Play/UI/s_attack.png",
	"Data/Image/Play/UI/sp0.png",
	"Data/Image/Play/UI/sp1.png",
	"Data/Image/Play/UI/sp2.png",
	"Data/Image/Play/UI/sp3.png",
	"Data/Image/Play/UI/spGauge.png",
	"Data/Image/Play/UI/lock.png",
	"Data/Image/Play/UI/lock2.png",
	"Data/Image/Play/UI/enemyBoxBack.png",
	"Data/Image/Play/UI/enemyHPBox.png",
	"Data/Image/Play/UI/enemyHP.png",
	"Data/Image/Play/UI/enemyIcon.png",
};


//�|�[�Y��UI�̎��
enum PAUSE_UI_TYPE {
	PAUSE_UI_CHAR,				//�|�[�Y���̉�ʕ���
	PAUSE_UI_CONTINUE,			//�|�[�YUI������
	PAUSE_UI_BACK,				//�|�[�YUI�߂�
	PAUSE_UI_TUTORIAL_1,		//�����摜1
	PAUSE_UI_TUTORIAL_2,		//�����摜2
	PAUSE_UI_TUTORIAL_3,		//�����摜3
	PAUSE_UI_TUTORIAL_4,		//�����摜4
	PAUSE_UI_TUTORIAL_5,		//�����摜5
	PAUSE_UI_TUTORIAL_6,		//�����摜6
	PAUSE_UI_TUTORIAL_BACK,		//�����摜�߂�
	PAUSE_UI_TUTORIAL_NEXT,		//�����摜����

	PAUSE_UI_NUM				//�|�[�Y��UI����
};


//�|�[�Y��UI�摜�̃p�X
constexpr char PAUSE_UI_IMAGE_PATH[4][128] = {
	"Data/Image/Play/UI/pause.png",			//�|�[�Y���̉��
	"Data/Image/Play/UI/pauseUI.png",		//�|�[�Y���̉�ʕ���
	"Data/Image/Play/UI/tutorial.png",		//�����摜1
	"Data/Image/Play/UI/tutorialUI.png"		//�����摜����
};


//UI���W�\����
struct UI_POS_INFO {
	int x;		//x���W
	int y;		//y���W
};


//�v���C���[�̃X�e�[�^�X�֌W
constexpr UI_POS_INFO PLAYER_STATUS_POS = { 65,900 };					//�v���C���[�X�e�[�^�XUI���W
constexpr UI_POS_INFO PLAYER_ICON_HP_POS = { 0,915 };					//�v���C���[HP�A�C�R�����W
constexpr UI_POS_INFO PLAYER_ICON_STAMINA_POS = { 0,995 };				//�v���C���[�X�^�~�i�A�C�R�����W	
constexpr int		  PLAYER_STATUS_HP_WIDTH = 6;						//HP�X�e�[�^�X����
constexpr int		  PLAYER_STATUS_STAMINA_WIDTH = 10;					//�X�^�~�i�X�e�[�^�X����
constexpr int		  PLAYER_STATUS_HEIGHT = 150;						//�X�e�[�^�X�o�[����


//�v���C���[�Z�֌W
constexpr UI_POS_INFO PLAYER_SP_GAUGE_POS = { SCREEN_SIZE_X / 2,950 };	//�v���C���[�K�E�Z�Q�[�W���W
constexpr UI_POS_INFO PLAYER_ACTION_DASH_POS = { 1770,750 };			//�v���C���[�_�b�V��UI
constexpr UI_POS_INFO PLAYER_ACTION_ATTACK_POS = { 1700, 870 };			//�v���C���[�U��UI
constexpr UI_POS_INFO PLAYER_ACTION_SP_POS = { 1600, 800 };				//�v���C���[�K�E�Z
constexpr UI_POS_INFO KEY_DASH_POS = { 1800 ,850 };						//�_�b�V���̃L�[���W
constexpr UI_POS_INFO KEY_ATTACK_POS = { 1730, 970 };					//�U���̃L�[���W
constexpr UI_POS_INFO KEY_SP_POS = { 1580, 900 };						//�K�E�Z�̃L�[���W
constexpr UI_POS_INFO KEY_AVOID_LEFT_POS = { 736, 550 };				//������̃L�[���W
constexpr UI_POS_INFO KEY_AVOID_RIGHT_POS = { 1136, 550 };				//�E����̃L�[���W
constexpr UI_POS_INFO KEY_AVOID_BACK_POS = { 936, 800 };				//������̃L�[���W
constexpr UI_POS_INFO COMBO_POS = { 350, 400 };							//�R���{�̍��W
constexpr UI_POS_INFO COMBO_BONUS_POS = { 430,465 };					//�R���{�{�[�i�X���W
constexpr UI_POS_INFO COMBO_GAUGE_POS = { 330,500 };					//�R���{�Q�[�W���W


//�G�Q�[�W�֌W
constexpr UI_POS_INFO ENEMY_GAUGE_BOX_POS_1 = { 1260,0 };				//�G�Q�[�W����`������W
constexpr UI_POS_INFO ENEMY_GAUGE_BOX_POS_2 = { 1920,120 };				//�G�Q�[�W����`�E�����W
constexpr UI_POS_INFO ENEMY_ICON_POS{ 1270,13 };						//�G�A�C�R�����W
constexpr UI_POS_INFO ENEMY_GAUGE_POS_1 = { 1350,10 };					//�G�Q�[�W������W
constexpr UI_POS_INFO ENEMY_GAUGE_POS_2 = { 1910,110 };					//�G�Q�[�W�E�����W
constexpr float		  ENEMY_GAUGE_WIDTH = 560.0f;						//�G�Q�[�W�̕�				
constexpr UI_POS_INFO ENEMY_GAUGE_TEXT_POS = { 1650,35 };				//�G�Q�[�W�e�L�X�g�`����W
constexpr int		  ENEMT_GAUGE_DRAW_TIME = 50;						//�G�Q�[�W�����ʕ`�掞��



//�|�[�Y��ʊ֌W
constexpr UI_POS_INFO PAUSE_POS_1 = { 300 ,500 };						//�|�[�Y���W�P
constexpr UI_POS_INFO PAUSE_POS_2 = { 300 ,800 };						//�|�[�Y���W�Q
constexpr float		  PAUSE_UI_SIZE_NUM = 0.06f;						//�|�[�YUI�T�C�Y�ω���
constexpr float		  PAUSE_UI_MAX_SIZE = 1.5f;							//�|�[�YUI�ő�T�C�Y


//�_���[�W�֌W
constexpr int MAX_DAMAGE_TEXT = 10;		//�����ɕ\���ł���_���[�W�e�L�X�g�̍ő吔
constexpr int DRAW_TIME = 30;			//�_���[�W�e�L�X�g���`�悳��鎞��



//�v���C�V�[����UI
class PlayUI {
private:

	Cursor cursor;				//�J�[�\��

	//�t�H���g
	int damageTextHandle;		//�_���[�W�e�L�X�g�̃t�H���g
	int comboTextHandle;		//�R���{�̃t�H���g
	int comboBonusTextHandle;	//�R���{�̃{�[�i�X�t�H���g
	int GaugeTextHandle;		//�Q�[�W�����̃t�H���g

	//�|�[�Y��ʊ֌W
	int pauseHandle[PAUSE_UI_NUM];		//�|�[�Y��ʂ̉摜
	UI_POS_INFO pos[2];					//�|�[�Y��ʉ摜���W
	float size[2];						//�|�[�Y��ʉ摜�T�C�Y
	bool select[2];						//�I�����ꂽ�t���O
	int page;							//�\������Ă�������̃y�[�W

	//�v���C�V�[��UI
	int	playUIHandle[UI_NUM];			//�v���C�V�[����UI�摜
	VECTOR lockPos;						//���b�N�I�����W
	
	//�_���[�W�֌W
	bool damageFlag[MAX_DAMAGE_TEXT];	//�_���[�W��\������t���O
	VECTOR damagePos[MAX_DAMAGE_TEXT];	//�_���[�W��\��������W
	int damageNum[MAX_DAMAGE_TEXT];		//�_���[�W��
	int drawTimeCount[MAX_DAMAGE_TEXT];	//�`�悳�ꂽ����
	int enemyIndex[MAX_DAMAGE_TEXT];	//�G�̓Y����

	//�Q�[�W�֌W
	bool subGaugeFlag;					//�Q�[�W�����\���t���O
	int subGaugeNum;					//�Q�[�W������
	int subGaugeDrawTime;				//�Q�[�W�����ʂ��`�悳�ꂽ����

	//���ۑ��p
	Player playerUI;					//�v���C���[���ۑ��p
	Gauge gaugeUI;						//�|�C���g���ۑ��p
	EnemyManager enemyManagerUI;		//�G���ۑ��p
	
public:

	PlayUI();
	~PlayUI(){}

	//����������
	void Init();

	//�ʏ폈��
	void Step(Player player, EnemyManager enemyManager, Gauge gauge);

	//�|�[�Y���̒ʏ폈��
	int StepPause();

	//�`�揈��
	void Draw();

	//�|�[�Y��ʕ`�揈��
	void DrawPause();

	//�j��
	void Delete();

private:

	//�_���[�W�̃e�L�X�g����
	void DamageText();

	//�Q�[�W�����̃e�L�X�g����
	void GaugeText();

	//���b�N�I��UI����
	void Lock();
};