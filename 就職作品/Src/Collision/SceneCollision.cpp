#include "SceneCollision.h"
#include "Collision.h"
#include "../MyLib/MyLib.h"
#include "../../GameData/gameData.h"


//�R���X�g���N�^
SceneCollision::SceneCollision() {
	lockChangeCount = 0;
}


//�v���C���[�ƃX�e�[�W�̓����蔻��
void SceneCollision::PlayerAndStage(Player* player, Stage* stage) {

	bool m_isHitFlag = false;

	MV1_COLL_RESULT_POLY_DIM res;
	VECTOR player_pos = player->GetPos();
	player_pos.y += PLAYER_SPHERE * 3;
	float radi = PLAYER_SPHERE * 3;

	//�X�e�[�W�̃R���W����
	res = MV1CollCheck_Sphere(stage->GetStageHandle(), -1, player_pos, radi);
	if (res.HitNum != 0) {
		m_isHitFlag = true;
	}

	//�X�e�[�W�Ɠ������Ă�������s
	if (m_isHitFlag) {

		for (int index = 0; index < res.HitNum; index++) {

			//�����͉����߂����Ȃ�
			if (res.Dim[index].HitPosition.y <= player_pos.y - 6) {
				res.Dim[index].Normal.x = 0;
				res.Dim[index].Normal.z = 0;
				if (res.Dim[index].Normal.y > 0.01) {//������
					player->Ground();
				}
			}

			//�߂荞�ݗʂ��v�Z
			float radi_1 = 15 + 0;
			float x =std::powf(player_pos.x - res.Dim[index].HitPosition.x, 2.0f);
			float y= std::powf(player_pos.y - res.Dim[index].HitPosition.y, 2.0f);
			float z= std::powf(player_pos.z - res.Dim[index].HitPosition.z, 2.0f);
			float radi_2 = x + y + z;
			radi_1 = radi_1 - sqrtf(radi_2);

			//�߂荞��ł��Ȃ��������߂�
			if (radi_1 <= 0) {
				continue;
			}

			//�����߂�
			VECTOR collision_suv = VScale(res.Dim[index].Normal, radi_1);
			player_pos = VAdd(player_pos, collision_suv);

		}
		//�����߂������W���Z�b�g
		player_pos.y -= PLAYER_SPHERE * 3;
		player->SetPos(player_pos);
	}

	MV1CollResultPolyDimTerminate(res);
}


//�G�ƃX�e�[�W�̓����蔻��
void SceneCollision::EnemyAndStage(EnemyManager* enemyManager, Stage* stage) {

	bool m_isHitFlag = false;

	MV1_COLL_RESULT_POLY_DIM res;
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//�G������
	for (int e_index = 0; e_index < max_ene; e_index++) {
		if (!enemyManager->enemy[e_index]->GetAlive()) { continue; }
		VECTOR enemy_pos = enemyManager->enemy[e_index]->GetPos();
		float radius = enemyManager->enemy[e_index]->GetSize()+5;
		enemy_pos.y += radius;

		res = MV1CollCheck_Sphere(stage->GetStageHandle(), -1, enemy_pos, radius);

		if (res.HitNum != 0) {
			m_isHitFlag = true;
		}

		//�X�e�[�W�Ɠ������Ă�������s
		if (m_isHitFlag) {

			for (int index = 0; index < res.HitNum; index++) {

				if (res.Dim[index].HitPosition.y <= enemy_pos.y - 6) {//�����͉����߂����Ȃ�
					res.Dim[index].Normal.x = 0;
					res.Dim[index].Normal.z = 0;
				}

				//�߂荞�ݗʂ��v�Z
				float radi_1 = radius + 0;
				float x = std::powf(enemy_pos.x - res.Dim[index].HitPosition.x, 2.0f);
				float y = std::powf(enemy_pos.y - res.Dim[index].HitPosition.y, 2.0f);
				float z = std::powf(enemy_pos.z - res.Dim[index].HitPosition.z, 2.0f);
				float radi_2 = x + y + z;
				radi_1 = radi_1 - sqrtf(radi_2);

				//�߂荞��ł��Ȃ��������߂�
				if (radi_1 <= 0) {
					continue;
				}

				//�����߂�
				VECTOR collision_suv = VScale(res.Dim[index].Normal, radi_1);
				enemy_pos = VAdd(enemy_pos, collision_suv);
				
			}
			//�����߂������W���Z�b�g
			enemy_pos.y -= radius;
			enemyManager->enemy[e_index]->SetPos(enemy_pos);
			MV1CollResultPolyDimTerminate(res);
		}
	}
}


