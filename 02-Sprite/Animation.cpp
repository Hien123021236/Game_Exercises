#include "Animation.h"
#include "Debug.h"


AnimationFrame::AnimationFrame(LPSPRITE sprite, DWORD time)
{
	this->sprite = sprite;
	this->time = time;
	this->size = D3DXVECTOR2(0, 0);
	this->size = sprite->Size();

}

AnimationFrame::AnimationFrame(LPSPRITE sprite, DWORD dtime, D3DXVECTOR2 size)
{
	this->sprite = sprite;
	this->time = time;
	this->size = D3DXVECTOR2(0, 0);
	this->size = size;
}

AnimationFrame::~AnimationFrame()
{
}


Animation::Animation()
{
	frames.clear();
	begin = 0;
	end = 0;
	isRepeat = false;
	isDoing = false;
	curFrameID = 0;
	time = 0;
}

bool Animation::IsDoing()
{
	return isDoing;
}



bool Animation::IsRepeat()
{
	return isRepeat;
}


void Animation::SetRepeat(bool repeat)
{
	if (repeat == true) {
		if (frames.size() > 0) {
			isRepeat = true;
			begin = 0;
			end = frames.size() - 1;
		}
		else
		{
			DebugOut(L"[Warnning]Animation::SetRepeat(bool): don't have sprite in sprites\n");
		}
	}
	else
	{
		this->isRepeat = false;
	}
}

void Animation::SetRepeat(unsigned int begin, unsigned int end)
{
	if (begin >= 0 && end < frames.size()) {
		isRepeat = true;
		this->begin = begin;
		this->end = end;
	}
	else
	{
		DebugOut(L"[Warnning]Animation::SetRepeat(unsigned int, unsigned int): There is an index out range the array\n");
	}
}

void Animation::AddFrame(LPSPRITE sprite, DWORD dtime)
{
	if (sprite != nullptr) {
		PLANIMATIONFRAME frame;
		if (this->frames.size() == 0)
			frame = new AnimationFrame(sprite, dtime);
		else
			frame = new AnimationFrame(sprite, frames.back()->time + dtime);

		frames.push_back(frame);
	}
}

unsigned int Animation::GetCurrentFrameID()
{
	return this->curFrameID;
}



void Animation::Start()
{
	if (this->frames.size() > 0 && isDoing == false) {
		curFrameID = 0;
		isDoing = true;
		time = 0;
	}
}

void Animation::Start(unsigned int frameID, bool contrinues)
{
	if (this->frames.size() > 0) {
		this->continues = continues;
		if (continues && isDoing == false) {
			curFrameID = frameID;
			isDoing = true;
			time = frames[curFrameID]->time;
		}
		if (!continues) {
			curFrameID = frameID;
			isDoing = true;
			time = frames[curFrameID]->time;
		}
	}
}

void Animation::Restart()
{
	if (this->frames.size() > 0 && isDoing == true) {
		curFrameID = 0;
		isDoing = true;
		time = 0;
	}
	else
	{
		//DebugOut(L"[Warnning]Animation::Restart(): can't restart\n");
	}
}


void Animation::Stop()
{
	if (this != nullptr) {
		this->curFrameID = 0;
		isDoing = false;
	}
}

float Animation::Height()
{
	if (curFrameID >= 0 && frames.size() > 0)
		return this->frames[curFrameID]->size.y;
	else
		return 0.0f;
}

float Animation::Width()
{
	if (curFrameID >= 0 && frames.size() > 0)
		return this->frames[curFrameID]->size.x;
	else
		return 0.0f;
}

void Animation::Update(DWORD dt)
{
	if (isDoing == true) {

		curFrameID = (time > frames[curFrameID]->time) ? (curFrameID + 1) : (curFrameID);
		if (isRepeat == false) {
			if (curFrameID >= frames.size()) {
				curFrameID = (frames.size() - 1);
				isDoing = false;
			}
		}
		else {
			time = (curFrameID > end) ? (0) : (time);
			curFrameID = (curFrameID > end) ? (begin) : (curFrameID);
		}

		time = time += dt;
	}
}



void Animation::Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler)
{
	if (this->frames.size() > 0 && curFrameID >= 0) {

		frames[curFrameID]->sprite->Draw(pos, spriteHandler);
	}
}





Animation::~Animation()
{
}


Animations::Animations()
{
	animations.clear();
	curAnimationID = -1;
}

int Animations::GetCurrentAnimationID()
{
	return curAnimationID;
}

void Animations::AddAnimation(LPANIMATION animation, unsigned int animationID)
{
	animations[animationID] = animation;
}

void Animations::Start(unsigned int animationID)
{
	if (animationID >= 0 && animationID < animations.size()) {
		if (curAnimationID != animationID)
		{
			this->animations[curAnimationID]->Stop();
			this->curAnimationID = animationID;
			this->animations.at(animationID)->Start();
		}
	}
}

void Animations::Start(unsigned int animationID, unsigned int frameID, bool continues)
{
	if (animationID >= 0 && animationID < animations.size()) {
		if (curAnimationID != animationID)
		{
			this->continues = continues;
			this->animations[curAnimationID]->Stop();
			this->curAnimationID = animationID;
			this->animations.at(animationID)->Start(frameID);
		}
	}
}

void Animations::Restart(unsigned int animationID)
{
	if (animationID >= 0 && animationID < animations.size()) {
		if (curAnimationID == animationID) {
			this->curAnimationID = animationID;
			animations.at(animationID)->Restart();
		}
	}
}

void Animations::Switch(unsigned int animationID)
{

}

void Animations::Stop(unsigned int animationID)
{
	if (animationID >= 0 && animationID < animations.size()) {
		this->animations.at(animationID)->Stop();
	}
}

LPANIMATION Animations::GetCurrentAnimation()
{
	if (curAnimationID >= 0 && curAnimationID < animations.size())
		return animations[curAnimationID];
	else
		return nullptr;
}

float Animations::Height()
{
	if (animations.size() > 0 && curAnimationID >= 0)
		return animations[curAnimationID]->Height();
	else
		return 0.0f;
}

float Animations::Width()
{
	if (animations.size() > 0 && curAnimationID >= 0)
		return animations[curAnimationID]->Width();
	else
		return 0.0f;
}

void Animations::Update(DWORD dt)
{
	if (animations.size() > 0 && curAnimationID >= 0) {
		if (animations[curAnimationID]->IsDoing() == false)
			Start(0);
		animations[curAnimationID]->Update(dt);
	}
}





void Animations::Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler)
{
	if (animations.size() > 0 && curAnimationID >= 0) {

		animations[curAnimationID]->Render(pos, spriteHandler);
	}
}
Animations::~Animations()
{
}


