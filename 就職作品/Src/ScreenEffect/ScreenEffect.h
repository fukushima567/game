#include "../Common.h"


constexpr int SWORD_EFFECT_NUM = 9;
constexpr int DASH_EFFECT_NUM = 4;


//スクリーンエフェクトクラス
class ScreenEffect {
private:

	//剣のエフェクト関係
	int swordEffeHandle[SWORD_EFFECT_NUM];
	int swordEffeIndex;
	int swordEffeCount;
	bool swordEffeActive;

	//風のエフェクト関係
	int windCount;
	int dashWindHandle[DASH_EFFECT_NUM];
	int windHandleIndex;
	int screenHandle;
	int wind_alpha;
	int white_alpha;
	int fadeAlpha;

public:

	ScreenEffect();
	~ScreenEffect(){}

	//初期化
	void Init();

	//破棄
	void Delete();

	//ダッシュ時の画面演出
	void DashEffect(float speed, bool draw);

	//剣ヒット時の画面演出
	void SwordEffect(bool request);

	//ぼかし
	void GaussEffect();

	//画面揺れ
	void ShakeScreen();

	//フェードイン
	bool FadeIn(bool black=true);

	//フェードアウト
	bool FadeOut(bool black = true);
};