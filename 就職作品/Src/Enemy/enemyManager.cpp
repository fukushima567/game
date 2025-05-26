#include "enemyManager.h"
#include "../MyLib/MyLib.h"
#include <fstream>




//�R���X�g���N�^
EnemyManager::EnemyManager() {

	for (int index = 0;index < MAX_ENEMY_NUM + 1;index++) {
		enemy[index] = nullptr;
	}

	memset(&spawnPos,0,sizeof(VECTOR[MAX_ENEMY_NUM]));		

	enemyEffect=0;			
	memset(&spawnCount,0,sizeof(int[MAX_ENEMY_NUM]));

	edit=false;							
	editIndex=0;
}


//������
void EnemyManager::Init() {

	//�X�|�[���n�_�ݒ�p
	edit = false;

	//�G��_���[�W�G�t�F�N�g
	enemyEffect = CEffekseerCtrl::LoadData("data/effect/damage.efk");
	
	enemy[MAX_ENEMY_NUM] = nullptr;

	//�X�e�[�W���Ƃɏo������G������
	int ene_level = 0;
	switch (GameData::GetInstance()->GetStageType()) {
	
	case STAGE_0:
		ene_level = 0;
		break;

	case STAGE_1:
		ene_level = 1;
		break;

	case STAGE_2:
		ene_level = 2;
		break;

	case STAGE_3:
		ene_level = 3;
		break;

	case STAGE_4:
		ene_level = 0;
		enemy[MAX_ENEMY_NUM] = new EnemyBoss;
		enemy[MAX_ENEMY_NUM]->Init();
		break;
	}


	//�G������
	int ene_no = 0;
	for (int index = 0;index < MAX_ENEMY_NUM;index++) {
	
		if (ene_no > ene_level) {
			ene_no = 0;
		}
		switch (ene_no) {
		case 0:
			enemy[index] = new Enemy01;
				break;
		case 1:
			enemy[index] = new Enemy02;
			break;
		case 2:
			enemy[index] = new Enemy03;
			break;
		case 3:
			enemy[index] = new Enemy04;
			break;
		}
		ene_no++;
		
		enemy[index]->Init();
		spawnCount[index] = ENEMY_SPAWN_TIME;
	}

	memset(spawnPos, 0, sizeof(VECTOR[20]));
	editIndex = 0;
	RoadSpawnData();
}


//�G�}�l�[�W���[�ʏ폈��
void EnemyManager::Step(VECTOR player_pos, bool is_spawn,bool is_stop) {

	//�X�|�[���n�_�ݒ�̏���
	if (edit) {
		SpawnEditor();
		return;
	}


	if (!is_spawn) {
		for (int index = 0; index < MAX_ENEMY_NUM; index++) {
			if (!enemy[index]->GetAlive()) { continue; }
			enemy[index]->Damage(999);
			enemy[index]->Step();
		}
	}


	//�G�̃X�|�[������
	for (int index = 0; index < MAX_ENEMY_NUM; index++) {
		if (VSize(spawnPos[index]) == 0) { continue; }
		if (enemy[index]->GetAlive()) { continue; }
		spawnCount[index]++;
		if (spawnCount[index] > ENEMY_SPAWN_TIME) {
			spawnCount[index] = 0;
			enemy[index]->spawn(spawnPos[index]);
		}
	}


	//�G�̏���
	for (int index = 0;index < MAX_ENEMY_NUM;index++) {
		if (!enemy[index]->GetAlive()) { continue; }

		enemy[index]->SetHitStop(is_stop);
		enemy[index]->SetPlayerPos(player_pos);
		enemy[index]->Step();
		

		if (enemy[index]->GetDamageHit()) {
			VECTOR e_p = enemy[index]->GetPos();
			e_p.y += enemy[index]->GetSize()+5;
			CEffekseerCtrl::Request(enemyEffect, e_p, false);
		}
	}

	//�{�X�̏���
	if (enemy[MAX_ENEMY_NUM] != nullptr) {
		enemy[MAX_ENEMY_NUM]->SetPlayerPos(player_pos);
		enemy[MAX_ENEMY_NUM]->Step();
		if (enemy[MAX_ENEMY_NUM]->GetDamageHit2()) {
			VECTOR e_p = enemy[MAX_ENEMY_NUM]->GetPos();
			e_p.y += enemy[MAX_ENEMY_NUM]->GetSize();
			CEffekseerCtrl::Request(enemyEffect, e_p, false);
		}
	}
}



//�G�}�l�[�W���[�`��
void EnemyManager::Draw() {


	//�X�|�[���n�_�ݒ�̕`��
	if (edit) {
		for (int index = 0;index < MAX_ENEMY_NUM;index++) {
			if (index == editIndex) {
				DrawSphere3D(spawnPos[index], 10, 16, GetColor(255,255,0), 200, true);
			}
			else {
				DrawSphere3D(spawnPos[index], 10, 16, 255, 255, true);
			}
		}
		DrawFormatString(500, 0, GetColor(255,0,0), "�I�𒆂̔ԍ�%d", editIndex);
		return;
	}


	//�G�`��
	for (int index = 0; index < MAX_ENEMY_NUM; index++) {
		if (!enemy[index]->GetAlive()) { continue; }
		enemy[index]->Draw();
	}

	if (enemy[MAX_ENEMY_NUM] != nullptr) {
		enemy[MAX_ENEMY_NUM]->Draw();
	}
}


//�j��
void EnemyManager::Delete() {

	for (int index = 0; index < MAX_ENEMY_NUM; index++) {
		enemy[index]->Delete();
	}
	if (enemy[MAX_ENEMY_NUM] != nullptr) {
		enemy[MAX_ENEMY_NUM]->Delete();
	}
}


//�G�X�|�[���n�_�ǂݍ���
void EnemyManager::RoadSpawnData() {

	std::ifstream o_file(SPAWN_PATH[GameData::GetInstance()->GetStageType()], std::ios::binary);
	if (!o_file) {
		return;
	}
	o_file.read(reinterpret_cast<char*>(&spawnPos), sizeof(VECTOR[MAX_ENEMY_NUM]));
	o_file.close();
}


//�G�X�|�[���n�_�̐ݒ�
void EnemyManager::SpawnEditor() {

	int speed = 1;

	if (Input::Keep(KEY_INPUT_RSHIFT)) {
		speed = 10;
	}

	if (Input::Keep(KEY_INPUT_UP)) {
		spawnPos[editIndex].z += speed;
	}
	if (Input::Keep(KEY_INPUT_DOWN)) {
		spawnPos[editIndex].z -= speed;
	}
	if (Input::Keep(KEY_INPUT_LEFT)) {
		spawnPos[editIndex].x -= speed;
	}
	if (Input::Keep(KEY_INPUT_RIGHT)) {
		spawnPos[editIndex].x += speed;
	}

	if (Input::Keep(KEY_INPUT_BACK)) {
		spawnPos[editIndex].x = 0;
		spawnPos[editIndex].y = 0;
		spawnPos[editIndex].z = 0;
	}

	if (Input::Push(KEY_INPUT_SPACE)) {
		editIndex++;
		editIndex %= MAX_ENEMY_NUM;
	}


	//enter�ŏ�������
	if (Input::Push(KEY_INPUT_RETURN)) {
		std::ofstream i_file(SPAWN_PATH[GameData::GetInstance()->GetStageType()], std::ios::binary);
		if (!i_file) {
			return;
		}

		i_file.write(reinterpret_cast<const char*>(&spawnPos), sizeof(VECTOR[MAX_ENEMY_NUM]));
		i_file.close();
	}
}