#include "playUI.h"
#include "../Collision/Collision.h"


//�R���X�g���N�^	
PlayUI::PlayUI(){

	damageTextHandle = 0;
	comboTextHandle = 0;
	comboBonusTextHandle = 0;
	GaugeTextHandle = 0;

	memset(playUIHandle, 0, sizeof(int[UI_NUM]));
	memset(pauseHandle, 0, sizeof(int[PAUSE_UI_NUM]));
	
	page = 0;
	memset(&pos, 0, sizeof(UI_POS_INFO[2]));
	memset(&size, 0, sizeof(float[2]));
	memset(&select, 0, sizeof(bool[2]));

	memset(&lockPos, 0, sizeof(VECTOR));

	memset(&damageFlag, 0, sizeof(bool[MAX_DAMAGE_TEXT]));
	memset(&damagePos, 0, sizeof(VECTOR[MAX_DAMAGE_TEXT]));
	memset(&damageNum, 0, sizeof(int[MAX_DAMAGE_TEXT]));
	memset(&drawTimeCount, 0, sizeof(int[MAX_DAMAGE_TEXT]));
	memset(&enemyIndex, 0, sizeof(int[MAX_DAMAGE_TEXT]));

	subGaugeFlag = false;
	subGaugeNum = 0;
	subGaugeDrawTime = 0;
}


//UI������
void PlayUI::Init() {

	//UI�̉摜�̃��[�h
	for (int index = 0;index < UI_NUM;index++) {
		if (index < UI_ENEMY_ICON_0) {
			playUIHandle[index] = LoadGraph(UI_IMAGE_PATH[index]);
		}
		else {
			LoadDivGraph(UI_IMAGE_PATH[UI_ENEMY_ICON_0], 5, 5, 1, 100, 100, &playUIHandle[UI_ENEMY_ICON_0]);
		}
	}


	//�|�[�Y��ʂ�UI�摜���[�h
	pauseHandle[PAUSE_UI_CHAR] = LoadGraph(PAUSE_UI_IMAGE_PATH[0]);
	LoadDivGraph(PAUSE_UI_IMAGE_PATH[1], 2, 1, 2, 256, 128, &pauseHandle[PAUSE_UI_CONTINUE]);
	LoadDivGraph(PAUSE_UI_IMAGE_PATH[2], 6, 3, 2, 1280, 1280, &pauseHandle[PAUSE_UI_TUTORIAL_1]);
	LoadDivGraph(PAUSE_UI_IMAGE_PATH[3], 2, 2, 1, 96, 96, &pauseHandle[PAUSE_UI_TUTORIAL_BACK]);

	pos[0] = PAUSE_POS_1;
	pos[1] = PAUSE_POS_2;
	
	//��_���[�W�t�H���g
	damageTextHandle = CreateFontToHandle(NULL, 100, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	
	//�Q�[�W�t�H���g
	GaugeTextHandle = CreateFontToHandle(NULL, 48, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�R���{���t�H���g
	char font_name[7][64];
	EnumFontName(*font_name, 7);
	comboTextHandle = CreateFontToHandle(font_name[6], 64, 48, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	comboBonusTextHandle = CreateFontToHandle(font_name[6], 28, 32, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�_���[�W�֌W������
	for (int index = 0;index < MAX_DAMAGE_TEXT;index++) {
		damageFlag[index] = false;
		damagePos[index] = { 0,0,0 };
		damageNum[index] = 0;
		drawTimeCount[index] = 0;
		enemyIndex[index] = -1;
	}

	//�J�[�\��
	cursor.Init();
}


//UI�ʏ폈��
void PlayUI::Step(Player player,EnemyManager enemyManager, Gauge gauge) {

	playerUI = player;
	enemyManagerUI = enemyManager;
	gaugeUI = gauge;

	DamageText();
	GaugeText();
	Lock();
}


//�|�[�Y����UI����
int PlayUI::StepPause() {

	cursor.Step();

	//UI�̔���
	for (int index = 0;index < 2;index++) {

		//�I�΂�Ă�����
		if (Collision::RectAndCircle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), (float)pos[index].x - 128, (float)pos[index].y - 64, 256, 128)) {
			
			cursor.Select();
			if (size[index] == 1.0f) {
				Sound::Play(C_SE_SELECT, false);
			}

			//UI�T�C�Y��傫��
			size[index] += PAUSE_UI_SIZE_NUM;
			if (size[index] >= PAUSE_UI_MAX_SIZE) {
				size[index] = PAUSE_UI_MAX_SIZE;
			}
			select[index] = true;

			//����{�^���������ꂽ��
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				Sound::Play(C_SE_DECIDE, false);
				return index+1;
			}
		}
		else {//�I�΂�Ă��Ȃ��Ȃ�UI��������
			size[index] -= PAUSE_UI_SIZE_NUM;
			if (size[index] <= 1.0f) {
				size[index] = 1.0f;
			}
			select[index] = false;
		}
	}
	

	//�`���[�g���A���摜�̕ύX����
	if (page > 0) {//�O��
		if (Collision::Circle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), 510, 600, 48)) {
			cursor.Select();
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				Sound::Play(C_SE_DECIDE, false);
				page--;
			}
		
		}
	}
	if (page < 4) {//����
		if (Collision::Circle(cursor.GetPos().x, cursor.GetPos().y, cursor.GetRadius(), 1800, 600, 48)) {
			cursor.Select();
			if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_A)) {
				Sound::Play(C_SE_DECIDE, false);
				page++;
			}
			
		}
	}
	return 0;
}


