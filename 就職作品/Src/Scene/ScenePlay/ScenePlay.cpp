#include "ScenePlay.h"


int GameTime;


//�v���C�V�[��������
void ScenePlay::Init() {

	CEffekseerCtrl::Init(50, 500);
	
	LoadDivGraph("data/Image/Play/UI/startScreen.png", 2, 1, 2, 1920, 1080, startHandle);
	
	
	LoadDivGraph("data/Image/Play/UI/clear.png", 2, 1, 2, 1920, 1080, clearHandle);

	player.Init();

	cameraManager.SetCameraType(cameraManager.CAMERA_TYPE_START);
	cameraManager.Init();
	cameraManager.SetNearFar(5, 5000);
	stage.Init();
	enemyManager.Init();
	gauge.Init();
	screenEffect.Init();
	ui.Init();
	
	if (GameData::GetInstance()->GetStageType() == STAGE_0) {
		LoadDivGraph("Data/Image/Play/UI/tutorial.png", 6, 3, 2, 1280, 1280, tutorialHandle);
		tutorial=true;
		page = 0;
		Sound::Play(P_BGM_1, true);
	}
	else if (GameData::GetInstance()->GetStageType() == STAGE_4) {
		Sound::Play(P_BGM_3, true);
	}else {
		Sound::Play(P_BGM_2, true);
	}

	sceneState = SCENE_PLAY_START;
	fade = false;

	sceneStateCount = 0;
	pause = false;
	GameTime = (int)NORMAL_TIME;
	fin = false;
}


//�v���C�V�[���ʏ폈��
void ScenePlay::Step() {

	//�n�܂�̏���
	if (sceneState == SCENE_PLAY_START) {
		if (Input::PushMouse(MOUSE_LEFT)|| PadInput::Push(XINPUT_BUTTON_A)) {
			
			fade = true;
		}
		
		enemyManager.Step({-1,-1,-1}, gauge.GetActive(),false);
		cameraManager.Step(player.GetPos(), -1.0f, false);
		sceneCollision.EnemyAndStage(&enemyManager, &stage);
	}

	//�v���C����
	if (sceneState == SCENE_PLAY_GAME) {

		//�X�e�[�W0�̂݃`���[�g���A���摜��`�悷��
		if (tutorial) {
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				page++;
				Sound::Play(C_SE_DECIDE,false);
				if (page > 5) {
					tutorial = false;
				}
			}
			return;
		}

		if (!pause) {
			CEffekseerCtrl::UpdateAutoCamera();

			player.Step();
			enemyManager.Step(player.GetPos(), gauge.GetActive(),player.GetHitStop());
			stage.Step();
			stage.SetPos(player.GetPos());
			player.SetCameraRad(cameraManager.GetRot());
			gauge.Step();
			ui.Step(player, enemyManager, gauge);

			//�����蔻��֌W
			sceneCollision.PlayerAndEnemy(&player, &enemyManager);
			sceneCollision.LockOn(&player, &enemyManager, &stage, player.GetLockOn());
			sceneCollision.EnemyAndEnemy(&enemyManager);

			sceneCollision.PlayerAttackAndEnemy(&player, &enemyManager, &gauge);
			sceneCollision.PlayerAndEnemyAttack(&player, &enemyManager);
			sceneCollision.PlayerAndEnemyBullet(&player, &enemyManager);

		
			sceneCollision.PlayerAndStage(&player, &stage);
			sceneCollision.EnemyAndStage(&enemyManager, &stage);
			cameraManager.Step(player.GetPos(), player.GetEneRad(), player.GetIsDash());

		}
		else {//�|�[�Y��ʏ���

			switch (ui.StepPause()) {
			case 0://���̂܂�
				
				break;
			case 1://���s
				pause = false;
				break;

			case 2://��߂�
				GameData::GetInstance()->SetSceneID(SELECT);
				Delete();
				break;
			}
		}

		//tab�L�[�Ń��j���[
		if (Input::Push(KEY_INPUT_ESCAPE) || PadInput::Push(XINPUT_BUTTON_START)) {
			if (!pause) {
				pause = true;
			}
			else {
				pause = false;
			}
		}

		if (!gauge.GetActive()|| player.GetHP() <= 0) {
			sceneStateCount++;
		}
		
		//�N���A���Q�[���I�[�o�[������
		if (sceneStateCount > 180) {
			if (!gauge.GetActive()) {
				sceneState = SCENE_PLAY_CLEAR;
				Sound::StopAll();
				Sound::Play(P_BGM_VICTORY, false);
			}
			else {
				sceneState = SCENE_PLAY_GAME_OVER;
			}
			fade = false;
		}
	}

	//�Q�[���N���A����
	if (sceneState == SCENE_PLAY_CLEAR) {
		player.clear();
		cameraManager.SetCameraType(cameraManager.CAMERA_TYPE_CLEAR);
		cameraManager.Step({ 0,0,0 }, 0, 0);
		if (Input::PushMouse(MOUSE_LEFT)|| PadInput::Push(XINPUT_BUTTON_A)) {
			fade = true;
		}
		GameTime = (int)NORMAL_TIME;
	}

	//�Q�[���I�[�o�[����
	if (sceneState == SCENE_PLAY_GAME_OVER) {
		Delete();
		GameData::GetInstance()->SetSceneID(OVER);
	}
}


