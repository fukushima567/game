#pragma once
#include "DxLib.h"
#include "../Common.h"
#include "../GameData/gameData.h"


//�T�E���hID
enum SOUND_ID {

	//�S�V�[�����ʂ̃T�E���h
	C_SE_SELECT,
	C_SE_DECIDE,
	C_SOUND_NUM,

	//�^�C�g���̃T�E���h
	T_BGM = C_SOUND_NUM,
	T_SOUND_NUM,

	//�Z���N�g�̃T�E���h
	S_BGM= T_SOUND_NUM,
	S_SOUND_NUM,

	//�v���C�V�[���T�E���h
	P_BGM_1 = S_SOUND_NUM,
	P_BGM_2,
	P_BGM_3,
	P_BGM_VICTORY,
	P_SE_PLAYER_WALK,
	P_SE_PLAYER_DASH,
	P_SE_PLAYER_DASH_FIN,
	P_SE_PLAYER_VOID,
	P_SE_PLAYER_ATTACK,
	P_SE_PLAYER_HIT_1,
	P_SE_PLAYER_HIT_2,
	P_SE_PLAYER_DAMAGE,
	P_SOUND_NUM,

	O_BGM= P_SOUND_NUM,

	//�T�E���h�̍��v��
	SOUND_NUM

};


//�T�E���h�N���X
class Sound {
public:

	
	//�T�E���h��
	static char SoundName[SOUND_NUM][256];

protected:

	//�T�E���h�n���h��
	static int handle[SOUND_NUM];

public:

	//�T�E���h������
	static void Init();

	//�S�V�[�����ʂ̃T�E���h���[�h
	static void LoadCommonSound();

	//�w��V�[���̃T�E���h���[�h
	static void LoadSound(int ID);

	//�T�E���h�̔j��
	static void Delete(bool all=false);

	//�Đ������ǂ���
	static bool IsPlay(SOUND_ID ID);

	//���ʂ𒲐߂���
	static void SetVolume(SOUND_ID ID, int vol);

	//�T�E���h��炷
	static void Play(SOUND_ID ID, bool loop,bool restart = true);

	//�T�E���h���~�߂�
	static void Stop(SOUND_ID ID);

	//���ׂẴT�E���h���~�߂�
	static void StopAll();

	
	
};