//UI�\��
void PlayUI::Draw() {

	//�v���C���[HP�A�X�^�~�i
	DrawGraph(PLAYER_STATUS_POS.x, PLAYER_STATUS_POS.y, playUIHandle[UI_PLAYER_STATUS_BASE], true);
	DrawRectGraph(PLAYER_STATUS_POS.x, PLAYER_STATUS_POS.y, 0, 0, playerUI.GetHP() * PLAYER_STATUS_HP_WIDTH, PLAYER_STATUS_HEIGHT, playUIHandle[UI_PLAYER_STATUS_HP], true, false);
	DrawRectGraph(PLAYER_STATUS_POS.x, PLAYER_STATUS_POS.y, 0, 0, playerUI.GetStaminaGauge() / PLAYER_STATUS_STAMINA_WIDTH, PLAYER_STATUS_HEIGHT, playUIHandle[UI_PLAYER_STATUS_STAMINA], true, false);
	DrawGraph(PLAYER_STATUS_POS.x, PLAYER_STATUS_POS.y, playUIHandle[UI_PLAYER_STATUS_FRAME], true);

	//HP�ƃX�^�~�i�̃A�C�R��
	DrawGraph(PLAYER_ICON_HP_POS.x, PLAYER_ICON_HP_POS.y, playUIHandle[UI_PLAYER_ICON_HP], true);
	DrawGraph(PLAYER_ICON_STAMINA_POS.x, PLAYER_ICON_STAMINA_POS.y, playUIHandle[UI_PLAYER_ICON_STAMINA], true);

	//�v���C���[������ԃQ�[�W
	if (playerUI.GetSpecialGauge() > 0) {
		DrawBox(PLAYER_SP_GAUGE_POS.x - MAX_SP_GAUGE / 4, PLAYER_SP_GAUGE_POS.y, PLAYER_SP_GAUGE_POS.x + MAX_SP_GAUGE / 4, 970, 0, true);
		DrawBox(PLAYER_SP_GAUGE_POS.x - playerUI.GetSpecialGauge() / 4, PLAYER_SP_GAUGE_POS.y, PLAYER_SP_GAUGE_POS.x + playerUI.GetSpecialGauge() / 4, 970, GetColor(255, 20, 20), true);
	}

	//�v���C���[�ZUI
	//�_�b�V��
	DrawGraph(PLAYER_ACTION_DASH_POS.x, PLAYER_ACTION_DASH_POS.y, playUIHandle[UI_PLAYER_ACTION_DASH], true);

	//�U��
	if (!playerUI.GetIsDash()) {
		DrawGraph(PLAYER_ACTION_ATTACK_POS.x, PLAYER_ACTION_ATTACK_POS.y, playUIHandle[UI_PLAYER_ACTION_NORMAL_ATTACK], true);
	}
	else {
		DrawGraph(PLAYER_ACTION_ATTACK_POS.x, PLAYER_ACTION_ATTACK_POS.y, playUIHandle[UI_PLAYER_ACTION_DASH_ATTACK], true);
	}

	//�K�E�ZUI
	int sp_ui_index = 0;
	if (playerUI.GetDashAttackCount() < DASH_ATTACK_COUNT_SP_1) {
		sp_ui_index = UI_PLAYER_SPECIAL_LV_0;
	}else if (playerUI.GetDashAttackCount() < DASH_ATTACK_COUNT_SP_2) {
		sp_ui_index = UI_PLAYER_SPECIAL_LV_1;
	}
	else if (playerUI.GetDashAttackCount() < DASH_ATTACK_COUNT_SP_3) {
		sp_ui_index = UI_PLAYER_SPECIAL_LV_2;
	}
	else {
		sp_ui_index = UI_PLAYER_SPECIAL_LV_3;
	}
	DrawRotaGraph(PLAYER_ACTION_SP_POS.x, PLAYER_ACTION_SP_POS.y, 1.0, 0.0, playUIHandle[sp_ui_index], true);
	
	//�K�E�Z�̃Q�[�W
	double percent = 0.0;
	if (playerUI.GetDashAttackCount() < DASH_ATTACK_COUNT_SP_3) {
		percent = (playerUI.GetDashAttackCount() % 10) * 10;
	}
	else {
		percent = 100.0;
	}
	DrawCircleGauge(PLAYER_ACTION_SP_POS.x, PLAYER_ACTION_SP_POS.y, percent, playUIHandle[UI_PLAYER_SPECIAL_GAUGE]);

	//�L�[UI
	if (PadInput::connectPad) {//�p�b�h
		KeyUI::Draw(IMAGE_BUTTON_RB, KEY_DASH_POS.x, KEY_DASH_POS.y);
		KeyUI::Draw(IMAGE_BUTTON_B, KEY_ATTACK_POS.x, KEY_ATTACK_POS.y);
		KeyUI::Draw(IMAGE_BUTTON_Y, KEY_SP_POS.x, KEY_SP_POS.y);
		if (playerUI.GetIsDash()) {
			KeyUI::Draw(IMAGE_STICK_LEFT, KEY_AVOID_LEFT_POS.x, KEY_AVOID_LEFT_POS.y);
			KeyUI::Draw(IMAGE_STICK_RIGHT, KEY_AVOID_RIGHT_POS.x, KEY_AVOID_RIGHT_POS.y);
			KeyUI::Draw(IMAGE_STICK_BACK, KEY_AVOID_BACK_POS.x, KEY_AVOID_BACK_POS.y);
		}
	}
	else {//�L�[�{�[�h
		KeyUI::Draw(IMAGE_MOUSE_RIGHT, KEY_DASH_POS.x, KEY_DASH_POS.y);
		KeyUI::Draw(IMAGE_MOUSE_LEFT, KEY_ATTACK_POS.x, KEY_ATTACK_POS.y);
		KeyUI::Draw(IMAGE_KEY_E, KEY_SP_POS.x, KEY_SP_POS.y);
		if (playerUI.GetIsDash()) {
			KeyUI::Draw(IMAGE_KEY_A, KEY_AVOID_LEFT_POS.x, KEY_AVOID_LEFT_POS.y);
			KeyUI::Draw(IMAGE_KEY_S, KEY_AVOID_RIGHT_POS.x, KEY_AVOID_RIGHT_POS.y);
			KeyUI::Draw(IMAGE_KEY_D, KEY_AVOID_BACK_POS.x, KEY_AVOID_BACK_POS.y);
		}
	}

	//�_���[�W�e�L�X�g
	for (int index = 0; index < MAX_DAMAGE_TEXT; index++) {

		//�\���t���O���I���Ȃ���s
		if (!damageFlag[index]) { continue; }
		
		int color;
		if (index == MAX_DAMAGE_TEXT - 1) {
			color = GetColor(240, 0, 0);
		}
		else {
			color = GetColor(255, 255, 255);
		}
		damagePos[index].y -= 8;
		DrawFormatStringToHandle((int)damagePos[index].x, (int)damagePos[index].y, color, damageTextHandle, "%d", damageNum[index]);
	}


	//�R���{���\��
	if (playerUI.GetCombo() > 0.0f) {
		DrawFormatStringToHandle(COMBO_POS.x, COMBO_POS.y, GetColor(255, 200, 0), comboTextHandle, "�R���{ %d", (int)playerUI.GetCombo());
		DrawFormatStringToHandle(COMBO_BONUS_POS.x, COMBO_BONUS_POS.y, GetColor(255, 200, 0), comboBonusTextHandle, "�|�C���g�~%0.1f",playerUI.GetCombo()/10.0f+1.0f);
		DrawBox(COMBO_GAUGE_POS.x, COMBO_GAUGE_POS.y, COMBO_GAUGE_POS.x + COMBO_TIME, COMBO_GAUGE_POS.y + 20, 0, true);
		DrawBox(COMBO_GAUGE_POS.x, COMBO_GAUGE_POS.y, COMBO_GAUGE_POS.x + playerUI.GetComboCount(), COMBO_GAUGE_POS.y + 20, GetColor(255,255,0), true);
	}

	//�Q�[�W
	if (gaugeUI.GetGauge() <gaugeUI.GetMaxGauge()) {

		//�Q�[�W������
		DrawBox(ENEMY_GAUGE_BOX_POS_1.x, ENEMY_GAUGE_BOX_POS_1.y, ENEMY_GAUGE_BOX_POS_2.x, ENEMY_GAUGE_BOX_POS_2.y,GetColor(200,200,240), true);
		DrawBox(ENEMY_GAUGE_BOX_POS_1.x, ENEMY_GAUGE_BOX_POS_1.y, ENEMY_GAUGE_BOX_POS_2.x, ENEMY_GAUGE_BOX_POS_2.y, 0, false);
		DrawGraph(ENEMY_ICON_POS.x, ENEMY_ICON_POS.y, playUIHandle[UI_ENEMY_ICON_0+ GameData::GetInstance()->GetStageType()], true);
		DrawGraph(ENEMY_GAUGE_POS_1.x, ENEMY_GAUGE_POS_1.y, playUIHandle[UI_ENEMY_HP_BOX_BACK],true);

		//�Q�[�W�{�̕���
		float gauge =  (float)gaugeUI.GetGauge()/ (float)gaugeUI.GetMaxGauge();
		float gauge_left_pos = ENEMY_GAUGE_POS_1.x + (ENEMY_GAUGE_WIDTH * (1.0f - gauge));
		float gauge_image_pos = ENEMY_GAUGE_WIDTH * (1.0f - gauge);
		float gauge_size = ENEMY_GAUGE_WIDTH * gauge;
		DrawRectGraph((int)gauge_left_pos, ENEMY_GAUGE_POS_1.y, (int)gauge_image_pos, 0, (int)gauge_size, ENEMY_GAUGE_POS_2.y, playUIHandle[UI_ENEMY_HP], true);
		
		//�Q�[�W�g
		DrawGraph(ENEMY_GAUGE_POS_1.x, ENEMY_GAUGE_POS_1.y, playUIHandle[UI_ENEMY_HP_BOX],true);
	
		DrawFormatStringToHandle(ENEMY_GAUGE_TEXT_POS.x, ENEMY_GAUGE_TEXT_POS.y, GetColor(255, 255, 255), GaugeTextHandle, "%d/%d", gaugeUI.GetGauge(), gaugeUI.GetMaxGauge());

		//�Q�[�W�㏸�̃e�L�X�g�`��
		if (subGaugeFlag) {
			DrawFormatStringToHandle(ENEMY_GAUGE_TEXT_POS.x, ENEMY_GAUGE_TEXT_POS.y+ (subGaugeDrawTime*3), GetColor(255,255,255), GaugeTextHandle, "+%d", subGaugeNum);
		}
	}
	
	//���b�N�I���̕`��
	if (lockPos.z != -1) {
		if (!playerUI.GetIsDash()) {
			DrawRotaGraph((int)lockPos.x, (int)lockPos.y, 1.0, 0.0, playUIHandle[UI_LOCK_ON_1], true);
		}
		else {
			DrawRotaGraph((int)lockPos.x, (int)lockPos.y, 1.0, 0.0, playUIHandle[UI_LOCK_ON_2], true);
		}
	}
}


