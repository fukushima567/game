#include "../Common.h"


constexpr int SWORD_EFFECT_NUM = 9;
constexpr int DASH_EFFECT_NUM = 4;


//�X�N���[���G�t�F�N�g�N���X
class ScreenEffect {
private:

	//���̃G�t�F�N�g�֌W
	int swordEffeHandle[SWORD_EFFECT_NUM];
	int swordEffeIndex;
	int swordEffeCount;
	bool swordEffeActive;

	//���̃G�t�F�N�g�֌W
	int windCount;
	int dashWindHandle[DASH_EFFECT_NUM];
	int windHandleIndex;
	int screenHandle;
	int wind_alpha;
	int white_alpha;
	int fadeAlpha;

public:

	ScreenEffect();
	~ScreenEffect(){}

	//������
	void Init();

	//�j��
	void Delete();

	//�_�b�V�����̉�ʉ��o
	void DashEffect(float speed, bool draw);

	//���q�b�g���̉�ʉ��o
	void SwordEffect(bool request);

	//�ڂ���
	void GaussEffect();

	//��ʗh��
	void ShakeScreen();

	//�t�F�[�h�C��
	bool FadeIn(bool black=true);

	//�t�F�[�h�A�E�g
	bool FadeOut(bool black = true);
};