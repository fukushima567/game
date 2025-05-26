#include "SceneCollision.h"
#include "Collision.h"
#include "../MyLib/MyLib.h"
#include "../../GameData/gameData.h"


//コンストラクタ
SceneCollision::SceneCollision() {
	lockChangeCount = 0;
}


//プレイヤーとステージの当たり判定
void SceneCollision::PlayerAndStage(Player* player, Stage* stage) {

	bool m_isHitFlag = false;

	MV1_COLL_RESULT_POLY_DIM res;
	VECTOR player_pos = player->GetPos();
	player_pos.y += PLAYER_SPHERE * 3;
	float radi = PLAYER_SPHERE * 3;

	//ステージのコリジョン
	res = MV1CollCheck_Sphere(stage->GetStageHandle(), -1, player_pos, radi);
	if (res.HitNum != 0) {
		m_isHitFlag = true;
	}

	//ステージと当たっていたら実行
	if (m_isHitFlag) {

		for (int index = 0; index < res.HitNum; index++) {

			//足元は押し戻ししない
			if (res.Dim[index].HitPosition.y <= player_pos.y - 6) {
				res.Dim[index].Normal.x = 0;
				res.Dim[index].Normal.z = 0;
				if (res.Dim[index].Normal.y > 0.01) {//床判定
					player->Ground();
				}
			}

			//めり込み量を計算
			float radi_1 = 15 + 0;
			float x =std::powf(player_pos.x - res.Dim[index].HitPosition.x, 2.0f);
			float y= std::powf(player_pos.y - res.Dim[index].HitPosition.y, 2.0f);
			float z= std::powf(player_pos.z - res.Dim[index].HitPosition.z, 2.0f);
			float radi_2 = x + y + z;
			radi_1 = radi_1 - sqrtf(radi_2);

			//めり込んでいなかったらやめる
			if (radi_1 <= 0) {
				continue;
			}

			//押し戻し
			VECTOR collision_suv = VScale(res.Dim[index].Normal, radi_1);
			player_pos = VAdd(player_pos, collision_suv);

		}
		//押し戻した座標をセット
		player_pos.y -= PLAYER_SPHERE * 3;
		player->SetPos(player_pos);
	}

	MV1CollResultPolyDimTerminate(res);
}


//敵とステージの当たり判定
void SceneCollision::EnemyAndStage(EnemyManager* enemyManager, Stage* stage) {

	bool m_isHitFlag = false;

	MV1_COLL_RESULT_POLY_DIM res;
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//敵情報を回す
	for (int e_index = 0; e_index < max_ene; e_index++) {
		if (!enemyManager->enemy[e_index]->GetAlive()) { continue; }
		VECTOR enemy_pos = enemyManager->enemy[e_index]->GetPos();
		float radius = enemyManager->enemy[e_index]->GetSize()+5;
		enemy_pos.y += radius;

		res = MV1CollCheck_Sphere(stage->GetStageHandle(), -1, enemy_pos, radius);

		if (res.HitNum != 0) {
			m_isHitFlag = true;
		}

		//ステージと当たっていたら実行
		if (m_isHitFlag) {

			for (int index = 0; index < res.HitNum; index++) {

				if (res.Dim[index].HitPosition.y <= enemy_pos.y - 6) {//足元は押し戻ししない
					res.Dim[index].Normal.x = 0;
					res.Dim[index].Normal.z = 0;
				}

				//めり込み量を計算
				float radi_1 = radius + 0;
				float x = std::powf(enemy_pos.x - res.Dim[index].HitPosition.x, 2.0f);
				float y = std::powf(enemy_pos.y - res.Dim[index].HitPosition.y, 2.0f);
				float z = std::powf(enemy_pos.z - res.Dim[index].HitPosition.z, 2.0f);
				float radi_2 = x + y + z;
				radi_1 = radi_1 - sqrtf(radi_2);

				//めり込んでいなかったらやめる
				if (radi_1 <= 0) {
					continue;
				}

				//押し戻し
				VECTOR collision_suv = VScale(res.Dim[index].Normal, radi_1);
				enemy_pos = VAdd(enemy_pos, collision_suv);
				
			}
			//押し戻した座標をセット
			enemy_pos.y -= radius;
			enemyManager->enemy[e_index]->SetPos(enemy_pos);
			MV1CollResultPolyDimTerminate(res);
		}
	}
}


