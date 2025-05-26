#pragma once


#define MOUSE_LEFT (0)

#define MOUSE_RIGHT (1)

//マウス座標
constexpr int MOUSE_NUM = 500;
	
class Input {
public:

	//インプット初期化
	static void Init();

	//インプット通常処理
	static void Step();

	//今押された
	static bool Push(int key_code);

	//押され続けている
	static bool Keep(int key_code);

	//離された
	static bool Release(int key_code);

	//マウスクリック今押された
	static bool PushMouse(int mouse_code);

	//マウスクリック押されている
	static bool KeepMouse(int mouse_code);

	//マウスクリック離された
	static bool ReleaseMouse(int mouse_code);

	//マウスの移動量を得る
	static void GetMouseNum(int* x, int* y);
};