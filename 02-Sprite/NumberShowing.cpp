#include "NumberShowing.h"

NumberShowing::NumberShowing(std::string label, float x, float y, int w, int h)
{
	this->label = label;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}

void NumberShowing::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	text = new Text();
	text->Init(d3ddv);
}

void NumberShowing::Render(LPD3DXSPRITE spriteHandler)
{
	RECT r;
	SetRect(&r, x, y, x + width, y + height);
	text->DrawLabel(this->label + std::to_string(value), r, 1);
}