//敵同士の当たり判定
void SceneCollision::EnemyAndEnemy(EnemyManager* enemyManager) {
	
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//敵情報を回す
	for (int index = 0; index < max_ene; index++) {
		if (enemyManager->enemy[index]->GetHP() <= 0) { continue; }
		VECTOR pos_1 = enemyManager->enemy[index]->GetPos();
		float size_1 = enemyManager->enemy[index]->GetSize();

		for (int index_2 = 0; index_2 < max_ene; index_2++) {
			if (index == index_2) { continue; }
			VECTOR pos_2 = enemyManager->enemy[index_2]->GetPos();
			float size_2 = enemyManager->enemy[index_2]->GetSize();

			//当たっていたら押し戻す
			if (Collision::Sphere(pos_1, pos_2, size_1, size_2)) {
				pos_1 = Collision::SpherePush(pos_1, pos_2, size_1, size_2);
				enemyManager->enemy[index]->SetPos(pos_1);
			}
		}
	}
}


//プレイヤーと敵の当たり判定
void SceneCollision::PlayerAndEnemy(Player* player, EnemyManager* enemyManager) {

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}
	
	//敵情報を回す
	for (int index = 0; index < max_ene; index++) {
		if (enemyManager->enemy[index]->GetHP() <= 0) { continue; }

		VECTOR player_pos = player->GetPos();
		float player_size = player->GetSize();

		VECTOR enemy_pos = enemyManager->enemy[index]->GetPos();
		float enemy_size = enemyManager->enemy[index]->GetSize();


		//当たっているなら当たり判定の処理へ
		if (Collision::Sphere(player_pos, enemy_pos, player_size, enemy_size)) {
			//ダッシュ失敗
			if (player->GetIsDash()) {
				player->AttackMiss();
			}
			else {
				//押し戻し
				player_pos = Collision::SpherePush(player_pos, enemy_pos, player_size, enemy_size);
				player->SetPos(player_pos);
			}
		}
	}
}


