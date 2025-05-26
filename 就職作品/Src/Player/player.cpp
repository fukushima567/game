#include "player.h"
#include "../MyLib/MyLib.h"
#include "../Collision/Collision.h"


//�R���X�g���N�^
Player::Player() {

	toolHandle = 0;
	frameIndex = 0;

	memset(&rot, 0, sizeof(VECTOR));
	memset(&cameraRot, 0, sizeof(VECTOR));
	memset(&toolPos, 0, sizeof(VECTOR));

	ground = false;
	lockOn = false;

	dashAttackCount = 0;
	invincibleCount = 0;

	combo = 0.0f;
	comboCount = 0;
	nearEneRad = 0.0f;

	drawDash = false;
	finishDash = false;
	staminaGauge = 0;
	avoidType = 0;
	avoidCount = 0.0f;
	currentMaxSpeed = 0.0f;
	dashSub = 0.0f;

	attackFlag = false;
	attackHit = false;
	attackMiss = false;
	attackType = 0;

	specialState = 0;
	specialGauge = 0;

	hitStop = false;
	hitStopNum = 0;
	hitStopCount = 0;

	damageFlag = false;
	damageNum = 0;
	damageRot = 0.0f;

	effectRequest = false;
	memset(&effectHandle, 0, sizeof(int(PLAYER_EFFECT_NUM)));
	memset(&effectIndex, 0, sizeof(int(PLAYER_EFFECT_NUM)));
}


//����������
void Player::Init() {
	
	//���f���̃��[�h
	modelHandle = MV1LoadModel("Data/Image/Play/player/player.mv1");
	toolHandle = MV1LoadModel("Data/Image/Play/player/sword.mv1");

	//�v���C���[�̃G�t�F�N�g���[�h
	effectHandle[PLAYER_EFFECT_ATTACK] = CEffekseerCtrl::LoadData("data/effect/sword.efk");
	effectHandle[PLAYER_EFFECT_SP] = CEffekseerCtrl::LoadData("data/effect/special.efk");
	effectHandle[PLAYER_EFFECT_SP_ATTACK] = CEffekseerCtrl::LoadData("data/effect/exSword.efk");

	//�v���C���[�̃o�b�N�J�����O���I�t��
	for (int index = 0; index < MV1GetMeshNum(modelHandle); index++) {
		MV1SetMeshBackCulling(modelHandle, index, FALSE);
	}

	//���W������
	pos = FIRST_POS;

	//�v���C���[�̓����蔻��T�C�Y������
	size = PLAYER_SPHERE;

	//�v���C���[�̗͏�����
	HP = MAX_HP;

	//�v���C���[�X�^�~�i������
	staminaGauge = MAX_STAMINA_GAUGE;

	//�v���C���[�̓�������t���[���擾
	frameIndex = MV1SearchFrame(modelHandle, "tool2");

	//�A�j���[�V����������
	InitAnim(PLAYER_ANIMATION_NUM);
}


//�ʏ폈��
void Player::Step() {

	attackHit = false;

	//�q�b�g�X�g�b�v
	if (hitStop) {
		hitStopCount++;

		//�N���A���q�b�g�X�g�b�v���̓G�t�F�N�g���~�߂�
		if (hitStopNum == HIT_STOP_CLEAR) {
			CEffekseerCtrl::StopUpdate();
		}
		//�w�莞�Ԍo�߂Ńq�b�g�X�g�b�v�I��
		if (hitStopCount > hitStopNum) {
			hitStopCount = 0;
			hitStop = false;
		}
		return;
	}

	drawDash = false;

	//�_�b�V���A�^�b�N�~�X���̃m�b�N�o�b�N
	if (attackMiss) {
		if (curAnim == PLAYER_MISS && animCount < ATTACK_MISS_TIME) {
			pos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_MISS_NUM);
		}
	}
	else {
		if (specialState != SPECIAL_READY && HP > 0) {

			KnockBack();
			//�m�b�N�o�b�N���͑�����󂯕t���Ȃ�
			if (!damageFlag) {
				Walk();
				Dash();
				Special();
				Attack();
			}

			pos = MyLib::Get3DCircle(pos, 0, rot.y, speed / (float)GameData::GetInstance()->GetGameTime());
		}
	}

	//���ʒu�ȉ��ŏ����ʒu�փ��Z�b�g
	if (pos.y <= PLAYER_MIN_Y) {
		pos = FIRST_POS;
		attackType = PLAYER_ATTACK_NONE;
		HP -= SUB_HP;
	}
	
	//�A�j���[�V��������
	Animation();
		
	//�G�t�F�N�g����
	Effect();

	pos.y -= GRAVITY;
	ground = false;
}


