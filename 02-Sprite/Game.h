#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Textures.h"
#include "Sprites.h"
#include "Animation.h"
#include"A.h"
#include"B.h"
#include"C.h"
#include"GateA.h"
#include"GateB.h"
#include "GateC.h"
#include"Timer.h"
#include"Countdown.h"
#include"NumberShowing.h"
#include<time.h>


#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object
	int delay = 1000;
	int countA = 0, countB = 0, countC = 0;
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 
	LPTEXTURE texture;
	GateA* gA;
	GateB* gB;
	GateC* gC;
	Timer* time;
	NumberShowing* total;
	NumberShowing* passed;
	NumberShowing* passedinA;
	NumberShowing* passedinB;
	NumberShowing* passedinC;
	Countdown* cdA;
	Countdown* cdB;
	Countdown* cdC;
	std::list<Object*> listObj;
	std::vector<Object*> listA;
	std::vector<Object*> listB;
	std::vector<Object*> listC;
	LPD3DXVECTOR2 backpointA;
	LPD3DXVECTOR2 backpointB;
	LPD3DXVECTOR2 backpointC;

public:
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	void LoadResource();
	void Run();
	void Update(DWORD dt);
	void Render();
	void CreateObj(DWORD dt);
	void SelectStack();
	void Up(std::vector<Object*> list, int index);
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame* GetInstance();

	~CGame();
};