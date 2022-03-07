#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <d3dx9tex.h>
#include <time.h>

class Text
{
public:
	// Fonts
	ID3DXFont* font;
	HRESULT fontResult;
	RECT rectText;
	std::string message;
	void DrawLabel(std::string, RECT, DWORD);
	bool Init(LPDIRECT3DDEVICE9 d3ddv);
	Text();
	~Text();
};

