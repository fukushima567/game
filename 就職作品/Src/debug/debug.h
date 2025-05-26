#pragma once
#include "DxLib.h"
#include "vector"
#include "list"
#include <string>

using namespace std;

constexpr bool isDebug = true;						//�f�o�b�N�����\���t���O

constexpr int MAX_LIST_SIZE = 30;					//���X�g�̍ő吔
constexpr int MAX_TEXT_SIZE = 512;					//�ő啶����


//�f�o�b�N�����\����
struct TextInfo {

	int x;				//x���W
	int y;				//y���W
	string debugText;	//�e�L�X�g
	unsigned int color;	//�e�L�X�g�J���[
	bool isUse;			//�g�p�t���O
};


//�f�o�b�N�����N���X
class DebugString {
private:
	DebugString();
	~DebugString();

	static DebugString* instance;

public:

	//�C���X�^���X�쐬
	static void Create();

	//�j��
	static void Destroy();

	//�C���X�^���X�擾
	static DebugString* GetInstance();

	//�f�o�b�N������ǉ�
	void AddText(int x, int y, string text);

	//�t�H�[�}�b�g���e�L�X�g�ǉ�
	void AddFormatText(int x, int y, const char* f_text, ...);

	//���O�ɏo��
	void DrawLogString(string text);

	//���O�Ƀt�H�[�}�b�g�o��
	void DrawLogFormatString(const char* f_text,...);

	//�`��
	void Draw();

private:

	//�e�L�X�g�\����
	list<TextInfo> TextInfoList;

	//�e�L�X�g���̒ǉ�
	void addTextInfo(TextInfo text_info);

};