//プレイヤーのロックオン判定
void SceneCollision::LockOn(Player* player, EnemyManager* enemyManager, Stage* stage,bool is_lock) {
	
	VECTOR player_pos = player->GetPos();
	
	VECTOR enemy_pos;

	int lock_state = 0;		//ロックオン切り替えの状態
	int lock_index;			//現在ロックオンされている敵の添え字


	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}


	//ロックオンの更新
	bool is_active_lock = false;
	for (int index = 0; index < max_ene; index++) {

		//敵を倒していたらロックオン解除
		if (enemyManager->enemy[index]->GetHP() <= 0) {
			if (enemyManager->enemy[index]->GetLock()) {
				enemyManager->enemy[index]->SetLock(false);
				player->SetNearEneRad(-1);
			}
			continue;
		}
		
		enemy_pos = enemyManager->enemy[index]->GetPos();

		//ロックされている敵の処理
		if (enemyManager->enemy[index]->GetLock()) {
		

			if (is_lock) {//ダッシュ中はロックオン維持
				player->SetNearEneRad(MyLib::GetPosRadian(player_pos.z, player_pos.x, enemy_pos.z, enemy_pos.x));
				is_active_lock = true;
				if (player->GetIsDash()) {

					enemyManager->enemy[index]->SetLock2(true);
					lock_index = index;

					//ロックオンの切り替え
					if (lockChangeCount > LOCK_CAST_TIME) {
						int mouse_x = 0, mouse_y = 0;
						Input::GetMouseNum(&mouse_x, &mouse_y);

						//左へロックオン
						if (mouse_x < -10 || PadInput::GetRX() < -10) {
							lock_state = 1;
						}//右へロックオン
						else if (mouse_x > 10 || PadInput::GetRX() > 10) {
							lock_state = 2;
						}
					}
				}
				break;
			}
			else {//走っていないならロックオンを解除
				enemyManager->enemy[index]->SetLock(false);
				enemyManager->enemy[index]->SetLock2(false);
				is_active_lock = false;
			}
		}
	}

	lockChangeCount++;
	

	//ロックオンの切り替え処理
	if (player->GetIsDash() &&lock_state != 0) {
		lockChangeCount = 0;
		int new_lock_index = -1;
		float cross;
		float pre_cross=10000.0f;

		for (int index = 0; index < max_ene; index++) {
			if (enemyManager->enemy[index]->GetHP() <= 0|| enemyManager->enemy[index]->GetLock2()) { continue; }
			enemy_pos = enemyManager->enemy[index]->GetPos();
			//ロックオン範囲に入っているか
			if (Collision::Sphere(player_pos, enemy_pos, 700, 0) && !Collision::Sphere(player_pos, enemy_pos, 40, 0)) {

				//画面内にいなければ戻る
				VECTOR lock_pos = ConvWorldPosToScreenPos(enemy_pos);
				if (lock_pos.z <= 0.0f || lock_pos.z >= 1.0f) { continue; }

				//プレイヤーと敵の間に障害物があれば戻る
				player_pos.y = 1;
				enemy_pos.y = 1;
				MV1_COLL_RESULT_POLY  res;
				res = MV1CollCheck_Line(stage->GetStageHandle(), -1, player_pos, enemy_pos);
				if (res.HitFlag) { continue; }

				//敵の左右を判定
				cross = MyLib::CalcCross(player_pos, player->GetRot(), enemy_pos);
			
				if (abs(cross) > abs(pre_cross)) { continue; }

				if (lock_state == 1) {
					if (cross > 0) {
						enemyManager->enemy[lock_index]->SetLock(false);
						new_lock_index = index;
					}
				}
				else {
					if (cross < 0) {
						enemyManager->enemy[lock_index]->SetLock(false);
						new_lock_index = index;
					}
				}
				pre_cross = cross;
			}

		}
		//ロックオン対象を決定
		if (new_lock_index != -1) {
			enemyManager->enemy[new_lock_index]->SetLock(true);
		}
	}
	

	//ロックオンされているなら以下実行しない
	if (is_active_lock) { return; }


	float range = -1;
	lock_index = -1;
	
	//ロックオン可能な対象を探す
	for (int index = 0; index < max_ene; index++) {

		if (enemyManager->enemy[index]->GetHP() <= 0) {continue;}
		enemy_pos = enemyManager->enemy[index]->GetPos();

		//必殺技時のロックオン
		if (player->GetSpecialState() == SPECIAL_ACTIVE) {
			if (enemy_pos.y > player_pos.y+10) { continue; }
			VECTOR ran = VSub(player_pos, enemy_pos);
			if (VSize(ran) < range || range == -1) {
				range =  VSize(ran);
				enemyManager->enemy[index]->SetLock(true);
				player->SetNearEneRad(MyLib::GetPosRadian(player_pos.z, player_pos.x, enemy_pos.z, enemy_pos.x));
			}
			if (range == -1) {
				player->SetNearEneRad(-1);
			}
		}
		//通常時のロックオン
		else {

			//ロックオン範囲に入っているか
			if (Collision::Sphere(player_pos, enemy_pos, 700, 0) && !Collision::Sphere(player_pos, enemy_pos, 40, 0)) {

				//プレイヤーに近いY軸にいなければ戻る
				if (enemy_pos.y > player_pos.y + 5) { continue; }

				//画面内にいなければ戻る
				VECTOR lock_pos = ConvWorldPosToScreenPos(enemy_pos);
				if (lock_pos.z <= 0.0f || lock_pos.z >= 1.0f) { continue; }
				
				//プレイヤーと敵の間に障害物があれば戻る
				VECTOR collision_player_pos = player->GetPos();
				collision_player_pos.y = 1;
				VECTOR collision_enemy_pos = enemyManager->enemy[index]->GetPos();
				collision_enemy_pos.y = 1;
				MV1_COLL_RESULT_POLY  res = MV1CollCheck_Line(stage->GetStageHandle(), -1, collision_player_pos, collision_enemy_pos);
				if (res.HitFlag) { continue; }

				//他の敵より画面中央により近ければロッックオン更新
				if (range > MyLib::GetLine(lock_pos.x, lock_pos.y, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y/2) || range == -1) {
					range = MyLib::GetLine(lock_pos.x, lock_pos.y, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y/2);
					enemyManager->enemy[index]->SetLock(true);
					if (lock_index != -1) {
						enemyManager->enemy[lock_index]->SetLock(false);
						enemyManager->enemy[lock_index]->SetLock2(false);
					}
					lock_index = index;
				}
			}
			player->SetNearEneRad(-1);
		}
	}
}


