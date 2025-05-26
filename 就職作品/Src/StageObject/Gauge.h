#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


//ステージごとの必要ゲージ量
constexpr int MAX_GAUGE[STAGE_NUM] = {
	150,
	600,
	1000,
	4000,
	1000
};


//ゲージクラス
class Gauge {
private:

	int maxGauge;
	int gauge;

public:

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//破棄
	void Delete();



	//ゲージ量を得る
	int GetGauge() { return gauge; }

	//最大のゲージ量を得る
	int GetMaxGauge() { return maxGauge; }

	//ゲージ量をセット
	void SetGauge(int num) {
		gauge = num;
	}

	//ゲージが有効か
	bool GetActive() {
		if (gauge < maxGauge) {
			return true;
		}
		return false;
	}
};