//�|�[�Y����UI�`��
void PlayUI::DrawPause() {

	DrawGraph(0, 0, pauseHandle[PAUSE_UI_CHAR], true);
	for (int index = 0; index < 2; index++) {
		DrawRotaGraph(pos[index].x, pos[index].y, size[index], 0.0, pauseHandle[index+1], true);
	}
	DrawModiGraph(560, 190, 1750, 190, 1750, 1080, 560, 1080, pauseHandle[page+4], true);
	
	if (page > 0) {
		DrawRotaGraph(510, 600, 1.0, 0.0, pauseHandle[PAUSE_UI_TUTORIAL_BACK], true);
	}
	if (page < 4) {
		DrawRotaGraph(1800, 600, 1.0, 0.0, pauseHandle[PAUSE_UI_TUTORIAL_NEXT], true);
	}
	cursor.Draw();
}


//�j������
void PlayUI::Delete() {
	
	for (int index = 0; index < UI_NUM; index++) {
		DeleteGraph(playUIHandle[index]);
	}
	for (int index = 0; index < PAUSE_UI_NUM; index++) {
		DeleteGraph(pauseHandle[index]);
	}
	DeleteFontToHandle(damageTextHandle);
	DeleteFontToHandle(comboTextHandle);
	DeleteFontToHandle(comboBonusTextHandle);
	DeleteFontToHandle(GaugeTextHandle);
	cursor.Delete();
}