//�G���m�̓����蔻��
void SceneCollision::EnemyAndEnemy(EnemyManager* enemyManager) {
	
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//�G������
	for (int index = 0; index < max_ene; index++) {
		if (enemyManager->enemy[index]->GetHP() <= 0) { continue; }
		VECTOR pos_1 = enemyManager->enemy[index]->GetPos();
		float size_1 = enemyManager->enemy[index]->GetSize();

		for (int index_2 = 0; index_2 < max_ene; index_2++) {
			if (index == index_2) { continue; }
			VECTOR pos_2 = enemyManager->enemy[index_2]->GetPos();
			float size_2 = enemyManager->enemy[index_2]->GetSize();

			//�������Ă����牟���߂�
			if (Collision::Sphere(pos_1, pos_2, size_1, size_2)) {
				pos_1 = Collision::SpherePush(pos_1, pos_2, size_1, size_2);
				enemyManager->enemy[index]->SetPos(pos_1);
			}
		}
	}
}


//�v���C���[�ƓG�̓����蔻��
void SceneCollision::PlayerAndEnemy(Player* player, EnemyManager* enemyManager) {

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}
	
	//�G������
	for (int index = 0; index < max_ene; index++) {
		if (enemyManager->enemy[index]->GetHP() <= 0) { continue; }

		VECTOR player_pos = player->GetPos();
		float player_size = player->GetSize();

		VECTOR enemy_pos = enemyManager->enemy[index]->GetPos();
		float enemy_size = enemyManager->enemy[index]->GetSize();


		//�������Ă���Ȃ瓖���蔻��̏�����
		if (Collision::Sphere(player_pos, enemy_pos, player_size, enemy_size)) {
			//�_�b�V�����s
			if (player->GetIsDash()) {
				player->AttackMiss();
			}
			else {
				//�����߂�
				player_pos = Collision::SpherePush(player_pos, enemy_pos, player_size, enemy_size);
				player->SetPos(player_pos);
			}
		}
	}
}