//�`�揈��
void Player::Draw() {

	if (lockOn && nearEneRad != -1) {
		rot.y = nearEneRad;
	}

	MV1SetRotationXYZ(modelHandle, { rot.x,rot.y + MyLib::GetRadian(180),rot.z });
	MV1SetPosition(modelHandle, pos);

	//����̍��W��ݒ�
	toolPos = MV1GetFrameLocalWorldMatrix(modelHandle, frameIndex);
	MV1SetMatrix(toolHandle, toolPos);

	//�v���C���[�̕`��
	MV1DrawModel(toolHandle);
	MV1DrawModel(modelHandle);
}


//�j������
void Player::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(toolHandle);
}


//��������
void Player::Walk() {

	float rad = 0.0f;

	//�����ړ�
	if (!lockOn && !finishDash) {
		speed = 0.0f;

		//�R���g���[���[�̈ړ�
		if (PadInput::GetLX() > 0 || PadInput::GetLY() > 0 || PadInput::GetLX() < 0 || PadInput::GetLY() < 0) {
			speed = WALK_SPEED;
			rad = MyLib::GetPosRadian(0, 0, (float)PadInput::GetLY(), (float)PadInput::GetLX());
			rot.y = cameraRot.y + rad;
		}

		//�L�[�{�[�h�̓���
		if (Input::Keep(KEY_INPUT_A)) {//��
			speed = WALK_SPEED;
			rad = MyLib::GetRadian(-90);
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_D)) {//�E
			speed = WALK_SPEED;
			rad = MyLib::GetRadian(90);
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_W)) {//�O
			speed = WALK_SPEED;
			rad -= rad / 2;
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_S)) {//���
			speed = WALK_SPEED;
			rot.y = cameraRot.y - rad / 2 + MyLib::GetRadian(180);
		}
	}

	//�����T�E���h
	if (curAnim == PLAYER_WALK) {
		if (animCount == WALK_ANIM_COUNT_1 || animCount == WALK_ANIM_COUNT_2) {
			Sound::Play(P_SE_PLAYER_WALK, false);
		}
	}
}


