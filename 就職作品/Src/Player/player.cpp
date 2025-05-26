#include "player.h"
#include "../MyLib/MyLib.h"
#include "../Collision/Collision.h"


//コンストラクタ
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


//初期化処理
void Player::Init() {
	
	//モデルのロード
	modelHandle = MV1LoadModel("Data/Image/Play/player/player.mv1");
	toolHandle = MV1LoadModel("Data/Image/Play/player/sword.mv1");

	//プレイヤーのエフェクトロード
	effectHandle[PLAYER_EFFECT_ATTACK] = CEffekseerCtrl::LoadData("data/effect/sword.efk");
	effectHandle[PLAYER_EFFECT_SP] = CEffekseerCtrl::LoadData("data/effect/special.efk");
	effectHandle[PLAYER_EFFECT_SP_ATTACK] = CEffekseerCtrl::LoadData("data/effect/exSword.efk");

	//プレイヤーのバックカリングをオフに
	for (int index = 0; index < MV1GetMeshNum(modelHandle); index++) {
		MV1SetMeshBackCulling(modelHandle, index, FALSE);
	}

	//座標初期化
	pos = FIRST_POS;

	//プレイヤーの当たり判定サイズ初期化
	size = PLAYER_SPHERE;

	//プレイヤー体力初期化
	HP = MAX_HP;

	//プレイヤースタミナ初期化
	staminaGauge = MAX_STAMINA_GAUGE;

	//プレイヤーの道具を持つフレーム取得
	frameIndex = MV1SearchFrame(modelHandle, "tool2");

	//アニメーション初期化
	InitAnim(PLAYER_ANIMATION_NUM);
}


//通常処理
void Player::Step() {

	attackHit = false;

	//ヒットストップ
	if (hitStop) {
		hitStopCount++;

		//クリア時ヒットストップ中はエフェクトを止める
		if (hitStopNum == HIT_STOP_CLEAR) {
			CEffekseerCtrl::StopUpdate();
		}
		//指定時間経過でヒットストップ終了
		if (hitStopCount > hitStopNum) {
			hitStopCount = 0;
			hitStop = false;
		}
		return;
	}

	drawDash = false;

	//ダッシュアタックミス時のノックバック
	if (attackMiss) {
		if (curAnim == PLAYER_MISS && animCount < ATTACK_MISS_TIME) {
			pos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_MISS_NUM);
		}
	}
	else {
		if (specialState != SPECIAL_READY && HP > 0) {

			KnockBack();
			//ノックバック中は操作を受け付けない
			if (!damageFlag) {
				Walk();
				Dash();
				Special();
				Attack();
			}

			pos = MyLib::Get3DCircle(pos, 0, rot.y, speed / (float)GameData::GetInstance()->GetGameTime());
		}
	}

	//一定位置以下で初期位置へリセット
	if (pos.y <= PLAYER_MIN_Y) {
		pos = FIRST_POS;
		attackType = PLAYER_ATTACK_NONE;
		HP -= SUB_HP;
	}
	
	//アニメーション処理
	Animation();
		
	//エフェクト処理
	Effect();

	pos.y -= GRAVITY;
	ground = false;
}


//描画処理
void Player::Draw() {

	if (lockOn && nearEneRad != -1) {
		rot.y = nearEneRad;
	}

	MV1SetRotationXYZ(modelHandle, { rot.x,rot.y + MyLib::GetRadian(180),rot.z });
	MV1SetPosition(modelHandle, pos);

	//武器の座標を設定
	toolPos = MV1GetFrameLocalWorldMatrix(modelHandle, frameIndex);
	MV1SetMatrix(toolHandle, toolPos);

	//プレイヤーの描画
	MV1DrawModel(toolHandle);
	MV1DrawModel(modelHandle);
}


//破棄処理
void Player::Delete() {
	DeleteAnim();
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(toolHandle);
}


