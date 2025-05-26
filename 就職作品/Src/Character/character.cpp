#include "character.h"


//�R���X�g���N�^
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


//�A�j���[�V����������
void Character::InitAnim(int anim_num) {

	animIndex = new int[anim_num];
	animBlend = new float[anim_num];
	curAnim=0;
	preAnim=1;

	for (int index = 0;index < anim_num;index++) {
		animBlend[index] = 0.0f;
	}

	animIndex[curAnim] = MV1AttachAnim(modelHandle, 0);//�A�j���[�V�����A�^�b�`
	animBlend[curAnim] = ANIM_MAX_BLRND;
	animIndex[preAnim] = MV1AttachAnim(modelHandle, 1);//�A�j���[�V�����A�^�b�`
	MV1SetAttachAnimBlendRate(modelHandle, animIndex[curAnim], animBlend[curAnim]);
	MV1SetAttachAnimBlendRate(modelHandle, animIndex[preAnim], animBlend[preAnim]);
	animAllTime=MV1GetAttachAnimTotalTime(modelHandle, animIndex[curAnim]);
}


//�A�j���[�V�����ύX
void Character::ChangeAnim(int anim_type) {

	preAnim = curAnim;
	curAnim = anim_type;
	animCount = 0;

	//�A�j���[�V�����A�^�b�`
	animIndex[anim_type] = MV1AttachAnim(modelHandle, anim_type);
	
	//�A�j���[�V�������Đ����Ԏ擾
	animAllTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex[curAnim]);
}


//�A�j���[�V�����̍X�V
void Character::UpdateAnim() {

	//�A�j���[�V�������Ԃ̑����ʂ�����
	animNum = ANIM_COUNT / GameData::GetInstance()->GetGameTime();

	//�A�j���[�V������؂�ւ���
	if (animBlend[curAnim] < ANIM_MAX_BLRND) {

		animBlend[curAnim] += ANIM_BLEND_NUM;
		animBlend[preAnim] -= ANIM_BLEND_NUM;

		//�A�j���[�V�����̃u�����h�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, animIndex[curAnim], animBlend[curAnim]);
		MV1SetAttachAnimBlendRate(modelHandle, animIndex[preAnim], animBlend[preAnim]);
	}
	else {//�؂�ւ��I������A�j���[�V�����̎��Ԃ�i�߂�
		MV1DetachAnim(modelHandle, animIndex[preAnim]);
		animCount += animNum;
		MV1SetAttachAnimTime(modelHandle, animIndex[curAnim], animCount);
	}
}


//�A�j���[�V�����j��
void Character::DeleteAnim() {

	delete []animIndex;
	delete []animBlend;
}