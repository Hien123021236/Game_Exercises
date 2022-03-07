#include "Countdown.h"

Countdown::Countdown()
{

}

void Countdown::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	this->tex = new Texture(L"countdown.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);
	this->sp1 = new Sprite(0, 66, 12, 74, tex->LPDIRECT3DTEXTURE());
	this->sp2 = new Sprite(0, 55, 22, 63, tex->LPDIRECT3DTEXTURE());
	this->sp3 = new Sprite(0, 44, 32, 52, tex->LPDIRECT3DTEXTURE());
	this->sp4 = new Sprite(0, 33, 42, 41, tex->LPDIRECT3DTEXTURE());
	this->sp5 = new Sprite(0, 22, 52, 30, tex->LPDIRECT3DTEXTURE());
	this->sp6 = new Sprite(0, 11, 62, 19, tex->LPDIRECT3DTEXTURE());
	this->sp7 = new Sprite(0, 0, 72, 8, tex->LPDIRECT3DTEXTURE());
	this->running = false;
	this->delay = 1000;
}

void Countdown::Start(int max)
{
	this->value = max;
	this->running = true;
}

void Countdown::Update(DWORD dt)
{
	if (running) {
		delay -= dt;
		if (delay <= 0) {
			delay = 1000;
			value--;
		}
	}
}

void Countdown::Render(LPD3DXSPRITE spriteHandler)
{
	switch (value)
	{
	case 1:
		sp1->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 2:
		sp2->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 3:
		sp3->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 4:
		sp4->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 5:
		sp5->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 6:
		sp6->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;
	case 7:
		sp7->Draw(D3DXVECTOR2(x, y), spriteHandler);
		break;

	default:

		break;
	}
}

