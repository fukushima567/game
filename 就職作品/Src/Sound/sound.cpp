#include "sound.h"


char Sound::SoundName[SOUND_NUM][256] = {
	"data/Sound/SE/ボタン選択.mp3",
	"data/Sound/SE/ボタン押す.mp3",
	"data/Sound/BGM/title.wav",
	"data/Sound/BGM/select.wav",
	"data/Sound/BGM/play_1.wav",
	"data/Sound/BGM/play_2.wav",
	"data/Sound/BGM/play_3.wav",
	"data/Sound/BGM/victory.wav",
	"data/Sound/SE/足音1.wav",
	"data/Sound/SE/足音2.wav",
	"data/Sound/SE/プレイヤー減速.wav",
	"data/Sound/SE/回避.mp3",
	"data/Sound/SE/攻撃.mp3",
	"data/Sound/SE/通常攻撃命中.mp3",
	"data/Sound/SE/ダッシュ攻撃命中.mp3",
	"data/Sound/SE/被弾.mp3",
	"data/Sound/BGM/gameover.wav"
};

int Sound::handle[SOUND_NUM];


//サウンド初期化
void Sound::Init() {

	for (int index = 0; index < SOUND_NUM; index++) {
		handle[index] = -1; 
	}

}

//全シーン共通のサウンドロード
void Sound::LoadCommonSound() {

	for (int index = 0; index < C_SOUND_NUM; index++) {

		handle[index]= LoadSoundMem(SoundName[index]);

	}

}

//指定シーンのサウンドロード
void Sound::LoadSound(int scene) {

	int index=0;
	int max=0;

	//シーンによって読み込むサウンドを変える
	switch (scene) {
	case TITLE:

		index = C_SOUND_NUM;
		max = T_SOUND_NUM;
		break;

	case SELECT:

		index = T_SOUND_NUM;
		max = S_SOUND_NUM;
		break;

	case PLAY:

		index = S_SOUND_NUM;
		max = P_SOUND_NUM;
		break;

	case OVER:

		index = P_SOUND_NUM;
		max = SOUND_NUM;
		break;
	}

	for (index; index < max; index++) {

		handle[index] = LoadSoundMem(SoundName[index]);
	}
}

//サウンドの破棄
void Sound::Delete(bool all) {
	int index;

	if (all) {
		index = 0;
	}
	else {
		index = C_SOUND_NUM;
	}

	for (index; index < SOUND_NUM; index++) {
		if (handle[index] == -1) { continue; }
		DeleteSoundMem(handle[index]);
		handle[index] = -1;
	}
}

//再生中かどうか
bool Sound::IsPlay(SOUND_ID ID) {

	return CheckSoundMem(handle[ID]);
}

//音量を調節する
void Sound::SetVolume(SOUND_ID ID, int vol) {

	ChangeVolumeSoundMem(255 * vol / 100, handle[ID]);
}

//サウンドを鳴らす
void Sound::Play(SOUND_ID ID, bool loop, bool restart) {

	if (loop) {
		if (IsPlay(ID)) {
			Stop(ID);
		}
		PlaySoundMem(handle[ID], DX_PLAYTYPE_LOOP, true);
	}
	else {
		if (IsPlay(ID)) {
			Stop(ID);
		}
		PlaySoundMem(handle[ID], DX_PLAYTYPE_BACK, true);
	}
}

//サウンドを止める
void Sound::Stop(SOUND_ID ID){

	StopSoundMem(handle[ID]);
}

//すべてのサウンドを止める
void Sound::StopAll() {

	for (int index = 0; index < SOUND_NUM; index++) {

		if (handle[index] == -1) { continue; }
		StopSoundMem(handle[index]);
	}
}
