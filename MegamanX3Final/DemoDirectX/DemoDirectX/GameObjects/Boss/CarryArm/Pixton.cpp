#include "Pixton.h"
#include "../../../GameComponents/Camera.h"


Pixton::Pixton()
{
	isBottom = false;
	anim     = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_39.png", 1, 1, 144, 88);
	this->SetWidth(anim->GetWidth());
	this->SetHeight(anim->GetHeight());
	posY = 0;
}

Pixton::~Pixton()
{
	delete anim;
}

RECT Pixton::GetBound()
{
	RECT r;
	r.left = _posX - _width / 2;
	r.right = _posX + _width / 2;
	r.bottom = _posY + _height / 2;
	r.top = r.bottom -16;
	return r;
}

void Pixton::Draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	anim->SetPosition(GetPosition());
	if (camera)
		anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	else
		anim->Draw(anim->GetPosition());
}

void Pixton::OnCollision(eSideCollision side)
{
	
}

void Pixton::Update(float gameTime)
{
	if (!_isAllowDraw)
		return;

	anim->Update(gameTime);
	BaseObject::Update(gameTime);
}

bool Pixton::MoveDown(float gameTime, float x, float y)
{
	if (!isBottom)
	{
		posY += 40 * gameTime;
		if (posY >= 88)
		{
			isBottom = true;
			posY = 88;
		}
		SetPosition(x + 55, y + posY);
	}
	return !isBottom;
}

bool Pixton::MoveUp(float gameTime, float x, float y)
{
	if (isBottom)
	{
		posY -= 40 * gameTime;
		if (posY <= 0)
		{
			isBottom = false;
			posY = 0;
			_vy = -40;
		}
		SetPosition(x + 56, y + posY);
	}
	return isBottom;
}
