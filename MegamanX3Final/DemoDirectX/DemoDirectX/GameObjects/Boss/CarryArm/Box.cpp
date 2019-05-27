#include "Box.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

Box::Box(bool isr)
{
	isR = isr;
	_objectType     = eObjectType::BOX;
	_MaxHP	= 6;
	_HP		= _MaxHP;
	anim    = new Animation("Resources/Enemies/CarryArm/box.png", 2, 1, 48, 48);
	pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	pAnimationDie->SetPause(true);
	_width    = anim->GetWidth();
	_height   = anim->GetHeight();
	_vx = 0;
	_vy = 0;
}
void Box::NewEntity()
{
	if (isR)
	{
		_vx = 0;
		_vy = 300;
		_Damage = 4;
	}
	else
	{
		_vx = 0;
		_vy = 0;
	}
	_HP = _MaxHP;
	_isDie = false;
	_posX = _startx;
	_posY = _starty;

}

Box::~Box()
{
	delete anim;
	delete pAnimationDie;
}

void Box::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!_isAllowDraw) return;

	if (!GameCollision::IsCollision(camera->GetBound(), GetBound()))
		if (isR)
			NewEntity();

	if (!pAnimationDie->GetPause())
	{
		pAnimationDie->Draw(pAnimationDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

		if (_height > 48)
		{
			int i = 24;
			while (true)
			{
				pAnimationDie->SetPosition(_posX, GetBound().top + i);
				pAnimationDie->Draw(pAnimationDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

				i += 48;
				if (i > _height)
					break;
			}
		}
	}

	if (!_isDie)
	{
		int i = 24;
		while (true)
		{
			anim->SetPosition(_posX, GetBound().top + i);
			anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

			if (isR)
				if (!pAnimationDie->GetPause())
					pAnimationDie->Draw(pAnimationDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

			i += 48;
			if (i > _height)
				return;
		}
	}
}

RECT Box::GetBound()
{
	RECT r;

	r.left = _posX - (float)_width / 2;
	r.top = _posY - (float)_height / 2;
	r.right = r.left + _width;
	r.bottom = r.top + _height;

	return r;
}

void Box::Update(float dt)
{
	if (!_isAllowDraw) return;

	anim->Update(dt);
	pAnimationDie->Update(dt);
	BaseObject::Update(dt);
}

void Box::OnCollision(eSideCollision side)
{
	if (_sideY == BaseObject::BOTTOM && isR)
	{
		_HP = 1;
		isBottom = false;
		_isDie = true;
		pAnimationDie->SetPosition(GetPosition());
		pAnimationDie->SetAnimation(0, 10, 0.05, false);
	}
}

void Box::OnCollision(BaseObject* obj)
{
	
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_HP = 1;
			isBottom = false;
			_isDie = true;
			pAnimationDie->SetPosition(GetPosition());
			pAnimationDie->SetAnimation(0, 8, 0.05, false);
		}
	}
}