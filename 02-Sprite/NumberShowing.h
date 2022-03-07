#pragma once
#include "Text.h"
#include <string>

class NumberShowing
{
private:
	Text* text;
	std::string label;
public:
	float x, y;
	int width = 0, height = 0;
	int value = 0;
	NumberShowing(std::string label, float x, float y, int w, int h);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Render(LPD3DXSPRITE spriteHandler);

};

