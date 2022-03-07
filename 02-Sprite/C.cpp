#include "C.h"

C::C()
{
}

void C::Init(LPDIRECT3DDEVICE9 d3ddv, LPTEXTURE texture)
{
	objectType = 3;
	doing = DOING::Idle;
	status = STATUS::New;
	x = 137;
	y = 300;

	vx = vy = 0;
	anis = new Animations();

	//idle C
	LPSPRITE IdleC = new Sprite(219, 42, 237, 63, texture->LPDIRECT3DTEXTURE());
	//Move C
	LPSPRITE MoveC1 = new Sprite(195, 43, 213, 64, texture->LPDIRECT3DTEXTURE());
	LPSPRITE MoveC2 = new Sprite(243, 43, 261, 64, texture->LPDIRECT3DTEXTURE());

	Animation* C_idle = new Animation();
	C_idle->AddFrame(IdleC, 100);

	Animation* C_move = new Animation();
	C_move->AddFrame(MoveC1, 200);
	C_move->AddFrame(MoveC2, 200);

	anis->AddAnimation(C_idle, 0);
	anis->AddAnimation(C_move, 1);
	C_idle->SetRepeat(true);
	C_move->SetRepeat(true);
}

void C::Move(LPD3DXVECTOR2 Target)
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

void C::Up(float d)
{
	Move(new D3DXVECTOR2(x, y - 12));
}

void C::Idle()
{

	vx = vy = 0;
	this->anis->Start(0);
	this->doing = DOING::Idle;
}

void C::Update(DWORD dt)
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
		if (distancex < 3 && distancey < 3) {
			this->Idle();
			x = target->x;
			y = target->y;
			vx = vy = 0;
			Idle();
		}
	}


}

void C::Render(LPD3DXSPRITE spriteHandler)
{
	if (y < 0) {
		return;
	}
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}


