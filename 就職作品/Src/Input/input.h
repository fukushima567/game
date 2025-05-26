#pragma once


#define MOUSE_LEFT (0)

#define MOUSE_RIGHT (1)

//�}�E�X���W
constexpr int MOUSE_NUM = 500;
	
class Input {
public:

	//�C���v�b�g������
	static void Init();

	//�C���v�b�g�ʏ폈��
	static void Step();

	//�������ꂽ
	static bool Push(int key_code);

	//�����ꑱ���Ă���
	static bool Keep(int key_code);

	//�����ꂽ
	static bool Release(int key_code);

	//�}�E�X�N���b�N�������ꂽ
	static bool PushMouse(int mouse_code);

	//�}�E�X�N���b�N������Ă���
	static bool KeepMouse(int mouse_code);

	//�}�E�X�N���b�N�����ꂽ
	static bool ReleaseMouse(int mouse_code);

	//�}�E�X�̈ړ��ʂ𓾂�
	static void GetMouseNum(int* x, int* y);
};