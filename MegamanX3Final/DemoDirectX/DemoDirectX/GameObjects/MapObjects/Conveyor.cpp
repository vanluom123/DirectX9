#include "Conveyor.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameCollision.h"

Conveyor::Conveyor(bool direction): BaseObject()
{
	_objectType = BaseObject::CONVEYOR;
	pAnimation = new Animation("Resources/MapObject/Conveyor.png", 1, 4, 128, 32, 0.1);
	pAnimation1 = new Animation("Resources/MapObject/Conveyor1.png", 1, 4, 32, 32, 0.1);

	pAnimation->SetAnimation(0, 4, 0.1);
	pAnimation1->SetAnimation(0, 4, 0.1);

	_isReverse = direction;
	_isDie = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;

	if (direction)
		VelocityX = -50;
	else
		VelocityX = 50;
}

Conveyor::~Conveyor()
{
	delete pAnimation;
}

void Conveyor::Update(float dt)
{
	pAnimation->Update(dt);
	pAnimation1->Update(dt);
}

void Conveyor::OnCollision(eSideCollision side)
{}

void Conveyor::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ROCK_MAN && obj->GetObjectType() != ENEMY)
		return;
	if (obj->GetObjectType() == ROCK_MAN)
		obj->AddVx(VelocityX);
	else if (obj->GetObjectType() == ENEMY)
		obj->AddVx(VelocityX/2);
}

void Conveyor::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	int i = 64;

	pAnimation->SetReverse(_isReverse);
	pAnimation->SetPosition(GetBound().left + i, _posY + 8);
	pAnimation->Draw(pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

	

	while (true)
	{
		i += 128;
		if (i >= _width)
			return;

		pAnimation->SetReverse(_isReverse);
		pAnimation->SetPosition(GetBound().left + i, _posY + 8);
		pAnimation->Draw(pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

		pAnimation1->SetReverse(_isReverse);
		pAnimation1->SetPosition(GetBound().left + i - 64, _posY + 8);
		pAnimation1->Draw(pAnimation1->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	}
}
