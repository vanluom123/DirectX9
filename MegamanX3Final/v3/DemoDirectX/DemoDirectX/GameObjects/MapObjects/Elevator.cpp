#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	m_objectType = BaseObject::OBJECT_ELEVATOR;
	_pAnim = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1);

	_pAnim->SetAnimation(0, 1);
	m_isReverse = false;
	m_isDie = false;
	_isRun = false;
	m_isAllowDraw = true;
	m_vx = 0;
	m_vy = 0;
}

Elevator::~Elevator()
{
	delete _pAnim;
}

void Elevator::Update(float dt)
{
	if (!m_isAllowDraw)
		return;

	if (m_posY > m_starty && m_posY < m_starty + 2)
	{
		m_posY = m_starty;
		_isRun = false;
		_pAnim->SetAnimation(0, 1);
		m_vx = 0;
		m_vy = 0;
	}

	if (GetBound().top < 428.0f)
	{
		_isRun = false;
		_pAnim->SetAnimation(0, 1);
		m_vx = 0;
		m_vy = 0;
	}
		
	if (_isRun)
	{
		m_posY -= 35 * dt;
	}

	_pAnim->Update(dt);

	BaseObject::Update(dt);
}

void Elevator::OnCollision(eSideCollision side)
{
}

void Elevator::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != OBJECT_ROCK_MAN || _isRun == true)
		return;

	_isRun = true;
	_pAnim->SetAnimation(0, 3, 0.05);
}

void Elevator::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!m_isAllowDraw)
		return;

	if (!GameCollision::IsCollision(camera->GetBound(), GetBound()))
	{
		_isRun = true;
		_pAnim->SetAnimation(0, 3, 0.05);
		m_posY = m_starty + 65;
	}

	_pAnim->SetReverse(m_isReverse);
	_pAnim->SetPosition(this->GetPosition());
	if (camera)
		_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_pAnim->Draw(_pAnim->GetPosition());

}
