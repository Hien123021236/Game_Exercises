#pragma once
#include <d3dx9.h>
#include <unordered_map>


class Texture {
private:
	LPDIRECT3DTEXTURE9 texture;
public:
	Texture(LPCWSTR filePath, D3DCOLOR transparentColor, LPDIRECT3DDEVICE9 d3ddv);
	LPDIRECT3DTEXTURE9 LPDIRECT3DTEXTURE();
	~Texture();
};

typedef Texture* LPTEXTURE;