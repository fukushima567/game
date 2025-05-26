#pragma once
#include "../Player/player.h"
#include "../StageObject/Gauge.h"
#include "../Enemy/EnemyManager.h"
#include "../../Cursor/cursor.h"


//UIの種類
enum UI_TYPE {
	UI_PLAYER_STATUS_BASE,				//プレイヤーのステータスバーの下
	UI_PLAYER_STATUS_HP,				//プレイヤーのHPバー
	UI_PLAYER_STATUS_STAMINA,			//プレイヤーのスタミナバー
	UI_PLAYER_STATUS_FRAME,				//プレイヤーのステータスバーの枠
	UI_PLAYER_ICON_HP,					//プレイヤーHPのアイコン
	UI_PLAYER_ICON_STAMINA,				//プレイヤースタミナのアイコン
	UI_PLAYER_ACTION_DASH,				//プレイヤーダッシュUI
	UI_PLAYER_ACTION_NORMAL_ATTACK,		//プレイヤー通常攻撃UI
	UI_PLAYER_ACTION_DASH_ATTACK,		//プレイヤーダッシュ攻撃UI
	UI_PLAYER_SPECIAL_LV_0,				//プレイヤー必殺技貯まっていないUI
	UI_PLAYER_SPECIAL_LV_1,				//プレイヤー必殺技LV1のUI
	UI_PLAYER_SPECIAL_LV_2,				//プレイヤー必殺技LV2のUI
	UI_PLAYER_SPECIAL_LV_3,				//プレイヤー必殺技LV3のUI
	UI_PLAYER_SPECIAL_GAUGE,			//プレイヤー必殺技ゲージのUI
	UI_LOCK_ON_1,						//非ダッシュ時のロックオン
	UI_LOCK_ON_2,						//ダッシュ時のロックオン
	UI_ENEMY_HP_BOX_BACK,				//敵HPの下
	UI_ENEMY_HP_BOX,					//敵のHP枠
	UI_ENEMY_HP,						//敵のHP
	UI_ENEMY_ICON_0,					//敵のアイコンステージ０
	UI_ENEMY_ICON_1,					//敵のアイコンステージ１
	UI_ENEMY_ICON_2,					//敵のアイコンステージ２
	UI_ENEMY_ICON_3,					//敵のアイコンステージ３
	UI_ENEMY_ICON_4,					//敵のアイコンステージ４

	UI_NUM								//UI総数
};


//UI画像のパス
constexpr char UI_IMAGE_PATH[UI_NUM][128] = {
	"Data/Image/Play/UI/stateBox.png",
	"Data/Image/Play/UI/HP.png",
	"Data/Image/Play/UI/stamina.png",
	"Data/Image/Play/UI/stateBox2.png",
	"Data/Image/Play/UI/hp_icon.png",
	"Data/Image/Play/UI/stamina_icon.png",
	"Data/Image/Play/UI/run.png",
	"Data/Image/Play/UI/attack.png",
	"Data/Image/Play/UI/s_attack.png",
	"Data/Image/Play/UI/sp0.png",
	"Data/Image/Play/UI/sp1.png",
	"Data/Image/Play/UI/sp2.png",
	"Data/Image/Play/UI/sp3.png",
	"Data/Image/Play/UI/spGauge.png",
	"Data/Image/Play/UI/lock.png",
	"Data/Image/Play/UI/lock2.png",
	"Data/Image/Play/UI/enemyBoxBack.png",
	"Data/Image/Play/UI/enemyHPBox.png",
	"Data/Image/Play/UI/enemyHP.png",
	"Data/Image/Play/UI/enemyIcon.png",
};


