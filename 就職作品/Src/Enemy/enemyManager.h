#pragma once
#include "enemy01.h"
#include "enemy02.h"
#include "enemy03.h"
#include "enemy04.h"
#include "boss.h"


constexpr int MAX_ENEMY_NUM = 20;			//�G�ő�̃X�|�[����
constexpr int ENEMY_SPAWN_TIME = 240;		//�G�X�|�[���܂ł̎���


//�G�X�|�[���f�[�^�p�X��
constexpr char SPAWN_PATH[5][256] = {
	"data/spawn_s0.bin",
	"data/spawn_s1.bin",
	"data/spawn_s2.bin",
	"data/spawn_s3.bin",
	"data/spawn_s4.bin",
};


//�G�}�l�[�W���[�N���X
class EnemyManager {
public:

	Enemy* enemy[MAX_ENEMY_NUM+1];		//�G�x�[�X�N���X
	
private:

	VECTOR spawnPos[MAX_ENEMY_NUM];		//�X�|�[�����W

	int enemyEffect;					//�G�̃G�t�F�N�g
	int spawnCount[MAX_ENEMY_NUM];		//�X�|�[������

	bool edit;							//�X�|�[���f�[�^�쐬�t���O
	int editIndex;						//�X�|�[���f�[�^�I�𒆓Y����

public:

	EnemyManager();
	~EnemyManager(){}

	//������
	void Init();

	//�ʏ폈��
	void Step(VECTOR player_pos, bool is_spawn,bool is_stop);

	//�`�揈��
	void Draw();

	//�j������
	void Delete();
	
private:

	//�X�|�[���f�[�^�̓ǂݍ���
	void RoadSpawnData();

	//�X�|�[���f�[�^�̍쐬
	void SpawnEditor();

};