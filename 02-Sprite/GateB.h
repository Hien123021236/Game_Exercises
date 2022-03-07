#pragma once
#include"Animation.h"
#include"Textures.h"
class GateB
{
private:
	int x, y;
	LPANIMATIONS anis;
public:
	GateB();
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPD3DXSPRITE spriteHandler);
};

