#include "B.h"

B::B()
{
}

void B::Init(LPDIRECT3DDEVICE9 d3ddv, LPTEXTURE texture)
{
	objectType = 2;
	doing = DOING::Idle;
	status = STATUS::New;
	x = 137;
	y = 300;
	vx = vy = 0;
	anis = new Animations();

	//idle B
	LPSPRITE IdleB = new Sprite(123, 41, 141, 63, texture->LPDIRECT3DTEXTURE());
	//Move B
	LPSPRITE MoveB1 = new Sprite(99, 41, 117, 63, texture->LPDIRECT3DTEXTURE());
	LPSPRITE MoveB2 = new Sprite(147, 41, 165, 63, texture->LPDIRECT3DTEXTURE());

	Animation* B_idle = new Animation();
	B_idle->AddFrame(IdleB, 100);

	Animation* B_move = new Animation();
	B_move->AddFrame(MoveB1, 200);
	B_move->AddFrame(IdleB, 200);
	B_move->AddFrame(MoveB2, 200);

	anis->AddAnimation(B_idle, 0);
	anis->AddAnimation(B_move, 1);
	B_idle->SetRepeat(true);
	B_move->SetRepeat(true);
}

void B::Move(LPD3DXVECTOR2 Target)
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

void B::Up(float d)
{
	Move(new D3DXVECTOR2(x, y - 12));
}

void B::Idle()
{
	doing = DOING::Idle;
	vx = vy = 0;
	this->anis->Start(0);
}

void B::Update(DWORD dt)
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

void B::Render(LPD3DXSPRITE spriteHandler)
{
	if (y < 0) {
		return;
	}
	if (anis != nullptr) {
		anis->Render(D3DXVECTOR2(x, y), spriteHandler);
	}
}