//���菈��
void Player::Dash() {
	
	//�^�[�Q�b�g���Ȃ��Ȃ�ƃ_�b�V���I��
	if (nearEneRad == -1) {
		lockOn = false;
	}

	//�X�^�~�i���Ȃ��Ȃ�ƃ_�b�V���I���A�R���{���Z�b�g
	if (staminaGauge <= 0) {
		lockOn = false;
		if (avoidType == AVOID_NONE) {
			finishDash = true;
		}
		else {
			finishDash = false;
		}
		combo = 0;
	}

	//�^�[�Q�b�g�Ɍ���
	if (nearEneRad != -1) {
		
		rot.y = nearEneRad;
	}

	//�_�b�V���̐؂�ւ�
	if (Input::PushMouse(MOUSE_RIGHT) || PadInput::Push(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		//�_�b�V��
		if (!lockOn) {
			lockOn = true;
		}
		else {//�_�b�V���I��
			lockOn = false;
			if (avoidType == AVOID_NONE) {
				finishDash = true;
			}
			else {
				finishDash = false;
			}
		}
	}


	//�_�b�V��
	if (lockOn) {
		finishDash = false;
		if (combo > 0) {
			drawDash = true;
		}

		//�_�b�V�����̓X�^�~�i����
		staminaGauge -= STAMINA_SUB_NUM;

		//�������
		Avoid();

		//������Ă��Ȃ���Α���
		if (avoidType == AVOID_NONE) {

			//�R���{���ő��葬�x�ύX
			if (DASH_SPEED + 1 * (combo / MAX_DASH_SPEED_NUM) < MAX_SPEED) {
				currentMaxSpeed = DASH_SPEED + 1.0f * (combo / MAX_DASH_SPEED_NUM);
			}
			else {//���x����ȏ�ɂ����Ȃ��悤�ɂ���
				currentMaxSpeed = MAX_SPEED;
			}

			//�_�b�V���̌����l
			dashSub = currentMaxSpeed / SUB_DASH_SPEED;
			
			//�_�b�V��������
			speed += ADD_DASH_SPEED;
			if (currentMaxSpeed < speed) {
				speed = currentMaxSpeed;
			}
		}
	}
	else {//�����Ă��Ȃ��Ƃ��A�X�^�~�i��
		staminaGauge += STAMINA_ADD_NUM;

		//�X�^�~�i�Q�[�W�̏����ݒ�
		if (MAX_STAMINA_GAUGE < staminaGauge) {
			staminaGauge = MAX_STAMINA_GAUGE;
		}

		avoidType = AVOID_NONE;
		avoidCount = 0;
	}

	//�_�b�V�����I������Ə��X�Ɍ���
	if (finishDash) {
		speed -= dashSub;
		if (speed <= 0) {
			finishDash = false;
		}
	}

	//����T�E���h
	if (curAnim == PLAYER_DASH) {
		if (animCount == DASH_ANIM_COUNT_1 || animCount == DASH_ANIM_COUNT_2) {
			Sound::Play(P_SE_PLAYER_DASH, false);
		}
	}
	//�����̃T�E���h
	if (curAnim == PLAYER_DASH_AFTER && animCount == 0) {
		Sound::Play(P_SE_PLAYER_DASH_FIN, false);
	}
	if (curAnim != PLAYER_DASH_AFTER) {
		Sound::Stop(P_SE_PLAYER_DASH_FIN);
	}
}


//�������
void Player::Avoid() {

	//��𔭓�����
	if (attackType == PLAYER_ATTACK_NONE && avoidType == AVOID_NONE) {
		//��
		if (Input::Push(KEY_INPUT_A) || PadInput::GetPushLX() < 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_LEFT;
			invincibleCount = AVOID_INVINCIBLE;
		}
		//�E
		if (Input::Push(KEY_INPUT_D) || PadInput::GetPushLX() > 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_RIGHT;
			invincibleCount = AVOID_INVINCIBLE;
		}
		//���
		if (Input::Push(KEY_INPUT_S) || PadInput::GetPushLY() < 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_BACK;
			invincibleCount = AVOID_INVINCIBLE;
		}
	}

	//��𒆂̏���
	switch (avoidType) {

	case AVOID_NONE:
		break;

		//��
	case AVOID_LEFT:
		rot.y += MyLib::GetRadian(-90);
		speed = avoidCount;
		avoidCount -= SUB_AVOID_COUNT;
		if (avoidCount <= 0) {
			avoidType = AVOID_NONE;
			avoidCount = 0;
		}
		break;

		//�E
	case AVOID_RIGHT:
		rot.y += MyLib::GetRadian(90);
		speed = avoidCount;
		avoidCount -= SUB_AVOID_COUNT;
		if (avoidCount <= 0) {
			avoidType = AVOID_NONE;
			avoidCount = 0;
		}
		break;

		//���
	case AVOID_BACK:
		rot.y += MyLib::GetRadian(180);
		speed = avoidCount;
		avoidCount -= SUB_AVOID_COUNT;
		if (avoidCount <= 0) {
			avoidType = AVOID_NONE;
			avoidCount = 0;
		}
		break;
	}
}


//�K�E�Z����
void Player::Special() {

	switch (specialState) {

	//�K�E�Z�̔���
	case SPECIAL_NONE:
		
		//�K�E�Z�̏����𖞂����Ă�����
		if (dashAttackCount >= DASH_ATTACK_COUNT_SP_1) {
			if (Input::Push(KEY_INPUT_E) || PadInput::Push(XINPUT_BUTTON_Y)) {
				lockOn = false;

				//�v���C���[�𔭌�
				for (int index = 0; index < PLAYER_MATERIAL_NUM; index++) {
					MV1SetMaterialEmiColor(modelHandle, index, COLOR_RED);
				}

				//�K�E�Z��Ԃ��Z�b�g
				specialState = SPECIAL_READY;
				specialGauge = MAX_SP_GAUGE;

				//�K�E�Z�̃��x���ɉ����čU���͂��Z�b�g
				if (dashAttackCount >= DASH_ATTACK_COUNT_SP_1) {
					attackPower = NOMAL_ATTACK_POWER;
				}
				if (dashAttackCount >= DASH_ATTACK_COUNT_SP_2) {
					attackPower = NOMAL_DASH_ATTACK_POWER;
				}
				if (dashAttackCount >= DASH_ATTACK_COUNT_SP_3) {
					attackPower = NOMAL_DASH_ATTACK_POWER * 2;
				}
				effectRequest = true;
			}
		}
		break;

	//�K�E�Z�\������
	case SPECIAL_READY:

		break;

	//�K�E�Z��
	case SPECIAL_ACTIVE:

		specialGauge--;
		invincibleCount = 0;
		//�Q�[�W�������Ȃ�ƕK�E�Z�I��
		if (specialGauge <= 0) {
			specialState = SPECIAL_FINISH;
		}
		break;

	//�K�E�Z�̏I��
	case SPECIAL_FINISH:
		for (int index = 0; index < PLAYER_MATERIAL_NUM; index++) {
			MV1SetMaterialEmiColor(modelHandle, index, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
		}
		attackType = PLAYER_ATTACK_NONE;
		specialState = SPECIAL_NONE;
		dashAttackCount = 0;
		break;
	}
}


//�m�b�N�o�b�N����
void Player::KnockBack() {

	//���G���Ԃ��J�E���g
	invincibleCount++;
	if (invincibleCount > DAMAGE_INTERVAL / 2) {
		damageFlag = false;
	}
	if (damageFlag) {//�_���[�W�t���O���I���̎��A�m�b�N�o�b�N
		speed = WALK_SPEED;
		pos.z = MyLib::GetCircleX(pos.z, speed, damageRot);
		pos.x = MyLib::GetCircleY(pos.x, speed, damageRot);
	}
}


//�U������
void Player::Attack() {

	//������Ԃ̃_�b�V���U��
	if (specialState == SPECIAL_ACTIVE) {
		attackType = PLAYER_ATTACK_SPECIAL;
	}
	if (attackType == PLAYER_ATTACK_SPECIAL) {
		drawDash = true;
		speed = SP_DASH_ATTACK_SPEED;
	}

	
	//�U��
	if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_B)) {

		if (attackType == PLAYER_ATTACK_NONE) {
			
			if (!lockOn) {//�����Ă��Ȃ�������ʏ�U��
				attackType = PLAYER_ATTACK_NORMAL;
			}
			else {//�����Ă�����_�b�V���U��
				attackType = PLAYER_ATTACK_DASH;
				effectRequest = true;
				avoidType = AVOID_NONE;
				avoidCount = 0;
			}

			//����U������
			Sound::Play(P_SE_PLAYER_ATTACK, false);
		}
	}

	//�ʏ�U�����͈ړ��ł��Ȃ�
	if (attackType == PLAYER_ATTACK_NORMAL) {
		speed = 0;
	}

	//�U���̐ݒ�
	switch (curAnim) {

	case PLAYER_NOMAL_ATTACK://�ʏ�U��
		if (animCount > ATTACK_NORMAL_MIN) {
			attackPos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_RANGE);
			attackPower = NOMAL_ATTACK_POWER;
			attackSize = ATTACK_SIZE_1;
			hitStopNum = HIT_STOP_NORMAL;
			attackFlag = true;
		}
		else {
			attackFlag = false;
		}
		break;

	case PLAYER_DASH_ATTACK://�_�b�V���U��
		if (animCount > ATTACK_DASH_MIN && animCount < ATTACK_DASH_MAX) {
			attackPos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_RANGE);
			attackSize = ATTACK_SIZE_1;
			attackFlag = true;
			hitStopNum = HIT_STOP_DASH;
			attackPower = NOMAL_DASH_ATTACK_POWER;
		}
		else {
			attackFlag = false;
		}
		break;

	case PLAYER_DASH_ATTACK_2://�������̃_�b�V���U��
		attackPos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_RANGE);
		hitStopNum = HIT_STOP_SPECIAL;
		attackSize = ATTACK_SIZE_1;
		if (nearEneRad != -1) {
			rot.y = nearEneRad;
		}
		dashAttackCount = 0;
		attackFlag = true;
		break;

	default://��U��
		attackFlag = false;
		break;
	}

	//�R���{���ɉ����ĕ��킪����
	float combo_color = combo;
	if (combo_color > MAX_SWORD_COLOR) {
		combo_color = MAX_SWORD_COLOR;
	}
	for (int index = 0; index < SWORD_MATERIAL_NUM; index++) {
		MV1SetMaterialEmiColor(toolHandle, index, GetColorF(combo_color / MAX_SWORD_COLOR, 0.0f, 0.0f, 1.0f));
	}

	//���Ԍo�߂ŃR���{������
	if (comboCount != 0) {
		comboCount--;
		if (comboCount == 0) {
			combo = 0;
		}
	}
}


