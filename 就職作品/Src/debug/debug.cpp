#include "debug.h"
#include <cstdarg>
#include <cstdio>
#include <windows.h>


//�C���X�^���X������
DebugString* DebugString::instance = nullptr;


//�R���X�g���N�^
DebugString::DebugString() {
	TextInfoList.resize(MAX_LIST_SIZE);
	for (TextInfo& value : TextInfoList) {
		value.isUse = false;
	}
}


//�f�X�g���N�^
DebugString::~DebugString() {

}


//�C���X�^���X�쐬
void DebugString::Create() {
	if (instance == nullptr) {
		instance = new DebugString();
	}
}


//�j��
void DebugString::Destroy() {
	delete instance;
	instance = nullptr;
}


//�C���X�^���X�擾
DebugString* DebugString::GetInstance() {

	if (instance == nullptr) {
		Create();
	}
	return instance;
}


//�e�L�X�g�ǉ�
void DebugString::AddText(int x, int y, string text){
	TextInfo val = { x,y,text,GetColor(255, 255, 255),true};
	addTextInfo(val);
}


//�t�H�[�}�b�g���e�L�X�g�ǉ�
void DebugString::AddFormatText(int x, int y, const char* f_text, ...){
	
	char buffer[MAX_TEXT_SIZE];

	va_list args;
	va_start(args, f_text);
	vsnprintf(buffer, sizeof(buffer), f_text, args);
	va_end(args);

	TextInfo val = { x,y,buffer,GetColor(255, 255, 0),true };
	addTextInfo(val);
}


//�e�L�X�g���̒ǉ�
void DebugString::addTextInfo(TextInfo text_info) {

	for (TextInfo& value : TextInfoList) {

		if (!value.isUse) {

			value = text_info;
			return;
		}
	}
}


//���O�ɏo��
void DebugString::DrawLogString(string text) {

	if (!isDebug) { return; }

	text += "\n";
	OutputDebugString(text.c_str());
}


//���O�Ƀt�H�[�}�b�g�o��
void DebugString::DrawLogFormatString(const char* f_text, ...) {

	if (!isDebug) { return; }

	char buffer[MAX_TEXT_SIZE];

	va_list args;
	va_start(args, f_text);
	vsnprintf(buffer, sizeof(buffer), f_text, args);
	va_end(args);

	string s = buffer;

	DrawLogString(buffer);
}


//�f�o�b�N�����`��
void DebugString::Draw() {
	
	if (!isDebug) { return; }

	for (TextInfo& value : TextInfoList) {

		if (value.isUse) {
			DrawString(value.x, value.y, value.debugText.c_str(), value.color);
			value.isUse = false;
		}
	}
}