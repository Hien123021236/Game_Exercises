#include "A.h"

A::A()
{
}

void A::Init(LPDIRECT3DDEVICE9 d3ddv, LPTEXTURE texture)
{
	objectType = 1;
	doing = DOING::Idle;
	status = STATUS::New;
	x = 137;
	y = 300;
	vx = vy = 0;
	anis = new Animations();
	//LPTEXTURE texture = new Texture(L"hhh.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);
	//idle A
	LPSPRITE IdleA = new Sprite(27, 42, 45, 63, texture->LPDIRECT3DTEXTURE());
	//Move A
	LPSPRITE MoveA1 = new Sprite(3, 43, 21, 63, texture->LPDIRECT3DTEXTURE());
	LPSPRITE MoveA2 = new Sprite(52, 43, 70, 63, texture->LPDIRECT3DTEXTURE());

	Animation* A_idle = new Animation();
	A_idle->AddFrame(IdleA, 100);

	Animation* A_move = new Animation();
	A_move->AddFrame(MoveA1, 200);
	A_move->AddFrame(MoveA2, 200);

	anis->AddAnimation(A_idle, 0);
	anis->AddAnimation(A_move, 1);
	A_idle->SetRepeat(true);
	A_move->SetRepeat(true);
}

void A::Move(LPD3DXVECTOR2 Target)
{
	this->target = Target;
	this->doing = DOING::Move;
	this->anis->Start(1);

	float dx = target->x - this->x;
	float dy = target->y - this->y;

	float vx = vx = 0.1 * dx / sqrt(dx * dx + dy * dy);
	float vy = vy = 0.1 * dy / sqrt(dx * dx + dy * dy);

	this->vx = vx;
	this->vy = vy;
}

void A::Up(float d)
{
	Move(new D3DXVECTOR2(x, y - 12));
}

void A::Idle()
{
	vx = vy = 0;
	this->anis->Start(0);
	this->doing = DOING::Idle;
}

void A::Update(DWORD dt)
{
	if (y < 0) {
		return;
	}
	this->x += vx * dt;
	this->y += vy * dt;

	if (anis != nullptr) {
		anis->Update(dt);
	}


	if (doing == DOING::Move) {
		float distancex = abs(this->x - target->x);
		float distancey = abs(this->y - target->y);
		if (distancex < 5 && distancey < 5) {
			this->Idle();
			x = target->x;
			y = target->y;
			vx = vy = 0;
			Idle();
		}
	}
	else if (doing == DOING::Idle) {
		this->Idle();
	}
}

void A::Render(LPD3DXSPRITE spriteHandler)
{
	if (y < 0) {
		return;
	}
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}

