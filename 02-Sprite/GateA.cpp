#include "GateA.h"

GateA::GateA()
{
}

void GateA::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	x = 50;
	y = 30;
	this->anis = new Animations();
	LPTEXTURE texture = new Texture(L"gate.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);

	LPSPRITE gateA = new Sprite(11, 4, 57, 66, texture->LPDIRECT3DTEXTURE());

	Animation* gate_A = new Animation();
	gate_A->AddFrame(gateA, 100);
	gate_A->SetRepeat(true);
	anis->AddAnimation(gate_A, 0);
	anis->Start(0);
}

void GateA::Update(DWORD dt)
{
	if (anis != nullptr) {
		anis->Update(dt);
	}
}

void GateA::Render(LPD3DXSPRITE spriteHandler)
{
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}