//ポーズ中UIの種類
enum PAUSE_UI_TYPE {
	PAUSE_UI_CHAR,				//ポーズ中の画面文字
	PAUSE_UI_CONTINUE,			//ポーズUI続ける
	PAUSE_UI_BACK,				//ポーズUI戻る
	PAUSE_UI_TUTORIAL_1,		//説明画像1
	PAUSE_UI_TUTORIAL_2,		//説明画像2
	PAUSE_UI_TUTORIAL_3,		//説明画像3
	PAUSE_UI_TUTORIAL_4,		//説明画像4
	PAUSE_UI_TUTORIAL_5,		//説明画像5
	PAUSE_UI_TUTORIAL_6,		//説明画像6
	PAUSE_UI_TUTORIAL_BACK,		//説明画像戻る
	PAUSE_UI_TUTORIAL_NEXT,		//説明画像次へ

	PAUSE_UI_NUM				//ポーズ中UI総数
};


//ポーズ中UI画像のパス
constexpr char PAUSE_UI_IMAGE_PATH[4][128] = {
	"Data/Image/Play/UI/pause.png",			//ポーズ中の画面
	"Data/Image/Play/UI/pauseUI.png",		//ポーズ中の画面文字
	"Data/Image/Play/UI/tutorial.png",		//説明画像1
	"Data/Image/Play/UI/tutorialUI.png"		//説明画像文字
};


//UI座標構造体
struct UI_POS_INFO {
	int x;		//x座標
	int y;		//y座標
};


//プレイヤーのステータス関係
constexpr UI_POS_INFO PLAYER_STATUS_POS = { 65,900 };					//プレイヤーステータスUI座標
constexpr UI_POS_INFO PLAYER_ICON_HP_POS = { 0,915 };					//プレイヤーHPアイコン座標
constexpr UI_POS_INFO PLAYER_ICON_STAMINA_POS = { 0,995 };				//プレイヤースタミナアイコン座標	
constexpr int		  PLAYER_STATUS_HP_WIDTH = 6;						//HPステータス長さ
constexpr int		  PLAYER_STATUS_STAMINA_WIDTH = 10;					//スタミナステータス長さ
constexpr int		  PLAYER_STATUS_HEIGHT = 150;						//ステータスバー太さ


//プレイヤー技関係
constexpr UI_POS_INFO PLAYER_SP_GAUGE_POS = { SCREEN_SIZE_X / 2,950 };	//プレイヤー必殺技ゲージ座標
constexpr UI_POS_INFO PLAYER_ACTION_DASH_POS = { 1770,750 };			//プレイヤーダッシュUI
constexpr UI_POS_INFO PLAYER_ACTION_ATTACK_POS = { 1700, 870 };			//プレイヤー攻撃UI
constexpr UI_POS_INFO PLAYER_ACTION_SP_POS = { 1600, 800 };				//プレイヤー必殺技
constexpr UI_POS_INFO KEY_DASH_POS = { 1800 ,850 };						//ダッシュのキー座標
constexpr UI_POS_INFO KEY_ATTACK_POS = { 1730, 970 };					//攻撃のキー座標
constexpr UI_POS_INFO KEY_SP_POS = { 1580, 900 };						//必殺技のキー座標
constexpr UI_POS_INFO KEY_AVOID_LEFT_POS = { 736, 550 };				//左回避のキー座標
constexpr UI_POS_INFO KEY_AVOID_RIGHT_POS = { 1136, 550 };				//右回避のキー座標
constexpr UI_POS_INFO KEY_AVOID_BACK_POS = { 936, 800 };				//後ろ回避のキー座標
constexpr UI_POS_INFO COMBO_POS = { 350, 400 };							//コンボの座標
constexpr UI_POS_INFO COMBO_BONUS_POS = { 430,465 };					//コンボボーナス座標
constexpr UI_POS_INFO COMBO_GAUGE_POS = { 330,500 };					//コンボゲージ座標