//歩き処理
void Player::Walk() {

	float rad = 0.0f;

	//歩き移動
	if (!lockOn && !finishDash) {
		speed = 0.0f;

		//コントローラーの移動
		if (PadInput::GetLX() > 0 || PadInput::GetLY() > 0 || PadInput::GetLX() < 0 || PadInput::GetLY() < 0) {
			speed = WALK_SPEED;
			rad = MyLib::GetPosRadian(0, 0, (float)PadInput::GetLY(), (float)PadInput::GetLX());
			rot.y = cameraRot.y + rad;
		}

		//キーボードの入力
		if (Input::Keep(KEY_INPUT_A)) {//左
			speed = WALK_SPEED;
			rad = MyLib::GetRadian(-90);
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_D)) {//右
			speed = WALK_SPEED;
			rad = MyLib::GetRadian(90);
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_W)) {//前
			speed = WALK_SPEED;
			rad -= rad / 2;
			rot.y = cameraRot.y + rad;
		}
		if (Input::Keep(KEY_INPUT_S)) {//後ろ
			speed = WALK_SPEED;
			rot.y = cameraRot.y - rad / 2 + MyLib::GetRadian(180);
		}
	}

	//歩きサウンド
	if (curAnim == PLAYER_WALK) {
		if (animCount == WALK_ANIM_COUNT_1 || animCount == WALK_ANIM_COUNT_2) {
			Sound::Play(P_SE_PLAYER_WALK, false);
		}
	}
}


