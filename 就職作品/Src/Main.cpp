#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Common.h"
#include "GameData/gameData.h"



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetOutApplicationLogValidFlag(false);

	//ウィンドウの状態を設定する
	ChangeWindowMode(false);

	//DXライブラリの初期化
	if(DxLib_Init() == -1)
	{
		return -1;
	}
	
	SetAlwaysRunFlag(true);

	//ウィンドウサイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);

	SetMouseDispFlag(false);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetFullSceneAntiAliasingMode(8, 8);
	SetUseDXArchiveFlag(true);

	//ディレクションライトをセット
	int light;
	VECTOR lightDirection = GetLightDirection();
	lightDirection.x *= -1;
	lightDirection.z *= -1;
	light =CreateDirLightHandle(lightDirection);
	SetLightEnableHandle(light,true);
	
	//フレームレート制御クラス
	FrameRate frameRate;
	
	//入力制御初期化
	Input::Init();
	PadInput::Init();

	//シーンマネージャー
	SceneManager sceneManager;
	sceneManager.Init();
	DebugString::GetInstance();
	//=====================================
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		
		frameRate.Step();
		//60フレームに制限
		if (frameRate.Play()) {

			if (CheckHitKey(KEY_INPUT_F5) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}
		
			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			//入力制御
			Input::Step();
			PadInput::Step();
		
			//シーンマネージャー通常処理
			sceneManager.Step();
			
			//フレームレート描画
			frameRate.CalcFps();
			//frameRate.DrawCalc();
		
			DebugString::GetInstance()->Draw();

			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}
	}
	//最後に１回だけやる処理をここに書く
	
	CEffekseerCtrl::Exit();
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}