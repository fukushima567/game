#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Common.h"
#include "GameData/gameData.h"



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetOutApplicationLogValidFlag(false);

	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(false);

	//DX���C�u�����̏�����
	if(DxLib_Init() == -1)
	{
		return -1;
	}
	
	SetAlwaysRunFlag(true);

	//�E�B���h�E�T�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetMouseDispFlag(false);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetFullSceneAntiAliasingMode(8, 8);
	SetUseDXArchiveFlag(true);

	//�f�B���N�V�������C�g���Z�b�g
	int light;
	VECTOR lightDirection = GetLightDirection();
	lightDirection.x *= -1;
	lightDirection.z *= -1;
	light =CreateDirLightHandle(lightDirection);
	SetLightEnableHandle(light,true);
	
	//�t���[�����[�g����N���X
	FrameRate frameRate;
	
	//���͐��䏉����
	Input::Init();
	PadInput::Init();

	//�V�[���}�l�[�W���[
	SceneManager sceneManager;
	sceneManager.Init();
	DebugString::GetInstance();
	//=====================================
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		
		frameRate.Step();
		//60�t���[���ɐ���
		if (frameRate.Play()) {

			if (CheckHitKey(KEY_INPUT_F5) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}
		
			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			//���͐���
			Input::Step();
			PadInput::Step();
		
			//�V�[���}�l�[�W���[�ʏ폈��
			sceneManager.Step();
			
			//�t���[�����[�g�`��
			frameRate.CalcFps();
			//frameRate.DrawCalc();
		
			DebugString::GetInstance()->Draw();

			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}
	}
	//�Ō�ɂP�񂾂���鏈���������ɏ���
	
	CEffekseerCtrl::Exit();
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}