//�v���C�V�[���`��
void ScenePlay::Draw() {
	
	switch (sceneState) {

		//�J�n�O�`��
	case SCENE_PLAY_START:

		stage.Draw();
		player.Draw();
		enemyManager.Draw();
		if (PadInput::connectPad) {
			DrawGraph(0, 0, startHandle[1], true);
		}
		else {
			DrawGraph(0, 0, startHandle[0], true);
		}

		if (!fade) {
			screenEffect.FadeIn();
		}
		else {
			if (screenEffect.FadeOut()) {
				sceneState = 1;
				cameraManager.SetCameraType(cameraManager.CAMERA_TYPE_PLAYER);
			}
		}
		break;


		//�v���C�`��
	case SCENE_PLAY_GAME:

		stage.Draw();
		if (cameraManager.GetRadius() < -5) {
			player.Draw();
		}
		enemyManager.Draw();
		gauge.Draw();

		CEffekseerCtrl::Draw();

		//�`���[�g���A���摜
		if (tutorial) {
			DrawModiGraph(300, 0, 1920 - 300, 0, 1920 - 300, 1030, 300, 1030, tutorialHandle[page], true);

			if (PadInput::connectPad) {
				DrawFormatStringToHandle(800, 980, BASE_FONT_COLOR, GameData::GetInstance()->GetFontHandle(), "A�{�^���Ŏ���");
			}
			else {
				DrawFormatStringToHandle(800, 980, BASE_FONT_COLOR, GameData::GetInstance()->GetFontHandle(), "�N���b�N�Ŏ���");
			}
			return;
		}

		if (!pause) {//��|�[�Y���̃G�t�F�N�g�AUI
			screenEffect.DashEffect(player.GetSpeed(), player.GetDrawScreenEffect());
			ui.Draw();
			if (player.GetHitStop()) {
				screenEffect.ShakeScreen();
			}
			screenEffect.SwordEffect(player.GetAttackHit());
		}
		else {//�|�[�Y���̃G�t�F�N�g�AUI
			screenEffect.GaussEffect();
			ui.DrawPause();
		}

		if (sceneStateCount > 110) {
			if (player.GetHP() <= 0) {
				screenEffect.FadeOut(true);
			}
			else {
				screenEffect.FadeOut(false);
			}
		}
		else {
			screenEffect.FadeIn();
		}
		break;


		//�Q�[���N���A
	case SCENE_PLAY_CLEAR:

		stage.Draw();
		player.Draw();
		if (!PadInput::connectPad) {
			DrawGraph(0, 0, clearHandle[0], true);
		}
		else {
			DrawGraph(0, 0, clearHandle[1], true);
		}

		if (!fade) {
			screenEffect.FadeIn(false);
		}
		else {
			if (screenEffect.FadeOut()) {
				Delete();
				GameData::GetInstance()->SetSceneID(SELECT);
			}
		}

		break;
	}
}


//�V�[���v���C�j��
void ScenePlay::Delete() {

	for (int index = 0; index < 2; index++) {
		DeleteGraph(clearHandle[index]);
		DeleteGraph(startHandle[index]);
	}

	for (int index = 0; index < 6; index++) {
		DeleteGraph(tutorialHandle[index]);
	}
	
	fin = true;
	stage.Delete();
	player.Delete();
	enemyManager.Delete();
	screenEffect.Delete();
	ui.Delete();
	CEffekseerCtrl::Exit();
}
