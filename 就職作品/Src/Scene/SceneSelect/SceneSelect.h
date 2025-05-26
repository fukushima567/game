#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../Cursor/cursor.h"


constexpr char STAGE_TEXT[STAGE_NUM][512]{
	"最初のステージです。\nダッシュ中の攻撃を当てるとコンボが発生します。\nコンボを繋ぎながら敵を倒すことで\n獲得スコアが増えます。\nスコアを一定まで上昇させるとクリアになります。",
	"クリア条件は同じです。\n遠距離攻撃をしてくる敵が登場します。\n回避を使い、攻撃を避けましょう。\n倒すことができればより多くスコアを獲得できます。\nコンボを繋げてクリアを目指しましょう。",
	"マグマに落ちるとダメージを受けます。\n落ちないように気をつける必要があります。\n新しい敵が登場します。\nターゲット切り替えや回避を使い、\n落下や敵の攻撃を避けて攻撃を当てましょう。",
	"新しい敵が登場します。\n体力が多く、倒すのが大変な分、\n獲得スコアも多くなっています。",
	"最後のステージです。\nボスが登場します。\nボスは攻撃した際、現在のコンボ数に応じてスコアが\n上昇します。周囲の敵でコンボを繋ぎましょう。",
};


//セレクトシーン
class SceneSelect :public SceneBase {
private:
	
	Cursor cursor;

	int selectIndex;

	int BackGroundHandle;
	int BackGroundPos[2];

	int stageBoxHandle[STAGE_NUM];
	VECTOR stageBoxPos[STAGE_NUM];
	VECTOR stageBoxSize[STAGE_NUM];
	float stageBoxScale[STAGE_NUM];

	int stageScreenHandle[STAGE_NUM];
	VECTOR stageScreenPos;
	VECTOR stageScreenSize;
	
public:
	
	void Init();
	void Step();
	void Draw();
	void Delete();
};
