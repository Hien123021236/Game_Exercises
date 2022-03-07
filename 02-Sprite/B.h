#pragma once
#include"Animation.h"
#include"Object.h"
class B : public Object
{
public:
	B();
	void Init(LPDIRECT3DDEVICE9 d3ddv, LPTEXTURE texture);
	void Move(LPD3DXVECTOR2 Target);
	void Up(float d);
	void Idle();
	void Update(DWORD dt);
	void Render(LPD3DXSPRITE spriteHandler);
};


