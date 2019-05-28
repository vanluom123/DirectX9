#include "Conveyor.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameCollision.h"

Conveyor::Conveyor(bool direction): BaseObject()
{
	_objectType = BaseObject::CONVEYOR;
	_pAnim = new Animation("Resources/MapObject/Conveyor.png", 1, 4, 128, 32, 0.1);
	_pAnim2 = new Animation("Resources/MapObject/Conveyor1.png", 1, 4, 32, 32, 0.1);

	_pAnim->SetAnimation(0, 4, 0.1);
	_pAnim2->SetAnimation(0, 4, 0.1);

	_isReverse = direction;
	_isDie = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;

	if (direction)
		_velocityX = -50;
	else
		_velocityX = 50;
}

Conveyor::~Conveyor()
{
	delete _pAnim;
}

void Conveyor::Update(float dt)
{
	_pAnim->Update(dt);
	_pAnim2->Update(dt);
}

void Conveyor::OnCollision(eSideCollision side)
{}

void Conveyor::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ROCK_MAN && obj->GetObjectType() != ENEMY)
		return;
	if (obj->GetObjectType() == ROCK_MAN)
		obj->AddVx(_velocityX);
	else if (obj->GetObjectType() == ENEMY)
		obj->AddVx(_velocityX/2);
}

void Conveyor::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	int i = 64;

	_pAnim->SetReverse(_isReverse);
	_pAnim->SetPosition(GetBound().left + i, _posY + 8);
	_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

	

	while (true)
	{
		i += 128;
		if (i >= _width)
			return;

		_pAnim->SetReverse(_isReverse);
		_pAnim->SetPosition(GetBound().left + i, _posY + 8);
		_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

		_pAnim2->SetReverse(_isReverse);
		_pAnim2->SetPosition(GetBound().left + i - 64, _posY + 8);
		_pAnim2->Draw(_pAnim2->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	}
}
