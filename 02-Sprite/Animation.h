#pragma once
#include <unordered_map>
#include "Sprites.h"

class AnimationFrame {
public:
	LPSPRITE sprite;
	DWORD time;
	D3DXVECTOR2 size;
	AnimationFrame(LPSPRITE sprite, DWORD dtime);
	AnimationFrame(LPSPRITE sprite, DWORD dtime, D3DXVECTOR2 size);
	~AnimationFrame();
};

typedef AnimationFrame* PLANIMATIONFRAME;

class Animation
{
private:
	std::vector<PLANIMATIONFRAME> frames;
	unsigned int begin, end;
	bool isRepeat;
	bool isDone;
	bool isDoing;
	bool continues = true;
	int curFrameID;
	DWORD time;
public:
	Animation();
	bool IsRepeat();
	bool IsDoing();
	void SetRepeat(bool repeat); //Xét animation có lặp lại ko
	void SetRepeat(unsigned int begin, unsigned int end); //xét lặp lại từ begin->end
	void AddFrame(LPSPRITE sprite, DWORD dtime);
	unsigned int GetCurrentFrameID();

	void Start();
	void Start(unsigned int frameID, bool contrinues = true);
	void Restart();
	void Stop();
	float Height();
	float Width();
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler);
	~Animation();
};
typedef Animation* LPANIMATION;


class Animations {
private:
	std::unordered_map<int, LPANIMATION> animations;
	int curAnimationID;
	int nextAnimationID;
	bool continues = true;
public:
	Animations();
	int GetCurrentAnimationID();
	void AddAnimation(LPANIMATION animation, unsigned int animationID);
	void Start(unsigned int animationID);
	void Start(unsigned int animationID, unsigned int frameID, bool continues = true);
	void Restart(unsigned int animationID);
	void Switch(unsigned int animationID);
	void Stop(unsigned int animationID);
	LPANIMATION GetCurrentAnimation();
	float Height();
	float Width();
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler);
	~Animations();
};

typedef Animations* LPANIMATIONS;