//�_���[�W�e�L�X�g����
void PlayUI::DamageText() {

	//�_���[�W�e�L�X�g�\�����ԍX�V
	for (int index = 0; index < MAX_DAMAGE_TEXT; index++) {

		//�\���t���O���I���Ȃ���s
		if (!damageFlag[index]) { continue; }
		drawTimeCount[index]++;
		if (drawTimeCount[index] >= DRAW_TIME) {
			damageFlag[index] = false;
			enemyIndex[index] = -1;
		}
	}


	//�v���C���[�̔�_���[�W
	if (playerUI.GetDamage()&&playerUI.GetHP()>0) {
		damagePos[MAX_DAMAGE_TEXT - 1] = ConvWorldPosToScreenPos(playerUI.GetPos());
		damagePos[MAX_DAMAGE_TEXT - 1].y -= 300;
		damageFlag[MAX_DAMAGE_TEXT - 1] = true;
		damageNum[MAX_DAMAGE_TEXT - 1] = playerUI.GetDamageNum();
		drawTimeCount[MAX_DAMAGE_TEXT - 1] = 0;
	}

	//�G�̔�_���[�W
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManagerUI.enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}
	for (int e_index = 0; e_index < max_ene; e_index++) {
		if (e_index == MAX_ENEMY_NUM) {
			if (!enemyManagerUI.enemy[e_index]->GetDamageHit2()) { continue; }
		}
		else {
			if (!enemyManagerUI.enemy[e_index]->GetDamageHit()) { continue; }
		}
		for (int index = 0; index < MAX_DAMAGE_TEXT - 1; index++) {
			if (damageFlag[index]) { continue; }
			if (enemyManagerUI.enemy[e_index]->GetDamageNum() == 999) { continue; }
			damageFlag[index] = true;
			enemyIndex[index] = index;
			damagePos[index].x = (float)SCREEN_SIZE_X / 2+(GetRand(200)-100);
			damagePos[index].y = (float)SCREEN_SIZE_Y / 2 + (GetRand(200) - 100);;
			damageNum[index] = enemyManagerUI.enemy[e_index]->GetDamageNum();
			drawTimeCount[index] = 0;
			break;
		}
	}
}


