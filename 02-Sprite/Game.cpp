#include "debug.h"
#include "Game.h"

CGame* CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/

int ramdom(int min, int max) {
	srand(std::time(NULL));
	return rand() % (max - min + 1) + min;
}

void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void CGame::LoadResource()
{
	this->texture = new Texture(L"hhh.png", D3DCOLOR_XRGB(255, 255, 255), d3ddv);

	listObj = std::list<Object*>();
	listA = std::vector<Object*>();
	listB = std::vector<Object*>();
	listC = std::vector<Object*>();

	backpointA = new D3DXVECTOR2(65, 75);
	backpointB = new D3DXVECTOR2(139, 75);
	backpointC = new D3DXVECTOR2(214, 75);

	this->gA = new GateA();
	gA->Init(d3ddv);

	this->gB = new GateB();
	gB->Init(d3ddv);

	this->gC = new GateC();
	gC->Init(d3ddv);

	this->time = new Timer();
	time->Init(d3ddv);
	time->x = 300;
	time->y = 50;
	time->Start();

	this->total = new NumberShowing("Total: ", 300, 80, 200, 60);
	total->Init(d3ddv);

	this->passed = new NumberShowing("Passed: ", 300, 110, 200, 60);
	passed->Init(d3ddv);

	this->passedinA = new NumberShowing("Passs in A: ", 300, 140, 200, 60);
	passedinA->Init(d3ddv);

	this->passedinB = new NumberShowing("Passs in B: ", 300, 170, 200, 60);
	passedinB->Init(d3ddv);

	this->passedinC = new NumberShowing("Passs in C: ", 300, 200, 200, 60);
	passedinC->Init(d3ddv);

	this->cdA = new Countdown();
	cdA->Init(d3ddv);
	cdA->x = 50;
	cdA->y = 20;

	this->cdB = new Countdown();
	cdB->Init(d3ddv);
	cdB->x = 125;
	cdB->y = 20;

	this->cdC = new Countdown();
	cdC->Init(d3ddv);
	cdC->x = 200;
	cdC->y = 20;
}

void CGame::Run()
{

	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / 60;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Render();
			Update(dt);

		}
		else {
			Sleep(tickPerFrame - dt);
		}

	}
}

void CGame::Update(DWORD dt)
{



	CreateObj(dt);



	backpointA->y = listA.size() * 12 + 75;
	backpointB->y = listB.size() * 12 + 75;
	backpointC->y = listC.size() * 12 + 75;



	//DebugOut(L"pA: y-%d size-%d\n", backpointA->y, listA.size());



	SelectStack();



	/*obj->Move(backpointA);
	listA.push_back(obj);*/
	for each (Object * obj in listObj)    // kiem tra 
	{
		if (obj->status != STATUS::OutSide) {
			if (obj->status == STATUS::Free) { // obj dang di chuyen toi hang cua minh, chua vao hang
				if (abs(obj->x - obj->target->x) < 10 && abs(obj->y - obj->target->y) < 10) // obj da toi hang doi
				{
					if (obj->objectType == 1) // obj la A
					{
						listA.push_back(obj);
						obj->stt = listA.size();
					}
					else
						if (obj->objectType == 2) // obj la B
						{
							listB.push_back(obj);
							obj->stt = listB.size();
						}
						else
							if (obj->objectType == 3) // obj la C
							{
								listC.push_back(obj);
								obj->stt = listC.size();
							}
					obj->status = STATUS::InStack;
					obj->x = obj->target->x;
					obj->y = obj->target->y;
					obj->Idle();
				}
			}



			if (obj->status == STATUS::InStack) { // obj dang trong hang doi
				if (obj->objectType == 1 && listA.size() > 0 && listA.front() == obj) // A 
				{
					cdA->Start(3);
					obj->status = STATUS::Wait;
				}
				else
					if (obj->objectType == 2 && listB.size() > 0 && listB.front() == obj) // B
					{
						cdB->Start(3);
						obj->status = STATUS::Wait;
					}
					else
						if (obj->objectType == 3 && listC.size() > 0 && listC.front() == obj) // C
						{
							cdC->Start(7);
							obj->status = STATUS::Wait;
						}
				obj->status == STATUS::Leave;
			}



			if (obj->status == STATUS::Wait) {
				if (obj->objectType == 1 && listA.size() > 0 && cdA->value <= 0)  // A
				{
					obj->Move(new D3DXVECTOR2(65, -100));
					obj->status = STATUS::Leave;
					passedinA->value++;
					listA.erase(listA.begin());
					if (listA.size() > 0) {
						Up(listA, 0);
						listA[0]->status = STATUS::Wait;
						cdA->Start(ramdom(2, 3));
					}
				}
				else
					if (obj->objectType == 2 && listB.size() > 0 && cdB->value <= 0) // B
					{
						obj->Move(new D3DXVECTOR2(139, -100));
						obj->status = STATUS::Leave;
						passedinB->value++;
						listB.erase(listB.begin());
						if (listB.size() > 0) {
							Up(listB, 0);
							listB[0]->status = STATUS::Wait;
							cdB->Start(ramdom(1, 4));
						}
					}
					else
						if (obj->objectType == 3 && listC.size() > 0 && cdC->value <= 0) // C
						{
							obj->Move(new D3DXVECTOR2(214, -100));
							obj->status = STATUS::Leave;
							passedinC->value++;
							listC.erase(listC.begin());
							if (listC.size() > 0) {
								Up(listC, 0);
								listC[0]->status = STATUS::Wait;
								cdC->Start(ramdom(3, 7));
							}



						}
			}

			if (obj->status == STATUS::Leave) { // obj da qua cong
				if (obj->y < -50)
					obj->status = STATUS::OutSide;
			}
		}



		obj->Update(dt);
	}



	gA->Update(dt);
	gB->Update(dt);
	gC->Update(dt);



	cdA->Update(dt);
	cdB->Update(dt);
	cdC->Update(dt);



	time->Update(dt);



	passed->value = passedinA->value + passedinB->value + passedinC->value;




}

