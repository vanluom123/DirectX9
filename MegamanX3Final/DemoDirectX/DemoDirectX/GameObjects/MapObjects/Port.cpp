#include "Port.h"
#include "../../GameComponents/GameCollision.h"

Port::Port()
{
	_objectType = BaseObject::PORT;
	pAnimation = new Animation("Resources/MapObject/Port.png", 1, 17, 16, 48, 0.1);

	pAnimation->SetAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	isOpen = false;
	isClose = false;
	isMove = false;
	_HP = 0;
	_Damage = 0;
	_vx = 0;
	_vy = 0;
}

Port::~Port()
{
	delete pAnimation;
}

RECT Port::GetBound()
{
	if (!isOpen)
		return BaseObject::GetBound();

	RECT r;
	r.left = _posX - _width;
	r.right = _posX + _height;
	r.top = _posY - _height/2;
	r.bottom = _posY + _height / 2;
	return r;
}

void Port::Update(float dt)
{
	if (pAnimation->GetPause() && isOpen)
	{
		if (isClose)
		{
			_HP = 2;
			_Damage = 1;
			isOpen = false;
			isMove = false;
			pAnimation->SetAnimation(0, 1);
			
		}
		else
		{
			isMove = true;
			_Damage = 1;
		}
	}

	pAnimation->Update(dt);
}

void Port::OnCollision(eSideCollision side)
{}

void Port::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ROCK_MAN || _HP > 0 || obj->GetBound().top < GetBound().top)
		return;

	if (!isOpen && !isClose)
	{
		_HP = -1;
		isOpen = true;
		isMove = false;
		_Damage = 0;
		pAnimation->SetAnimation(0, 17, 0.1, false);
	}

	if (isMove)
	{
		if (obj->GetReverse())
			obj->SetVx(-40);
		else
			obj->SetVx(40);

		bound.top = _posY - _height / 2;
		bound.bottom = _posY + _height / 2;
		bound.left = _posX - 20;
		bound.right = _posX + 20;

		if (!GameCollision::IsCollision(bound, obj->GetBound()))
		{
			isClose = true;
			pAnimation->SetAnimation(1, 17, 0.1, false);
			isMove = false;
			_Damage = 0;
		}
	}
	else
		obj->SetVx(0);
	
}

void Port::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (pAnimation->GetPause())
		return;
	pAnimation->SetReverse(_isReverse);

	pAnimation->SetPosition(_startx - 8, _starty);
	pAnimation->Draw(pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

	pAnimation->SetPosition(_startx + 8, _starty);
	pAnimation->Draw(pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
}
