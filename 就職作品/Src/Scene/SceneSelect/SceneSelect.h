#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


//ステージごとの表示されるテキスト
constexpr char STAGE_TEXT[STAGE_NUM][512]{
	" 最初のステージです。\n ダッシュ中の攻撃を当てるとコンボが発生します。\n コンボを繋ぎながら敵を倒すことで\n 獲得スコアが増えます。\n スコアを一定まで上昇させるとクリアになります。",
	" クリア条件は同じです。\n 遠距離攻撃をしてくる敵が登場します。\n 回避を使い、攻撃を避けましょう。\n 倒すことができればより多くスコアを獲得できます。\n コンボを繋げてクリアを目指しましょう。",
	" マグマに落ちるとダメージを受けます。\n 落ちないように気をつける必要があります。\n 新しい敵が登場します。\n ターゲット切り替えや回避を使い、\n 落下や敵の攻撃を避けて攻撃を当てましょう。",
	" 新しい敵が登場します。\n 体力が多く、倒すのが大変な分、\n 獲得スコアも多くなっています。",
	" 最後のステージです。\n ボスが登場します。\n ボスは攻撃した際、現在のコンボ数に応じてスコア\n が上昇します。周囲の敵でコンボを繋ぎましょう。",
};


//セレクトシーン
class SceneSelect :public SceneBase {
private:
	
	Cursor cursor;

	int selectIndex;

	//背景関係
	int backGroundHandle[2];
	int backGroundPos[2];

	//ステージ選択UI
	int stageBoxHandle[STAGE_NUM];
	VECTOR stageBoxPos[STAGE_NUM];
	VECTOR stageBoxSize[STAGE_NUM];
	float stageBoxScale[STAGE_NUM];

	//ステージ画像
	int stageScreenHandle[STAGE_NUM];
	VECTOR stageScreenPos;
	VECTOR stageScreenSize;
	
	
public:
	
	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//破棄処理
	void Delete();
};