//プレイヤーの攻撃と敵の当たり判定
void SceneCollision::PlayerAttackAndEnemy(Player* player, EnemyManager* enemyManager, Gauge* gauge) {

	//攻撃していなければ実行しない
	if (!player->GetAttackFlag()) {
		return;
	}

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//敵情報を回す
	for (int index = 0; index < max_ene; index++) {

		//敵が攻撃を受ける状態でなければ戻る
		if (enemyManager->enemy[index]->GetHP() <= 0 || enemyManager->enemy[index]->GetDamage()) { continue; }

		VECTOR p_attack_pos= player->GetAttackPos();
		float  p_attack_size = player->GetAttackSize();
		VECTOR e_pos = enemyManager->enemy[index]->GetPos();
		float  e_size = enemyManager->enemy[index]->GetSize();


		//当たっていれば処理へ
		if (Collision::Sphere(p_attack_pos, e_pos, p_attack_size, e_size)) {

			//敵にダメージを与える
			enemyManager->enemy[index]->Damage(player->GetAttackPower());
			enemyManager->enemy[index]->SetKnockBackRad(player->GetRot());

			//ゲージを更新
			float com = player->GetCombo();
			if (player->GetAttackPower() > NOMAL_ATTACK_POWER) {
				com++;
			}
			//ボスは被ダメージでスコア加算
			if (index == MAX_ENEMY_NUM) {
				gauge->SetGauge(gauge->GetGauge() + (int)com * player->GetAttackPower());
			}
			//倒したらポイントを加算
			if (enemyManager->enemy[index]->GetHP()<=0) {
				gauge->SetGauge((int)((float)gauge->GetGauge() + enemyManager->enemy[index]->GetPoint() * (com / 10.0f + 1.0f)));
			}
			
			
			//プレイヤーヒットストップをセット
			player->SetHitStop();
			
			//クリア条件を満たしたら最大ヒットストップ
			if (!gauge->GetActive()) {
				player->SetHitStop(true);
			}

			//ダッシュ攻撃ならコンボ
			if (player->GetAttackPower() > NOMAL_ATTACK_POWER || player->GetSpecialState() != 0) {
				player->Combo();
				Sound::Play(P_SE_PLAYER_HIT_2, false);
			}
			else {//通常攻撃の処理
				Sound::Play(P_SE_PLAYER_HIT_1, false);
			}
		}
	}
}


//プレイヤーと敵の攻撃の当たり判定
void SceneCollision::PlayerAndEnemyAttack(Player* player, EnemyManager* enemyManager) {

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//敵の情報を回す
	for (int index = 0; index < max_ene; index++) {

		//敵が攻撃していないなら戻る
		if (!enemyManager->enemy[index]->GetAttack()) { continue; }

		VECTOR p_pos = player->GetPos();
		float  p_size = player->GetSize();
		VECTOR e_attack_pos = enemyManager->enemy[index]->GetAttackPos();
		float  e_size = enemyManager->enemy[index]->GetSize();

		//当たっていたらダメージを受ける
		if (Collision::Sphere(p_pos,e_attack_pos,p_size,e_size)) {
			player->Damage(enemyManager->enemy[index]->GetPos(), enemyManager->enemy[index]->GetAttackPower());
		}
	}
}


//プレイヤーと敵弾の当たり判定
void SceneCollision::PlayerAndEnemyBullet(Player* player, EnemyManager* enemyManager) {
	
	//敵の全体数を管理する
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//敵の情報を回す
	for (int index = 0; index < max_ene; index++) {

		//敵が弾を使わないなら戻る
		if (!enemyManager->enemy[index]->GetBulletUse()) { continue; }

		//弾情報を回す
		for (int b_index = 0;b_index < ENEMY_MAX_BULLET;b_index++) {

			//弾が出ていないなら戻る
			if (!enemyManager->enemy[index]->GetBulletActive(b_index)) { continue; }

			//弾が当たったらダメージを受ける
			if (Collision::Sphere(player->GetPos(), enemyManager->enemy[index]->GetBulletPos(b_index), player->GetSize(), enemyManager->enemy[index]->GetBulletSize())) {
				Sound::Play(P_SE_PLAYER_DAMAGE, false);
				player->Damage(enemyManager->enemy[index]->GetBulletPos(b_index), enemyManager->enemy[index]->GetAttackPower());
			}
		}
	}
}