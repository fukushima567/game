#include "sound.h"


char Sound::SoundName[SOUND_NUM][256] = {
	"data/Sound/SE/�{�^���I��.mp3",
	"data/Sound/SE/�{�^������.mp3",
	"data/Sound/BGM/title.wav",
	"data/Sound/BGM/select.wav",
	"data/Sound/BGM/play_1.wav",
	"data/Sound/BGM/play_2.wav",
	"data/Sound/BGM/play_3.wav",
	"data/Sound/BGM/victory.wav",
	"data/Sound/SE/����1.wav",
	"data/Sound/SE/����2.wav",
	"data/Sound/SE/�v���C���[����.wav",
	"data/Sound/SE/���.mp3",
	"data/Sound/SE/�U��.mp3",
	"data/Sound/SE/�ʏ�U������.mp3",
	"data/Sound/SE/�_�b�V���U������.mp3",
	"data/Sound/SE/��e.mp3",
	"data/Sound/BGM/gameover.wav"
};

int Sound::handle[SOUND_NUM];


//�T�E���h������
void Sound::Init() {

	for (int index = 0; index < SOUND_NUM; index++) {
		handle[index] = -1; 
	}

}

//�S�V�[�����ʂ̃T�E���h���[�h
void Sound::LoadCommonSound() {

	for (int index = 0; index < C_SOUND_NUM; index++) {

		handle[index]= LoadSoundMem(SoundName[index]);

	}

}

//�w��V�[���̃T�E���h���[�h
void Sound::LoadSound(int scene) {

	int index=0;
	int max=0;

	//�V�[���ɂ���ēǂݍ��ރT�E���h��ς���
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

//�T�E���h�̔j��
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

//�Đ������ǂ���
bool Sound::IsPlay(SOUND_ID ID) {

	return CheckSoundMem(handle[ID]);
}

//���ʂ𒲐߂���
void Sound::SetVolume(SOUND_ID ID, int vol) {

	ChangeVolumeSoundMem(255 * vol / 100, handle[ID]);
}

//�T�E���h��炷
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

//�T�E���h���~�߂�
void Sound::Stop(SOUND_ID ID){

	StopSoundMem(handle[ID]);
}

//���ׂẴT�E���h���~�߂�
void Sound::StopAll() {

	for (int index = 0; index < SOUND_NUM; index++) {

		if (handle[index] == -1) { continue; }
		StopSoundMem(handle[index]);
	}
}