//�Q�[�W�̃e�L�X�g����
void PlayUI::GaugeText() {

	//�`�悳��Ă���Ȃ玞�Ԃ��X�V
	if(subGaugeFlag){
		subGaugeDrawTime++;
		if (subGaugeDrawTime >= ENEMT_GAUGE_DRAW_TIME) {
			subGaugeDrawTime = 0;
			subGaugeFlag = false;
		}
	}

	//�{�X�����邩
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManagerUI.enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	
	for (int e_index = 0; e_index < max_ene; e_index++) {
		//�{�X
		if (max_ene == MAX_ENEMY_NUM+1) {
			if (enemyManagerUI.enemy[e_index]->GetDamageHit2()) {

				//�_���[�W���󂯂Ă�������s
				subGaugeFlag = true;
				subGaugeDrawTime = 0;
				subGaugeNum = playerUI.GetAttackPower() * (int)playerUI.GetCombo();
			}
		}


		//�ʏ�G
		if (!enemyManagerUI.enemy[e_index]->GetDamageHit() || enemyManagerUI.enemy[e_index]->GetHP() > 0) { continue; }

		//�|���ꂽ�炽����s
		subGaugeFlag = true;
		subGaugeDrawTime = 0;
		subGaugeNum = (int)(enemyManagerUI.enemy[e_index]->GetPoint() * (playerUI.GetCombo() / 10.0f + 1.0f));
	}
	
}


//���b�N�I��UI����
void PlayUI::Lock() {

	VECTOR ene_pos;
	bool exist_lock = false;
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManagerUI.enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}
	for (int e_index = 0; e_index < max_ene; e_index++) {
		if (enemyManagerUI.enemy[e_index]->GetLock()) {
			ene_pos = enemyManagerUI.enemy[e_index]->GetPos();
			ene_pos.y += enemyManagerUI.enemy[e_index]->GetSize()+8;
			lockPos = ConvWorldPosToScreenPos(ene_pos);
			exist_lock = true;
			break;
		}
	}
	if (!exist_lock) {
		lockPos.z = -1;
	}
}