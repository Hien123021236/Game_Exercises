#include "GateB.h"

GateB::GateB()
{
}

void GateB::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	x = 125;
	y = 30;
	this->anis = new Animations();
	LPTEXTURE texture = new Texture(L"gate.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);

	LPSPRITE gateB = new Sprite(78, 4, 124, 66, texture->LPDIRECT3DTEXTURE());

	Animation* gate_B = new Animation();
	gate_B->AddFrame(gateB, 100);
	gate_B->SetRepeat(true);
	anis->AddAnimation(gate_B, 0);
	anis->Start(0);
}

void GateB::Update(DWORD dt)
{
	if (anis != nullptr) {
		anis->Update(dt);
	}
}

void GateB::Render(LPD3DXSPRITE spriteHandler)
{
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}