void CGame::Render()
{
	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(this->backBuffer, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for each (Object * obj in listObj)
		{
			obj->Render(spriteHandler);
		}
		gA->Render(spriteHandler);
		gB->Render(spriteHandler);
		gC->Render(spriteHandler);

		cdA->Render(spriteHandler);
		cdB->Render(spriteHandler);
		cdC->Render(spriteHandler);

		time->Render(spriteHandler);
		total->Render(spriteHandler);
		passed->Render(spriteHandler);
		passedinA->Render(spriteHandler);
		passedinB->Render(spriteHandler);
		passedinC->Render(spriteHandler);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}


void CGame::CreateObj(DWORD dt)
{
	delay -= dt;
	if (delay <= 0) {
		this->total->value++;
		delay = 2000;
		Object* obj = nullptr;

		srand(std::time(NULL));
		//DebugOut(L"%d\n", std::time(NULL));

		int ran = rand() % 10;
		if (ran == 0) {
			obj = new A();
			obj->Init(d3ddv, texture);
			countA++;
		}
		else if (ran > 0 && ran < 4) {
			obj = new B();
			obj->Init(d3ddv, texture);
			countB++;
		}
		else {
			obj = new C();
			obj->Init(d3ddv, texture);
			countC++;
		}

		this->listObj.push_back(obj);
	}
}
void CGame::SelectStack() {
	for each (Object * obj in listObj)
	{
		if (obj->status == STATUS::New) {
			if (obj->objectType == 1) {
				obj->Move(backpointA);
				obj->status = STATUS::Free;
			}
			else
				if (obj->objectType == 2) {
					obj->Move(backpointB);
					obj->status = STATUS::Free;
				}
				else
					if (obj->objectType == 3) {
						obj->Move(backpointC);
						obj->status = STATUS::Free;
					}
		}
		else
			if (obj->status == STATUS::Free) {
				if (listA.size() == 0 && listB.size() > 0 && listC.size() > 0) {
					obj->Move(backpointA);
					obj->objectType = 1;
				}
				else
					if (listA.size() > 0 && listB.size() == 0 && listC.size() > 1) {
						obj->Move(backpointB);
						obj->objectType = 2;
					}
					else
						if (listA.size() > 0 && listB.size() > 0 && listC.size() == 0) {
							obj->Move(backpointC);
							obj->objectType = 3;
						}
			}

		else
		if (obj->status == STATUS::InStack) {       
		    if (obj->objectType == 1 && obj->stt == 2) {
		        if (listB.size() <= 0) {
		            obj->Move(backpointB);
		            listA.erase(listA.begin() + obj->stt - 1);
		            obj->objectType = 2;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        else
		        if (listC.size() <= 0) {
		            obj->Move(backpointC);
		            listA.erase(listA.begin() + obj->stt - 1);
		            obj->objectType = 3;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        //Up(listA, obj->stt);
		    }
		    else
		    if (obj->objectType == 2 && obj->stt == 2) {
		        if (listA.size() <= 0) {
		            obj->Move(backpointA);
		            listB.erase(listB.begin() + obj->stt - 1);
		            obj->objectType = 1;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        else
		        if (listC.size() <= 0) {
		            obj->Move(backpointC);
		            listB.erase(listB.begin() + obj->stt - 1);
		            obj->objectType = 3;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        //Up(listB, obj->stt);
		    }
		    else
		    if (obj->objectType == 3 && obj->stt == 2) {
		        if (listA.size() <= 0) {
		            obj->Move(backpointA);
		            listC.erase(listC.begin() + obj->stt - 1);
		            obj->objectType = 1;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        else
		        if (listB.size() <= 0) {
		            obj->Move(backpointB);
		            listC.erase(listC.begin() + obj->stt - 1);
		            obj->objectType = 2;
		            obj->status = STATUS::Free;
		            //DebugOut(L"GO\n");
		        }
		        //Up(listC, obj->stt);
		    }

		}
		DebugOut(L"GO %d %d %d\n", listA.size(), listB.size(), listC.size());
	}
}

//void CGame::SelectStack()
//{
//	for each (Object * obj in listObj)
//	{
//		if (obj->status == STATUS::New) {
//			if (obj->objectType == 1) {
//				obj->Move(backpointA);
//				obj->status = STATUS::Free;
//			}
//			else
//				if (obj->objectType == 2) {
//					obj->Move(backpointB);
//					obj->status = STATUS::Free;
//				}
//				else
//					if (obj->objectType == 3) {
//						obj->Move(backpointC);
//						obj->status = STATUS::Free;
//					}
//		}
//	}
//}


void CGame::Up(std::vector<Object*> list, int index)
{
	if (list.size() > 0) {
		for (int i = index; i < list.size(); i++) {
			list[i]->Up(12);
		}
	}
}

/*
	Utility function to load texture
*/


CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}


CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}


