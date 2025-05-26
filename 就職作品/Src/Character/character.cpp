#include "character.h"


//コンストラクタ
Character::Character() {

	modelHandle = 0;

	memset(&pos, 0, sizeof(VECTOR));
	size = 0.0f;

	memset(&attackPos, 0, sizeof(VECTOR));
	attackSize = 0.0f;
	attackPower = 0;

	speed = 0.0f;

	HP = 0;

	animIndex = nullptr;
	curAnim = 0;
	preAnim = 0;
	animBlend = nullptr;
	animNum = 0.0f;
	animCount = 0.0f;
	animAllTime = 0.0f;
}


//アニメーション初期化
void Character::InitAnim(int anim_num) {

	animIndex = new int[anim_num];
	animBlend = new float[anim_num];
	curAnim=0;
	preAnim=1;

	for (int index = 0;index < anim_num;index++) {
		animBlend[index] = 0.0f;
	}

	animIndex[curAnim] = MV1AttachAnim(modelHandle, 0);//アニメーションアタッチ
	animBlend[curAnim] = ANIM_MAX_BLRND;
	animIndex[preAnim] = MV1AttachAnim(modelHandle, 1);//アニメーションアタッチ
	MV1SetAttachAnimBlendRate(modelHandle, animIndex[curAnim], animBlend[curAnim]);
	MV1SetAttachAnimBlendRate(modelHandle, animIndex[preAnim], animBlend[preAnim]);
	animAllTime=MV1GetAttachAnimTotalTime(modelHandle, animIndex[curAnim]);
}


//アニメーション変更
void Character::ChangeAnim(int anim_type) {

	preAnim = curAnim;
	curAnim = anim_type;
	animCount = 0;

	//アニメーションアタッチ
	animIndex[anim_type] = MV1AttachAnim(modelHandle, anim_type);
	
	//アニメーション総再生時間取得
	animAllTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex[curAnim]);
}


//アニメーションの更新
void Character::UpdateAnim() {

	//アニメーション時間の増加量を決定
	animNum = ANIM_COUNT / GameData::GetInstance()->GetGameTime();

	//アニメーションを切り替える
	if (animBlend[curAnim] < ANIM_MAX_BLRND) {

		animBlend[curAnim] += ANIM_BLEND_NUM;
		animBlend[preAnim] -= ANIM_BLEND_NUM;

		//アニメーションのブレンド率をセット
		MV1SetAttachAnimBlendRate(modelHandle, animIndex[curAnim], animBlend[curAnim]);
		MV1SetAttachAnimBlendRate(modelHandle, animIndex[preAnim], animBlend[preAnim]);
	}
	else {//切り替え終えたらアニメーションの時間を進める
		MV1DetachAnim(modelHandle, animIndex[preAnim]);
		animCount += animNum;
		MV1SetAttachAnimTime(modelHandle, animIndex[curAnim], animCount);
	}
}


//アニメーション破棄
void Character::DeleteAnim() {

	delete []animIndex;
	delete []animBlend;
}