#pragma once
#include "Textures.h"
#include "Sprites.h"

class Countdown
{
private:
	LPTEXTURE tex;
	bool running;
	int delay;
	LPSPRITE sp1;
	LPSPRITE sp2;
	LPSPRITE sp3;
	LPSPRITE sp4;
	LPSPRITE sp5;
	LPSPRITE sp6;
	LPSPRITE sp7;
public:
	int x, y;
	int value = -1;
	Countdown();
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Start(int max);
	virtual void Update(DWORD dt);
	virtual void Render(LPD3DXSPRITE spriteHandler);

};



