#pragma once
#include "DxLib.h"
#include "../Common.h"
#include "../GameData/gameData.h"


//サウンドID
enum SOUND_ID {

	//全シーン共通のサウンド
	C_SE_SELECT,
	C_SE_DECIDE,
	C_SOUND_NUM,

	//タイトルのサウンド
	T_BGM = C_SOUND_NUM,
	T_SOUND_NUM,

	//セレクトのサウンド
	S_BGM= T_SOUND_NUM,
	S_SOUND_NUM,

	//プレイシーンサウンド
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

	//サウンドの合計数
	SOUND_NUM

};


//サウンドクラス
class Sound {
public:

	
	//サウンド名
	static char SoundName[SOUND_NUM][256];

protected:

	//サウンドハンドル
	static int handle[SOUND_NUM];

public:

	//サウンド初期化
	static void Init();

	//全シーン共通のサウンドロード
	static void LoadCommonSound();

	//指定シーンのサウンドロード
	static void LoadSound(int ID);

	//サウンドの破棄
	static void Delete(bool all=false);

	//再生中かどうか
	static bool IsPlay(SOUND_ID ID);

	//音量を調節する
	static void SetVolume(SOUND_ID ID, int vol);

	//サウンドを鳴らす
	static void Play(SOUND_ID ID, bool loop,bool restart = true);

	//サウンドを止める
	static void Stop(SOUND_ID ID);

	//すべてのサウンドを止める
	static void StopAll();

	
	
};