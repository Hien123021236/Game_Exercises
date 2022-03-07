#pragma once
#include "Text.h"
#include <ctime>

class Timer
{
public:
	float x, y;
	int h, m, s;
	int delay = 1000;
	int totalTime = 0;
	RECT rTimer;
	Text* txt;
	bool running = true;
	void Start();
	void Stop();
	void Update(DWORD dt);
	void Render(LPD3DXSPRITE spriteHandler);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
};