//敵ゲージ関係
constexpr UI_POS_INFO ENEMY_GAUGE_BOX_POS_1 = { 1260,0 };				//敵ゲージ下矩形左上座標
constexpr UI_POS_INFO ENEMY_GAUGE_BOX_POS_2 = { 1920,120 };				//敵ゲージ下矩形右下座標
constexpr UI_POS_INFO ENEMY_ICON_POS{ 1270,13 };						//敵アイコン座標
constexpr UI_POS_INFO ENEMY_GAUGE_POS_1 = { 1350,10 };					//敵ゲージ左上座標
constexpr UI_POS_INFO ENEMY_GAUGE_POS_2 = { 1910,110 };					//敵ゲージ右下座標
constexpr float		  ENEMY_GAUGE_WIDTH = 560.0f;						//敵ゲージの幅				
constexpr UI_POS_INFO ENEMY_GAUGE_TEXT_POS = { 1650,35 };				//敵ゲージテキスト描画座標
constexpr int		  ENEMT_GAUGE_DRAW_TIME = 50;						//敵ゲージ減少量描画時間



//ポーズ画面関係
constexpr UI_POS_INFO PAUSE_POS_1 = { 300 ,500 };						//ポーズ座標１
constexpr UI_POS_INFO PAUSE_POS_2 = { 300 ,800 };						//ポーズ座標２
constexpr float		  PAUSE_UI_SIZE_NUM = 0.06f;						//ポーズUIサイズ変化量
constexpr float		  PAUSE_UI_MAX_SIZE = 1.5f;							//ポーズUI最大サイズ


//ダメージ関係
constexpr int MAX_DAMAGE_TEXT = 10;		//同時に表示できるダメージテキストの最大数
constexpr int DRAW_TIME = 30;			//ダメージテキストが描画される時間



//プレイシーンのUI
class PlayUI {
private:

	Cursor cursor;				//カーソル

	//フォント
	int damageTextHandle;		//ダメージテキストのフォント
	int comboTextHandle;		//コンボのフォント
	int comboBonusTextHandle;	//コンボのボーナスフォント
	int GaugeTextHandle;		//ゲージ減少のフォント

	//ポーズ画面関係
	int pauseHandle[PAUSE_UI_NUM];		//ポーズ画面の画像
	UI_POS_INFO pos[2];					//ポーズ画面画像座標
	float size[2];						//ポーズ画面画像サイズ
	bool select[2];						//選択されたフラグ
	int page;							//表示されている説明のページ

	//プレイシーンUI
	int	playUIHandle[UI_NUM];			//プレイシーンのUI画像
	VECTOR lockPos;						//ロックオン座標
	
	//ダメージ関係
	bool damageFlag[MAX_DAMAGE_TEXT];	//ダメージを表示するフラグ
	VECTOR damagePos[MAX_DAMAGE_TEXT];	//ダメージを表示する座標
	int damageNum[MAX_DAMAGE_TEXT];		//ダメージ量
	int drawTimeCount[MAX_DAMAGE_TEXT];	//描画された時間
	int enemyIndex[MAX_DAMAGE_TEXT];	//敵の添え字

	//ゲージ関係
	bool subGaugeFlag;					//ゲージ減少表示フラグ
	int subGaugeNum;					//ゲージ減少量
	int subGaugeDrawTime;				//ゲージ減少量が描画された時間

	//情報保存用
	Player playerUI;					//プレイヤー情報保存用
	Gauge gaugeUI;						//ポイント情報保存用
	EnemyManager enemyManagerUI;		//敵情報保存用
	
public:

	PlayUI();
	~PlayUI(){}

	//初期化処理
	void Init();

	//通常処理
	void Step(Player player, EnemyManager enemyManager, Gauge gauge);

	//ポーズ中の通常処理
	int StepPause();

	//描画処理
	void Draw();

	//ポーズ画面描画処理
	void DrawPause();

	//破棄
	void Delete();

private:

	//ダメージのテキスト処理
	void DamageText();

	//ゲージ減少のテキスト処理
	void GaugeText();

	//ロックオンUI処理
	void Lock();
};