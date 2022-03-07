#include "Timer.h"
#include"debug.h"

void Timer::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	txt = new Text();
	txt->Init(d3ddv);
}


void Timer::Start()
{
	running = true;
}


void Timer::Update(DWORD dt)
{
	if (running) {
		totalTime += dt;
		delay -= dt;
		h = totalTime / 3600000;
		m = (totalTime % 3600000) / 60000;
		s = (totalTime % 60000) / 1000;
	}

}

void Timer::Render(LPD3DXSPRITE spriteHandler)
{
	SetRect(&rTimer, x, y, x + 120, y + 60);
	txt->DrawLabel(std::string("TIME : " + std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s)), rTimer, DT_LEFT);
}


