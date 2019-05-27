#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	_objectType = BaseObject::ELEVATOR;
	pAnimation = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1);

	pAnimation->SetAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	isRun = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;
}

Elevator::~Elevator()
{
	delete pAnimation;
}

void Elevator::Update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (_posY > _starty && _posY < _starty + 2)
	{
		_posY = _starty;
		isRun = false;
		pAnimation->SetAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}

	if (GetBound().top < 428.0f)
	{
		isRun = false;
		pAnimation->SetAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}
		
	if (isRun)
	{
		_posY -= 35 * dt;
	}

	pAnimation->Update(dt);

	BaseObject::Update(dt);
}

void Elevator::OnCollision(eSideCollision side)
{
}

void Elevator::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ROCK_MAN || isRun == true)
		return;

	isRun = true;
	pAnimation->SetAnimation(0, 3, 0.05);
}

void Elevator::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!GameCollision::IsCollision(camera->GetBound(), GetBound()))
	{
		isRun = true;
		pAnimation->SetAnimation(0, 3, 0.05);
		_posY = _starty + 65;
	}

	pAnimation->SetReverse(_isReverse);
	pAnimation->SetPosition(this->GetPosition());
	if (camera)
		pAnimation->Draw(pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		pAnimation->Draw(pAnimation->GetPosition());

}