//走り処理
void Player::Dash() {
	
	//ターゲットがなくなるとダッシュ終了
	if (nearEneRad == -1) {
		lockOn = false;
	}

	//スタミナがなくなるとダッシュ終了、コンボリセット
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

	//ターゲットに向く
	if (nearEneRad != -1) {
		
		rot.y = nearEneRad;
	}

	//ダッシュの切り替え
	if (Input::PushMouse(MOUSE_RIGHT) || PadInput::Push(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		//ダッシュ
		if (!lockOn) {
			lockOn = true;
		}
		else {//ダッシュ終了
			lockOn = false;
			if (avoidType == AVOID_NONE) {
				finishDash = true;
			}
			else {
				finishDash = false;
			}
		}
	}


	//ダッシュ
	if (lockOn) {
		finishDash = false;
		if (combo > 0) {
			drawDash = true;
		}

		//ダッシュ中はスタミナ減少
		staminaGauge -= STAMINA_SUB_NUM;

		//回避処理
		Avoid();

		//回避していなければ走る
		if (avoidType == AVOID_NONE) {

			//コンボ数で走り速度変更
			if (DASH_SPEED + 1 * (combo / MAX_DASH_SPEED_NUM) < MAX_SPEED) {
				currentMaxSpeed = DASH_SPEED + 1.0f * (combo / MAX_DASH_SPEED_NUM);
			}
			else {//速度上限以上にいかないようにする
				currentMaxSpeed = MAX_SPEED;
			}

			//ダッシュの減速値
			dashSub = currentMaxSpeed / SUB_DASH_SPEED;
			
			//ダッシュ中加速
			speed += ADD_DASH_SPEED;
			if (currentMaxSpeed < speed) {
				speed = currentMaxSpeed;
			}
		}
	}
	else {//走っていないとき、スタミナ回復
		staminaGauge += STAMINA_ADD_NUM;

		//スタミナゲージの上限を設定
		if (MAX_STAMINA_GAUGE < staminaGauge) {
			staminaGauge = MAX_STAMINA_GAUGE;
		}

		avoidType = AVOID_NONE;
		avoidCount = 0;
	}

	//ダッシュが終了すると徐々に減速
	if (finishDash) {
		speed -= dashSub;
		if (speed <= 0) {
			finishDash = false;
		}
	}

	//走りサウンド
	if (curAnim == PLAYER_DASH) {
		if (animCount == DASH_ANIM_COUNT_1 || animCount == DASH_ANIM_COUNT_2) {
			Sound::Play(P_SE_PLAYER_DASH, false);
		}
	}
	//走り後のサウンド
	if (curAnim == PLAYER_DASH_AFTER && animCount == 0) {
		Sound::Play(P_SE_PLAYER_DASH_FIN, false);
	}
	if (curAnim != PLAYER_DASH_AFTER) {
		Sound::Stop(P_SE_PLAYER_DASH_FIN);
	}
}


//回避処理
void Player::Avoid() {

	//回避発動処理
	if (attackType == PLAYER_ATTACK_NONE && avoidType == AVOID_NONE) {
		//左
		if (Input::Push(KEY_INPUT_A) || PadInput::GetPushLX() < 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_LEFT;
			invincibleCount = AVOID_INVINCIBLE;
		}
		//右
		if (Input::Push(KEY_INPUT_D) || PadInput::GetPushLX() > 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_RIGHT;
			invincibleCount = AVOID_INVINCIBLE;
		}
		//後ろ
		if (Input::Push(KEY_INPUT_S) || PadInput::GetPushLY() < 0) {
			Sound::Play(P_SE_PLAYER_VOID, false);
			avoidCount = MAX_AVOID_COUNT;
			avoidType = AVOID_BACK;
			invincibleCount = AVOID_INVINCIBLE;
		}
	}

	//回避中の処理
	switch (avoidType) {

	case AVOID_NONE:
		break;

		//左
	case AVOID_LEFT:
		rot.y += MyLib::GetRadian(-90);
		speed = avoidCount;
		avoidCount -= SUB_AVOID_COUNT;
		if (avoidCount <= 0) {
			avoidType = AVOID_NONE;
			avoidCount = 0;
		}
		break;

		//右
	case AVOID_RIGHT:
		rot.y += MyLib::GetRadian(90);
		speed = avoidCount;
		avoidCount -= SUB_AVOID_COUNT;
		if (avoidCount <= 0) {
			avoidType = AVOID_NONE;
			avoidCount = 0;
		}
		break;

		//後ろ
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


//必殺技処理
void Player::Special() {

	switch (specialState) {

	//必殺技の発動
	case SPECIAL_NONE:
		
		//必殺技の条件を満たしていたら
		if (dashAttackCount >= DASH_ATTACK_COUNT_SP_1) {
			if (Input::Push(KEY_INPUT_E) || PadInput::Push(XINPUT_BUTTON_Y)) {
				lockOn = false;

				//プレイヤーを発光
				for (int index = 0; index < PLAYER_MATERIAL_NUM; index++) {
					MV1SetMaterialEmiColor(modelHandle, index, COLOR_RED);
				}

				//必殺技状態をセット
				specialState = SPECIAL_READY;
				specialGauge = MAX_SP_GAUGE;

				//必殺技のレベルに応じて攻撃力をセット
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

	//必殺技予備動作
	case SPECIAL_READY:

		break;

	//必殺技中
	case SPECIAL_ACTIVE:

		specialGauge--;
		invincibleCount = 0;
		//ゲージが無くなると必殺技終了
		if (specialGauge <= 0) {
			specialState = SPECIAL_FINISH;
		}
		break;

	//必殺技の終了
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


//ノックバック処理
void Player::KnockBack() {

	//無敵時間をカウント
	invincibleCount++;
	if (invincibleCount > DAMAGE_INTERVAL / 2) {
		damageFlag = false;
	}
	if (damageFlag) {//ダメージフラグがオンの時、ノックバック
		speed = WALK_SPEED;
		pos.z = MyLib::GetCircleX(pos.z, speed, damageRot);
		pos.x = MyLib::GetCircleY(pos.x, speed, damageRot);
	}
}


//攻撃処理
void Player::Attack() {

	//強化状態のダッシュ攻撃
	if (specialState == SPECIAL_ACTIVE) {
		attackType = PLAYER_ATTACK_SPECIAL;
	}
	if (attackType == PLAYER_ATTACK_SPECIAL) {
		drawDash = true;
		speed = SP_DASH_ATTACK_SPEED;
	}

	
	//攻撃
	if (Input::PushMouse(MOUSE_LEFT) || PadInput::Push(XINPUT_BUTTON_B)) {

		if (attackType == PLAYER_ATTACK_NONE) {
			
			if (!lockOn) {//走っていなかったら通常攻撃
				attackType = PLAYER_ATTACK_NORMAL;
			}
			else {//走っていたらダッシュ攻撃
				attackType = PLAYER_ATTACK_DASH;
				effectRequest = true;
				avoidType = AVOID_NONE;
				avoidCount = 0;
			}

			//剣を振った音
			Sound::Play(P_SE_PLAYER_ATTACK, false);
		}
	}

	//通常攻撃時は移動できない
	if (attackType == PLAYER_ATTACK_NORMAL) {
		speed = 0;
	}

	//攻撃の設定
	switch (curAnim) {

	case PLAYER_NOMAL_ATTACK://通常攻撃
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

	case PLAYER_DASH_ATTACK://ダッシュ攻撃
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

	case PLAYER_DASH_ATTACK_2://強化中のダッシュ攻撃
		attackPos = MyLib::Get3DCircle(pos, 0, rot.y, ATTACK_RANGE);
		hitStopNum = HIT_STOP_SPECIAL;
		attackSize = ATTACK_SIZE_1;
		if (nearEneRad != -1) {
			rot.y = nearEneRad;
		}
		dashAttackCount = 0;
		attackFlag = true;
		break;

	default://非攻撃
		attackFlag = false;
		break;
	}

	//コンボ数に応じて武器が発光
	float combo_color = combo;
	if (combo_color > MAX_SWORD_COLOR) {
		combo_color = MAX_SWORD_COLOR;
	}
	for (int index = 0; index < SWORD_MATERIAL_NUM; index++) {
		MV1SetMaterialEmiColor(toolHandle, index, GetColorF(combo_color / MAX_SWORD_COLOR, 0.0f, 0.0f, 1.0f));
	}

	//時間経過でコンボが消失
	if (comboCount != 0) {
		comboCount--;
		if (comboCount == 0) {
			combo = 0;
		}
	}
}


//アニメーション処理
void Player::Animation() {

	//アニメーションが切り替え終わったら実行
	if (animBlend[curAnim] >= 1.0f) {

		if (HP <= 0) {//プレイヤー倒され
			if (curAnim != PLAYER_DATH) {
				ChangeAnim(PLAYER_DATH);
			}
		}
		else if (specialState == SPECIAL_READY) {//強化状態移行
			if (curAnim != PLAYER_SPECIAL) {
				ChangeAnim(PLAYER_SPECIAL);
			}
		}
		else if (!ground) {//ジャンプ降下
			if (curAnim != PLAYER_AIR) {
				ChangeAnim(PLAYER_AIR);
			}
		}
		else if (specialState == SPECIAL_ACTIVE) {//強化状態ダッシュ攻撃
			if (curAnim != PLAYER_DASH_ATTACK_2) {
				ChangeAnim(PLAYER_DASH_ATTACK_2);
			}
		}
		else if (attackMiss) {//攻撃失敗
			if (curAnim != PLAYER_MISS) {
				ChangeAnim(PLAYER_MISS);
			}
		}
		else if (damageFlag) {//被ダメージ
			if (curAnim != PLAYER_DAMAGE) {
				ChangeAnim(PLAYER_DAMAGE);
			}
		}
		else if (avoidType == AVOID_LEFT) {//左回避
			if (curAnim != PLAYER_LEFT_STEP) {
				ChangeAnim(PLAYER_LEFT_STEP);
			}
		}
		else if (avoidType == AVOID_RIGHT) {//右回避
			if (curAnim != PLAYER_RIGHT_STEP) {
				ChangeAnim(PLAYER_RIGHT_STEP);
			}
		}
		else if (avoidType == AVOID_BACK) {//後ろ回避
			if (curAnim != PLAYER_BACK_STEP) {
				ChangeAnim(PLAYER_BACK_STEP);
			}
		}
		else if (attackType == PLAYER_ATTACK_DASH) {//ダッシュ攻撃
			if (curAnim != PLAYER_DASH_ATTACK) {
				ChangeAnim(PLAYER_DASH_ATTACK);
			}
		}
		else if (finishDash) {//走り後
			if (curAnim != PLAYER_DASH_AFTER) {
				ChangeAnim(PLAYER_DASH_AFTER);
			}
		}
		else if (attackType == PLAYER_ATTACK_NORMAL) {//通常攻撃
			if (curAnim != PLAYER_NOMAL_ATTACK) {
				ChangeAnim(PLAYER_NOMAL_ATTACK);
			}
		}
		else if (lockOn) {//ダッシュ
			if (curAnim != PLAYER_DASH) {
				ChangeAnim(PLAYER_DASH);
			}
		}
		else if (speed <= WALK_SPEED && speed > 0) {//歩き
			if (curAnim != PLAYER_WALK) {
				ChangeAnim(PLAYER_WALK);
			}
		}
		else {
			if (curAnim != PLAYER_IDLE && attackType== PLAYER_ATTACK_NONE) {//待機
				ChangeAnim(PLAYER_IDLE);
			}
		}
	}

	//アニメーションを更新
	UpdateAnim();

	//アニメーションを再生し終えたら
	if (animCount >= animAllTime) {
		if (curAnim == PLAYER_SPECIAL) {
			specialState++;
		}
		else if (curAnim == PLAYER_MISS) {
			attackMiss = false;
		}//ループ
		else if (curAnim != PLAYER_DASH_ATTACK && curAnim != PLAYER_NOMAL_ATTACK) {
			animCount = 0.0f;
		}
		else {
			attackType = PLAYER_ATTACK_NONE;
		}
	}
}


//エフェクト処理
void Player::Effect() {
	
	//ダッシュアタック斬撃
	if (attackType == PLAYER_ATTACK_DASH) {
		if (effectRequest) {
			effectIndex[PLAYER_EFFECT_ATTACK] = CEffekseerCtrl::Request(effectHandle[PLAYER_EFFECT_ATTACK], pos, false);
			effectRequest = false;
		}
		else {//エフェクト位置更新
			CEffekseerCtrl::SetPosition(effectIndex[PLAYER_EFFECT_ATTACK], pos);
			CEffekseerCtrl::SetRot(effectIndex[PLAYER_EFFECT_ATTACK], { rot.x,rot.y - MyLib::GetRadian(90),rot.z });
		}
	}

	//必殺斬撃
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


//クリア時の処理
void Player::clear() {

	rot.y = 0.0f;
	pos = { 0,0,0 };
	//クリアアニメーションに変更
	if (curAnim != PLAYER_CLEAR) {
		ChangeAnim(PLAYER_CLEAR);
	}
	//アニメーションを更新
	UpdateAnim();
	if (animCount >= animAllTime) {
		animCount = animAllTime;
	}
}


//ダメージを受ける
void Player::Damage(VECTOR enemy_pos,int damage){

	//無敵時間が終わっていたら処理
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


//コンボ処理
void Player::Combo() {
	combo++;
	comboCount = COMBO_TIME;
	dashAttackCount++;
	staminaGauge = MAX_STAMINA_GAUGE;
	lockOn = false;
	attackHit = true;
	finishDash = true;
}


//ダッシュ攻撃失敗処理
void Player::AttackMiss() {
	finishDash = false;
	combo = 0;
	attackMiss = true;
	lockOn = false;
	Sound::Play(P_SE_PLAYER_DAMAGE, false);
}


//床についた際の処理
void Player::Ground() { 
	ground = true;
}


//ダメージを受けた瞬間か
bool Player::GetDamage() {

	if (damageFlag && animCount == 0 && PLAYER_DAMAGE) {
		return true;
	}
	else {
		return false;
	}
}


//ダッシュ状態か
bool Player::GetIsDash() {
	if (lockOn && attackType == PLAYER_ATTACK_NONE && avoidType == AVOID_NONE) {
		return true;
	}
	return false;
}


//一番近い敵の角度を得る
float Player::GetEneRad() {
	if (specialState != SPECIAL_NONE) { return -1; }
	return nearEneRad;
}


//一番近い敵との角度をセット
void Player::SetNearEneRad(float ene_rad){
	if (ene_rad != -1) {
		if (ene_rad < 0) {
			ene_rad += MyLib::GetRadian(360);
		}
	}
	nearEneRad = ene_rad;
}


//ヒットストップをオンにする
void Player::SetHitStop(bool max) {
	hitStop = true;
	if (max) {
		hitStopNum = HIT_STOP_CLEAR;
		GameData::GetInstance()->SetGameTime(SLOW_TIME);
	}
}