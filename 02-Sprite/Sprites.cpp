#include "Sprites.h"



Sprite::Sprite(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	this->border.left = left;
	this->border.right = right;
	this->border.top = top;
	this->border.bottom = bottom;
	this->texture = texture;
	size.x = right - left + 1;
	size.y = bottom - top + 1;
}

RECT Sprite::Border()
{
	return border;
}

D3DXVECTOR2 Sprite::Size()
{
	return size;
}



void Sprite::Draw(D3DXVECTOR2 position, LPD3DXSPRITE spritehandle)
{
	D3DXVECTOR3 p(position.x, position.y, 0);
	spritehandle->Draw(texture, &border, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}


Sprite::~Sprite()
{
}
