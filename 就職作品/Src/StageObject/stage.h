#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


//ステージのパス
constexpr char STAGE_PATH[STAGE_NUM][256] = {
	"data/Image/Play/stage/stage0.mv1",
	"data/Image/Play/stage/stage1.mv1",
	"data/Image/Play/stage/stage2.mv1",
	"data/Image/Play/stage/stage3.mv1",
	"data/Image/Play/stage/stage4.mv1",
};


//スカイドームのサイズ
constexpr VECTOR SKY_DOME_SIZE[STAGE_NUM] = {
	1.5f,1.5f,1.5f,
	1.5f,1.5f,1.5f,
	1.0f,1.0f,1.0f,
	1.2f,1.2f,1.2f,
	1.0f,1.0f,1.0f
};


//ステージクラス
class Stage{
private:

	int skyHandle;		//スカイドームのハンドル
	VECTOR skyPos;		//スカイドームの座標

	int stageHandle;	//ステージのハンドル
	
public:

	Stage();
	~Stage(){};

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄
	void Delete();

	//ステージ情報を得る
	int GetStageHandle() {return stageHandle;}

	//スカイドームの座標をセット
	void SetPos(VECTOR pos) { skyPos = pos; }
};