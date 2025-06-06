#pragma once
#include "../Common.h"
#include "enemy.h"


//GÖW
constexpr float	ENEMY_02_POINT = 30.0f;					//G2Ì|Cg

//eÖW
constexpr int	ENEMY_02_MAX_BULLET = 3;				//G2ÌeÅå
constexpr int	ENEMY_02_BULLET_INTERVAL = 10;			//G2ÌeC^[o
constexpr float ENEMY_02_BULLET_SIZE = 20.0f;			//G2eÌTCY
constexpr float ENEMY_02_BULLET_MOVE_SPEED = 5.0f;		//G2eÚ®¬x
constexpr float ENEMY_02_BULLET_Y_POS = 16.0f;			//G2eYÀW
constexpr float ENEMY_02_BULLET_START_TIME = 40.0f;		//G2e­ËAjÔ
constexpr float ENEMY_02_BULLET_FIN_TIME = 30.0f;		//G2eÁÅAjÔ(1ÂOÌU)



//G02NX
class Enemy02 :public Enemy {
private:

	float bulletRadian;

	
public:

	Enemy02();
	~Enemy02(){}

	//ú»
	void Init();

	//Êí
	void Step();

	//`æ
	void Draw();

	//jü	
	void Delete();

private:

	//U
	void Attack();

	//eÌ
	void Bullet();

	//Aj[V
	void Animation();

public:

	//UÌÅ©
	bool GetAttack();

	//X|[
	void spawn(VECTOR spawn_pos);
};