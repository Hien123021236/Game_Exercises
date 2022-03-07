#pragma once
#include"Textures.h"
#include "Animation.h"
enum STATUS
{
	New,
	Free,
	InStack,
	Wait,
	Leave,
	OutSide
};

enum DOING
{
	Idle,
	Move
};


class Object
{
public:
	LPD3DXVECTOR2 target;
	LPANIMATIONS anis;
	float x, y;
	float vx, vy;
	int doing;
	int status;
	int stt;
	int objectType;
	Object() { anis = nullptr; }
	virtual void Init(LPDIRECT3DDEVICE9 d3ddv, LPTEXTURE texture) = 0;
	virtual void Move(LPD3DXVECTOR2 Target) = 0;
	virtual void Up(float d) = 0;
	virtual void Idle() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render(LPD3DXSPRITE spriteHandler) = 0;
};