//�v���C���[�̃��b�N�I������
void SceneCollision::LockOn(Player* player, EnemyManager* enemyManager, Stage* stage,bool is_lock) {
	
	VECTOR player_pos = player->GetPos();
	
	VECTOR enemy_pos;

	int lock_state = 0;		//���b�N�I���؂�ւ��̏��
	int lock_index;			//���݃��b�N�I������Ă���G�̓Y����


	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}


	//���b�N�I���̍X�V
	bool is_active_lock = false;
	for (int index = 0; index < max_ene; index++) {

		//�G��|���Ă����烍�b�N�I������
		if (enemyManager->enemy[index]->GetHP() <= 0) {
			if (enemyManager->enemy[index]->GetLock()) {
				enemyManager->enemy[index]->SetLock(false);
				player->SetNearEneRad(-1);
			}
			continue;
		}
		
		enemy_pos = enemyManager->enemy[index]->GetPos();

		//���b�N����Ă���G�̏���
		if (enemyManager->enemy[index]->GetLock()) {
		

			if (is_lock) {//�_�b�V�����̓��b�N�I���ێ�
				player->SetNearEneRad(MyLib::GetPosRadian(player_pos.z, player_pos.x, enemy_pos.z, enemy_pos.x));
				is_active_lock = true;
				if (player->GetIsDash()) {

					enemyManager->enemy[index]->SetLock2(true);
					lock_index = index;

					//���b�N�I���̐؂�ւ�
					if (lockChangeCount > LOCK_CAST_TIME) {
						int mouse_x = 0, mouse_y = 0;
						Input::GetMouseNum(&mouse_x, &mouse_y);

						//���փ��b�N�I��
						if (mouse_x < -10 || PadInput::GetRX() < -10) {
							lock_state = 1;
						}//�E�փ��b�N�I��
						else if (mouse_x > 10 || PadInput::GetRX() > 10) {
							lock_state = 2;
						}
					}
				}
				break;
			}
			else {//�����Ă��Ȃ��Ȃ烍�b�N�I��������
				enemyManager->enemy[index]->SetLock(false);
				enemyManager->enemy[index]->SetLock2(false);
				is_active_lock = false;
			}
		}
	}

	lockChangeCount++;
	

	//���b�N�I���̐؂�ւ�����
	if (player->GetIsDash() &&lock_state != 0) {
		lockChangeCount = 0;
		int new_lock_index = -1;
		float cross;
		float pre_cross=10000.0f;

		for (int index = 0; index < max_ene; index++) {
			if (enemyManager->enemy[index]->GetHP() <= 0|| enemyManager->enemy[index]->GetLock2()) { continue; }
			enemy_pos = enemyManager->enemy[index]->GetPos();
			//���b�N�I���͈͂ɓ����Ă��邩
			if (Collision::Sphere(player_pos, enemy_pos, 700, 0) && !Collision::Sphere(player_pos, enemy_pos, 40, 0)) {

				//��ʓ��ɂ��Ȃ���Ζ߂�
				VECTOR lock_pos = ConvWorldPosToScreenPos(enemy_pos);
				if (lock_pos.z <= 0.0f || lock_pos.z >= 1.0f) { continue; }

				//�v���C���[�ƓG�̊Ԃɏ�Q��������Ζ߂�
				player_pos.y = 1;
				enemy_pos.y = 1;
				MV1_COLL_RESULT_POLY  res;
				res = MV1CollCheck_Line(stage->GetStageHandle(), -1, player_pos, enemy_pos);
				if (res.HitFlag) { continue; }

				//�G�̍��E�𔻒�
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
		//���b�N�I���Ώۂ�����
		if (new_lock_index != -1) {
			enemyManager->enemy[new_lock_index]->SetLock(true);
		}
	}
	

	//���b�N�I������Ă���Ȃ�ȉ����s���Ȃ�
	if (is_active_lock) { return; }


	float range = -1;
	lock_index = -1;
	
	//���b�N�I���\�ȑΏۂ�T��
	for (int index = 0; index < max_ene; index++) {

		if (enemyManager->enemy[index]->GetHP() <= 0) {continue;}
		enemy_pos = enemyManager->enemy[index]->GetPos();

		//�K�E�Z���̃��b�N�I��
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
		//�ʏ펞�̃��b�N�I��
		else {

			//���b�N�I���͈͂ɓ����Ă��邩
			if (Collision::Sphere(player_pos, enemy_pos, 700, 0) && !Collision::Sphere(player_pos, enemy_pos, 40, 0)) {

				//�v���C���[�ɋ߂�Y���ɂ��Ȃ���Ζ߂�
				if (enemy_pos.y > player_pos.y + 5) { continue; }

				//��ʓ��ɂ��Ȃ���Ζ߂�
				VECTOR lock_pos = ConvWorldPosToScreenPos(enemy_pos);
				if (lock_pos.z <= 0.0f || lock_pos.z >= 1.0f) { continue; }
				
				//�v���C���[�ƓG�̊Ԃɏ�Q��������Ζ߂�
				VECTOR collision_player_pos = player->GetPos();
				collision_player_pos.y = 1;
				VECTOR collision_enemy_pos = enemyManager->enemy[index]->GetPos();
				collision_enemy_pos.y = 1;
				MV1_COLL_RESULT_POLY  res = MV1CollCheck_Line(stage->GetStageHandle(), -1, collision_player_pos, collision_enemy_pos);
				if (res.HitFlag) { continue; }

				//���̓G����ʒ����ɂ��߂���΃��b�b�N�I���X�V
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


//�v���C���[�̍U���ƓG�̓����蔻��
void SceneCollision::PlayerAttackAndEnemy(Player* player, EnemyManager* enemyManager, Gauge* gauge) {

	//�U�����Ă��Ȃ���Ύ��s���Ȃ�
	if (!player->GetAttackFlag()) {
		return;
	}

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//�G������
	for (int index = 0; index < max_ene; index++) {

		//�G���U�����󂯂��ԂłȂ���Ζ߂�
		if (enemyManager->enemy[index]->GetHP() <= 0 || enemyManager->enemy[index]->GetDamage()) { continue; }

		VECTOR p_attack_pos= player->GetAttackPos();
		float  p_attack_size = player->GetAttackSize();
		VECTOR e_pos = enemyManager->enemy[index]->GetPos();
		float  e_size = enemyManager->enemy[index]->GetSize();


		//�������Ă���Ώ�����
		if (Collision::Sphere(p_attack_pos, e_pos, p_attack_size, e_size)) {

			//�G�Ƀ_���[�W��^����
			enemyManager->enemy[index]->Damage(player->GetAttackPower());
			enemyManager->enemy[index]->SetKnockBackRad(player->GetRot());

			//�Q�[�W���X�V
			float com = player->GetCombo();
			if (player->GetAttackPower() > NOMAL_ATTACK_POWER) {
				com++;
			}
			//�{�X�͔�_���[�W�ŃX�R�A���Z
			if (index == MAX_ENEMY_NUM) {
				gauge->SetGauge(gauge->GetGauge() + (int)com * player->GetAttackPower());
			}
			//�|������|�C���g�����Z
			if (enemyManager->enemy[index]->GetHP()<=0) {
				gauge->SetGauge((int)((float)gauge->GetGauge() + enemyManager->enemy[index]->GetPoint() * (com / 10.0f + 1.0f)));
			}
			
			
			//�v���C���[�q�b�g�X�g�b�v���Z�b�g
			player->SetHitStop();
			
			//�N���A�����𖞂�������ő�q�b�g�X�g�b�v
			if (!gauge->GetActive()) {
				player->SetHitStop(true);
			}

			//�_�b�V���U���Ȃ�R���{
			if (player->GetAttackPower() > NOMAL_ATTACK_POWER || player->GetSpecialState() != 0) {
				player->Combo();
				Sound::Play(P_SE_PLAYER_HIT_2, false);
			}
			else {//�ʏ�U���̏���
				Sound::Play(P_SE_PLAYER_HIT_1, false);
			}
		}
	}
}


//�v���C���[�ƓG�̍U���̓����蔻��
void SceneCollision::PlayerAndEnemyAttack(Player* player, EnemyManager* enemyManager) {

	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//�G�̏�����
	for (int index = 0; index < max_ene; index++) {

		//�G���U�����Ă��Ȃ��Ȃ�߂�
		if (!enemyManager->enemy[index]->GetAttack()) { continue; }

		VECTOR p_pos = player->GetPos();
		float  p_size = player->GetSize();
		VECTOR e_attack_pos = enemyManager->enemy[index]->GetAttackPos();
		float  e_size = enemyManager->enemy[index]->GetSize();

		//�������Ă�����_���[�W���󂯂�
		if (Collision::Sphere(p_pos,e_attack_pos,p_size,e_size)) {
			player->Damage(enemyManager->enemy[index]->GetPos(), enemyManager->enemy[index]->GetAttackPower());
		}
	}
}


//�v���C���[�ƓG�e�̓����蔻��
void SceneCollision::PlayerAndEnemyBullet(Player* player, EnemyManager* enemyManager) {
	
	//�G�̑S�̐����Ǘ�����
	int max_ene = MAX_ENEMY_NUM;
	if (enemyManager->enemy[MAX_ENEMY_NUM] != nullptr) {
		max_ene++;
	}

	//�G�̏�����
	for (int index = 0; index < max_ene; index++) {

		//�G���e���g��Ȃ��Ȃ�߂�
		if (!enemyManager->enemy[index]->GetBulletUse()) { continue; }

		//�e������
		for (int b_index = 0;b_index < ENEMY_MAX_BULLET;b_index++) {

			//�e���o�Ă��Ȃ��Ȃ�߂�
			if (!enemyManager->enemy[index]->GetBulletActive(b_index)) { continue; }

			//�e������������_���[�W���󂯂�
			if (Collision::Sphere(player->GetPos(), enemyManager->enemy[index]->GetBulletPos(b_index), player->GetSize(), enemyManager->enemy[index]->GetBulletSize())) {
				Sound::Play(P_SE_PLAYER_DAMAGE, false);
				player->Damage(enemyManager->enemy[index]->GetBulletPos(b_index), enemyManager->enemy[index]->GetAttackPower());
			}
		}
	}
}