#pragma once
#include"Animation.h"
#include"Textures.h"
class GateA
{
private:
	int x, y;
	LPANIMATIONS anis;

public:
	GateA();
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPD3DXSPRITE spriteHandler);
};

