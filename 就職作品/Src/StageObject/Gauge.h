#pragma once
#include "../Common.h"
#include "../GameData/gameData.h"


//�X�e�[�W���Ƃ̕K�v�Q�[�W��
constexpr int MAX_GAUGE[STAGE_NUM] = {
	150,
	600,
	1000,
	4000,
	1000
};


//�Q�[�W�N���X
class Gauge {
private:

	int maxGauge;
	int gauge;

public:

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�j��
	void Delete();



	//�Q�[�W�ʂ𓾂�
	int GetGauge() { return gauge; }

	//�ő�̃Q�[�W�ʂ𓾂�
	int GetMaxGauge() { return maxGauge; }

	//�Q�[�W�ʂ��Z�b�g
	void SetGauge(int num) {
		gauge = num;
	}

	//�Q�[�W���L����
	bool GetActive() {
		if (gauge < maxGauge) {
			return true;
		}
		return false;
	}
};