//�A�j���[�V��������
void Player::Animation() {

	//�A�j���[�V�������؂�ւ��I���������s
	if (animBlend[curAnim] >= 1.0f) {

		if (HP <= 0) {//�v���C���[�|����
			if (curAnim != PLAYER_DATH) {
				ChangeAnim(PLAYER_DATH);
			}
		}
		else if (specialState == SPECIAL_READY) {//������Ԉڍs
			if (curAnim != PLAYER_SPECIAL) {
				ChangeAnim(PLAYER_SPECIAL);
			}
		}
		else if (!ground) {//�W�����v�~��
			if (curAnim != PLAYER_AIR) {
				ChangeAnim(PLAYER_AIR);
			}
		}
		else if (specialState == SPECIAL_ACTIVE) {//������ԃ_�b�V���U��
			if (curAnim != PLAYER_DASH_ATTACK_2) {
				ChangeAnim(PLAYER_DASH_ATTACK_2);
			}
		}
		else if (attackMiss) {//�U�����s
			if (curAnim != PLAYER_MISS) {
				ChangeAnim(PLAYER_MISS);
			}
		}
		else if (damageFlag) {//��_���[�W
			if (curAnim != PLAYER_DAMAGE) {
				ChangeAnim(PLAYER_DAMAGE);
			}
		}
		else if (avoidType == AVOID_LEFT) {//�����
			if (curAnim != PLAYER_LEFT_STEP) {
				ChangeAnim(PLAYER_LEFT_STEP);
			}
		}
		else if (avoidType == AVOID_RIGHT) {//�E���
			if (curAnim != PLAYER_RIGHT_STEP) {
				ChangeAnim(PLAYER_RIGHT_STEP);
			}
		}
		else if (avoidType == AVOID_BACK) {//�����
			if (curAnim != PLAYER_BACK_STEP) {
				ChangeAnim(PLAYER_BACK_STEP);
			}
		}
		else if (attackType == PLAYER_ATTACK_DASH) {//�_�b�V���U��
			if (curAnim != PLAYER_DASH_ATTACK) {
				ChangeAnim(PLAYER_DASH_ATTACK);
			}
		}
		else if (finishDash) {//�����
			if (curAnim != PLAYER_DASH_AFTER) {
				ChangeAnim(PLAYER_DASH_AFTER);
			}
		}
		else if (attackType == PLAYER_ATTACK_NORMAL) {//�ʏ�U��
			if (curAnim != PLAYER_NOMAL_ATTACK) {
				ChangeAnim(PLAYER_NOMAL_ATTACK);
			}
		}
		else if (lockOn) {//�_�b�V��
			if (curAnim != PLAYER_DASH) {
				ChangeAnim(PLAYER_DASH);
			}
		}
		else if (speed <= WALK_SPEED && speed > 0) {//����
			if (curAnim != PLAYER_WALK) {
				ChangeAnim(PLAYER_WALK);
			}
		}
		else {
			if (curAnim != PLAYER_IDLE && attackType== PLAYER_ATTACK_NONE) {//�ҋ@
				ChangeAnim(PLAYER_IDLE);
			}
		}
	}

	//�A�j���[�V�������X�V
	UpdateAnim();

	//�A�j���[�V�������Đ����I������
	if (animCount >= animAllTime) {
		if (curAnim == PLAYER_SPECIAL) {
			specialState++;
		}
		else if (curAnim == PLAYER_MISS) {
			attackMiss = false;
		}//���[�v
		else if (curAnim != PLAYER_DASH_ATTACK && curAnim != PLAYER_NOMAL_ATTACK) {
			animCount = 0.0f;
		}
		else {
			attackType = PLAYER_ATTACK_NONE;
		}
	}
}


