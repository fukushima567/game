#pragma once

#include "../Player/player.h"
#include "../Enemy/enemyManager.h"
#include "../StageObject/gauge.h"
#include "../StageObject/stage.h"
#include "../Camera/cameraManager.h"


constexpr int LOCK_CAST_TIME = 20;		//���b�N�I���؂�ւ��̃N�[���^�C��


//�v���C�V�[���̓����蔻��
class SceneCollision {

private:

	int lockChangeCount;	//���b�N�I���؂�ւ��J�E���g

public:

	SceneCollision();
	~SceneCollision(){}

	//�v���C���[�ƃX�e�[�W�̓����蔻��
	void PlayerAndStage(Player* player, Stage* stage);

	//�G�ƃX�e�[�W�̓����蔻��
	void EnemyAndStage(EnemyManager* enemyManager,Stage* stage);

	//�G���m�̓����蔻��
	void EnemyAndEnemy(EnemyManager* enemyManager);

	//�v���C���[�ƓG�̓����蔻��
	void PlayerAndEnemy(Player *player,EnemyManager *enemyManager);

	//�v���C���[�̃��b�N�I������
	void LockOn(Player* player, EnemyManager* enemyManager ,Stage* stage,bool is_lock);

	//�v���C���[�̍U���ƓG�̓����蔻��
	void PlayerAttackAndEnemy(Player* player, EnemyManager* enemyManager, Gauge* gauge);

	//�v���C���[�ƓG�̍U���̓����蔻��
	void PlayerAndEnemyAttack(Player* player, EnemyManager* enemyManager);

	//�v���C���[�ƓG�e�̓����蔻��
	void PlayerAndEnemyBullet(Player* player, EnemyManager* enemyManager);
};