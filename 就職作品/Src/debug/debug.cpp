#include "debug.h"
#include <cstdarg>
#include <cstdio>
#include <windows.h>


//インスタンス初期化
DebugString* DebugString::instance = nullptr;


//コンストラクタ
DebugString::DebugString() {
	TextInfoList.resize(MAX_LIST_SIZE);
	for (TextInfo& value : TextInfoList) {
		value.isUse = false;
	}
}


//デストラクタ
DebugString::~DebugString() {

}


//インスタンス作成
void DebugString::Create() {
	if (instance == nullptr) {
		instance = new DebugString();
	}
}


//破棄
void DebugString::Destroy() {
	delete instance;
	instance = nullptr;
}


//インスタンス取得
DebugString* DebugString::GetInstance() {

	if (instance == nullptr) {
		Create();
	}
	return instance;
}


//テキスト追加
void DebugString::AddText(int x, int y, string text){
	TextInfo val = { x,y,text,GetColor(255, 255, 255),true};
	addTextInfo(val);
}


//フォーマットつきテキスト追加
void DebugString::AddFormatText(int x, int y, const char* f_text, ...){
	
	char buffer[MAX_TEXT_SIZE];

	va_list args;
	va_start(args, f_text);
	vsnprintf(buffer, sizeof(buffer), f_text, args);
	va_end(args);

	TextInfo val = { x,y,buffer,GetColor(255, 255, 0),true };
	addTextInfo(val);
}


//テキスト情報の追加
void DebugString::addTextInfo(TextInfo text_info) {

	for (TextInfo& value : TextInfoList) {

		if (!value.isUse) {

			value = text_info;
			return;
		}
	}
}


//ログに出力
void DebugString::DrawLogString(string text) {

	if (!isDebug) { return; }

	text += "\n";
	OutputDebugString(text.c_str());
}


//ログにフォーマット出力
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


//デバック文字描画
void DebugString::Draw() {
	
	if (!isDebug) { return; }

	for (TextInfo& value : TextInfoList) {

		if (value.isUse) {
			DrawString(value.x, value.y, value.debugText.c_str(), value.color);
			value.isUse = false;
		}
	}
}