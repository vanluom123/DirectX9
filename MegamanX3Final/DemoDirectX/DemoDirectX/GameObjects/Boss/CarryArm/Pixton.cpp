#include "Pixton.h"
#include "../../../GameComponents/Camera.h"


Pixton::Pixton()
{
	isBottom = false;
	anim     = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_39.png", 1, 1, 144, 88);
	this->SetWidth(anim->getWidth());
	this->SetHeight(anim->getHeight());
	posY = 0;
}

Pixton::~Pixton()
{
	delete anim;
}

RECT Pixton::GetBound()
{
	RECT r;
	r.left = x - width / 2;
	r.right = x + width / 2;
	r.bottom = y + height / 2;
	r.top = r.bottom -16;
	return r;
}

void Pixton::Draw(Camera * camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotate, D3DCOLOR color)
{
	if (!allowDraw)
		return;

	anim->setPosition(GetPosition());
	if (camera)
		anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	else
		anim->draw(anim->getPosition());
}

void Pixton::OnCollision(SideCollisions side)
{
	
}

void Pixton::Update(float gameTime)
{
	if (!allowDraw)
		return;

	anim->update(gameTime);
	Entity::Update(gameTime);
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
			vy = -40;
		}
		SetPosition(x + 56, y + posY);
	}
	return isBottom;
}