//�G�t�F�N�g����
void Player::Effect() {
	
	//�_�b�V���A�^�b�N�a��
	if (attackType == PLAYER_ATTACK_DASH) {
		if (effectRequest) {
			effectIndex[PLAYER_EFFECT_ATTACK] = CEffekseerCtrl::Request(effectHandle[PLAYER_EFFECT_ATTACK], pos, false);
			effectRequest = false;
		}
		else {//�G�t�F�N�g�ʒu�X�V
			CEffekseerCtrl::SetPosition(effectIndex[PLAYER_EFFECT_ATTACK], pos);
			CEffekseerCtrl::SetRot(effectIndex[PLAYER_EFFECT_ATTACK], { rot.x,rot.y - MyLib::GetRadian(90),rot.z });
		}
	}

	//�K�E�a��
	if (attackType == PLAYER_ATTACK_SPECIAL) {
		if (effectRequest) {
			effectIndex[PLAYER_EFFECT_SP_ATTACK] = CEffekseerCtrl::Request(effectHandle[PLAYER_EFFECT_SP_ATTACK], pos, true);
			effectRequest = false;
		}
		else {
			CEffekseerCtrl::SetPosition(effectIndex[PLAYER_EFFECT_SP_ATTACK], { pos.x,pos.y,pos.z });
			CEffekseerCtrl::SetRot(effectIndex[PLAYER_EFFECT_SP_ATTACK], { rot.x,rot.y - MyLib::GetRadian(90),rot.z });
		}
		if (specialState == SPECIAL_FINISH) {
			CEffekseerCtrl::Stop(effectIndex[PLAYER_EFFECT_SP_ATTACK]);
		}
	}

	if (curAnim == PLAYER_SPECIAL && animCount == 0) {
		effectIndex[PLAYER_EFFECT_SP] = CEffekseerCtrl::Request(effectHandle[PLAYER_EFFECT_SP], pos, false);
	}
}


