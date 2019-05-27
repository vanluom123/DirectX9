#include "Conveyor.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameCollision.h"

Conveyor::Conveyor(bool direction): BaseObject()
{
	m_objectType = BaseObject::OBJECT_CONVEYOR;
	_pAnim = new Animation("Resources/MapObject/Conveyor.png", 1, 4, 128, 32, 0.1);
	_pAnim2 = new Animation("Resources/MapObject/Conveyor1.png", 1, 4, 32, 32, 0.1);

	_pAnim->SetAnimation(0, 4, 0.1);
	_pAnim2->SetAnimation(0, 4, 0.1);

	m_isReverse = direction;
	m_isDie = false;
	m_isAllowDraw = true;
	m_vx = 0;
	m_vy = 0;

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
	if (obj->GetObjectType() != OBJECT_ROCK_MAN && obj->GetObjectType() != OBJECT_ENEMY)
		return;
	if (obj->GetObjectType() == OBJECT_ROCK_MAN)
		obj->AddVx(_velocityX);
	else if (obj->GetObjectType() == OBJECT_ENEMY)
		obj->AddVx(_velocityX/2);
}

void Conveyor::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!m_isAllowDraw)
		return;

	int i = 64;

	_pAnim->SetReverse(m_isReverse);
	_pAnim->SetPosition(GetBound().left + i, m_posY + 8);
	_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

	

	while (true)
	{
		i += 128;
		if (i >= m_width)
			return;

		_pAnim->SetReverse(m_isReverse);
		_pAnim->SetPosition(GetBound().left + i, m_posY + 8);
		_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

		_pAnim2->SetReverse(m_isReverse);
		_pAnim2->SetPosition(GetBound().left + i - 64, m_posY + 8);
		_pAnim2->Draw(_pAnim2->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	}
}
