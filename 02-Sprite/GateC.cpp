#include "GateC.h"

GateC::GateC()
{
}

void GateC::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	x = 200;
	y = 30;
	this->anis = new Animations();
	LPTEXTURE texture = new Texture(L"gate.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);

	LPSPRITE gateC = new Sprite(144, 4, 190, 66, texture->LPDIRECT3DTEXTURE());

	Animation* gate_C = new Animation();
	gate_C->AddFrame(gateC, 100);
	gate_C->SetRepeat(true);
	anis->AddAnimation(gate_C, 0);
	anis->Start(0);
}

void GateC::Update(DWORD dt)
{
	if (anis != nullptr) {
		anis->Update(dt);
	}
}

void GateC::Render(LPD3DXSPRITE spriteHandler)
{
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}

