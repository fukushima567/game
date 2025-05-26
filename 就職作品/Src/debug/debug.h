#pragma once
#include "DxLib.h"
#include "vector"
#include "list"
#include <string>

using namespace std;

constexpr bool isDebug = true;						//デバック文字表示フラグ

constexpr int MAX_LIST_SIZE = 30;					//リストの最大数
constexpr int MAX_TEXT_SIZE = 512;					//最大文字数


//デバック文字構造体
struct TextInfo {

	int x;				//x座標
	int y;				//y座標
	string debugText;	//テキスト
	unsigned int color;	//テキストカラー
	bool isUse;			//使用フラグ
};


//デバック文字クラス
class DebugString {
private:
	DebugString();
	~DebugString();

	static DebugString* instance;

public:

	//インスタンス作成
	static void Create();

	//破棄
	static void Destroy();

	//インスタンス取得
	static DebugString* GetInstance();

	//デバック文字を追加
	void AddText(int x, int y, string text);

	//フォーマットつきテキスト追加
	void AddFormatText(int x, int y, const char* f_text, ...);

	//ログに出力
	void DrawLogString(string text);

	//ログにフォーマット出力
	void DrawLogFormatString(const char* f_text,...);

	//描画
	void Draw();

private:

	//テキスト構造体
	list<TextInfo> TextInfoList;

	//テキスト情報の追加
	void addTextInfo(TextInfo text_info);

};