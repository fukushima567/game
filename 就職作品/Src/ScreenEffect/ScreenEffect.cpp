#include "ScreenEffect.h"


//コンストラクタ
ScreenEffect::ScreenEffect() {

	memset(&swordEffeHandle, 0, sizeof(int[SWORD_EFFECT_NUM]));
	swordEffeIndex = 0;
	swordEffeCount = 0;
	swordEffeActive = false;

	windCount = 0;
	memset(&dashWindHandle, 0, sizeof(int[DASH_EFFECT_NUM]));
	windHandleIndex = 0;
	screenHandle = 0;
	wind_alpha = 0;
	white_alpha = 0;
	fadeAlpha = 0;
}


//初期化
void ScreenEffect::Init() {

	dashWindHandle[0] = LoadGraph("data/image/play/ScreenEffect/dashWind01.png");
	dashWindHandle[1] = LoadGraph("data/image/play/ScreenEffect/dashWind02.png");
	dashWindHandle[2] = LoadGraph("data/image/play/ScreenEffect/dashWind03.png");
	dashWindHandle[3] = LoadGraph("data/image/play/ScreenEffect/dashWind04.png");
	screenHandle = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	LoadDivGraph("data/effect/sword.png", SWORD_EFFECT_NUM, SWORD_EFFECT_NUM,1,224,224, swordEffeHandle);
	fadeAlpha = -1;
}


//ダッシュ時の画面演出
void ScreenEffect::DashEffect(float speed,bool draw){
	
	if (!draw) { return; }

	//速度が一定以上なら描画(速度で描画の強さが変わる)
	if (speed>2.5f) {
		wind_alpha = (int)speed * 12;
		white_alpha = (int)speed * 3;
	}
	else {

		if (wind_alpha) {
			wind_alpha--;
		}
		if (white_alpha) {
			white_alpha--;
		}
	}

	//3fごとに画像切り替え
	windCount++;
	if (windCount > 3) {
		windHandleIndex++;
		windCount = 0;
	}

	if (wind_alpha && white_alpha) {

		//画面のぼかし
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		GetDrawScreenGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, screenHandle);
		DrawGraph((int)(speed / 3.0f), 0, screenHandle, true);
		DrawGraph((int)(-speed / 3.0f), 0, screenHandle, true);

		//風切りエフェクト
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, wind_alpha);
		DrawGraph(0, 0, dashWindHandle[windHandleIndex % 3], true);

		//画面を白く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, white_alpha);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	}
}


//剣ヒット時の画面演出
void ScreenEffect::SwordEffect(bool request) {
	
	if (request && !swordEffeActive) {
		swordEffeActive = true;
		swordEffeIndex = 0;
		swordEffeCount = 0;
	}

	if (swordEffeActive) {

		int alpha = 0;
		if (swordEffeIndex==1|| swordEffeIndex==8) {
			alpha = 10;
		}
		if (swordEffeIndex == 2 || swordEffeIndex == 7) {
			alpha = 20;
		}
		if (swordEffeIndex == 3 || swordEffeIndex == 6) {
			alpha = 40;
		}
		if (swordEffeIndex == 4 || swordEffeIndex == 5) {
			alpha = 80;
		}

		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, 0, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 50, 8.0, 4.6, swordEffeHandle[swordEffeIndex], true);
	
		swordEffeCount++;
		if (swordEffeIndex == 5) {
			if (swordEffeCount > 2) {
				swordEffeCount = 0;
				swordEffeIndex++;
			}
		}
		else {
			if (swordEffeCount > 1) {
				swordEffeCount = 0;
				swordEffeIndex++;
			}
		}
		if (swordEffeIndex == 9) {
			swordEffeActive = false;
			swordEffeIndex = 0;
			swordEffeCount = 0;
		}
	}
}


//画面揺れ
void ScreenEffect::ShakeScreen() {

	GetDrawScreenGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, screenHandle);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, true);
	DrawGraph((int)((GetRand(10)-5)*1.5),(int)((GetRand(10)-5)*1.5), screenHandle, true);
}


//暗めぼかし
void ScreenEffect::GaussEffect() {

	GetDrawScreenGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, screenHandle);
	GraphFilter(screenHandle, DX_GRAPH_FILTER_GAUSS,8, 100);
	DrawGraph(0, 0, screenHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);
}


//フェードイン
bool ScreenEffect::FadeIn(bool black) {

	if (fadeAlpha == -1) {
		fadeAlpha = 255;
	}
	if (fadeAlpha > 0) {
		fadeAlpha -= 7;
	}
	if (fadeAlpha < 0) {
		fadeAlpha = 0;
	}

	int color;
	if (black) {
		color = GetColor(0, 0, 0);
	}
	else {
		color = GetColor(255, 255, 255);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);
	

	if (fadeAlpha <= 0) {
		return true;
	}
	return false;
}


//フェードアウト
bool ScreenEffect::FadeOut(bool black) {

	if (fadeAlpha == -1) {
		fadeAlpha = 0;
	}
	if (fadeAlpha <= 255) {
		fadeAlpha += 7;
	}
	if (fadeAlpha > 255) {
		fadeAlpha = 255;
	}

	int color;
	if (black) {
		color=GetColor(0, 0, 0);
	}
	else {
		color=GetColor(255, 255, 255);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);
	

	if (fadeAlpha >= 255) {
		return true;
	}
	return false;
}


//破棄
void ScreenEffect::Delete() {

	for (int index = 0; index < SWORD_EFFECT_NUM; index++) {
		DeleteGraph(swordEffeHandle[index]);
	}

	for (int index = 0; index < DASH_EFFECT_NUM; index++) {
		DeleteGraph(dashWindHandle[index]);
	}
}