//�N���A���̏���
void Player::clear() {

	rot.y = 0.0f;
	pos = { 0,0,0 };
	//�N���A�A�j���[�V�����ɕύX
	if (curAnim != PLAYER_CLEAR) {
		ChangeAnim(PLAYER_CLEAR);
	}
	//�A�j���[�V�������X�V
	UpdateAnim();
	if (animCount >= animAllTime) {
		animCount = animAllTime;
	}
}


//�_���[�W���󂯂�
void Player::Damage(VECTOR enemy_pos,int damage){

	//���G���Ԃ��I����Ă����珈��
	if (invincibleCount >= DAMAGE_INTERVAL) {
		invincibleCount = 0;
		HP -= damage;
		damageNum = damage;
		damageFlag = true;
		attackType = PLAYER_ATTACK_NONE;
		attackFlag = false;
		lockOn = false;
		finishDash = false;
		combo = 0;
		damageRot = MyLib::GetPosRadian(enemy_pos.z, enemy_pos.x, pos.z, pos.x);
		Sound::Play(P_SE_PLAYER_DAMAGE, false);
	}
}


//�R���{����
void Player::Combo() {
	combo++;
	comboCount = COMBO_TIME;
	dashAttackCount++;
	staminaGauge = MAX_STAMINA_GAUGE;
	lockOn = false;
	attackHit = true;
	finishDash = true;
}


//�_�b�V���U�����s����
void Player::AttackMiss() {
	finishDash = false;
	combo = 0;
	attackMiss = true;
	lockOn = false;
	Sound::Play(P_SE_PLAYER_DAMAGE, false);
}


//���ɂ����ۂ̏���
void Player::Ground() { 
	ground = true;
}


//�_���[�W���󂯂��u�Ԃ�
bool Player::GetDamage() {

	if (damageFlag && animCount == 0 && PLAYER_DAMAGE) {
		return true;
	}
	else {
		return false;
	}
}


//�_�b�V����Ԃ�
bool Player::GetIsDash() {
	if (lockOn && attackType == PLAYER_ATTACK_NONE && avoidType == AVOID_NONE) {
		return true;
	}
	return false;
}


//��ԋ߂��G�̊p�x�𓾂�
float Player::GetEneRad() {
	if (specialState != SPECIAL_NONE) { return -1; }
	return nearEneRad;
}


//��ԋ߂��G�Ƃ̊p�x���Z�b�g
void Player::SetNearEneRad(float ene_rad){
	if (ene_rad != -1) {
		if (ene_rad < 0) {
			ene_rad += MyLib::GetRadian(360);
		}
	}
	nearEneRad = ene_rad;
}


//�q�b�g�X�g�b�v���I���ɂ���
void Player::SetHitStop(bool max) {
	hitStop = true;
	if (max) {
		hitStopNum = HIT_STOP_CLEAR;
		GameData::GetInstance()->SetGameTime(SLOW_TIME);
	}
}