#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	_objectType = BaseObject::ELEVATOR;
	_pAnim = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1);

	_pAnim->SetAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	_isRun = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;
}

Elevator::~Elevator()
{
	delete _pAnim;
}

void Elevator::Update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (_posY > _starty && _posY < _starty + 2)
	{
		_posY = _starty;
		_isRun = false;
		_pAnim->SetAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}

	if (GetBound().top < 428.0f)
	{
		_isRun = false;
		_pAnim->SetAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}
		
	if (_isRun)
	{
		_posY -= 35 * dt;
	}

	_pAnim->Update(dt);

	BaseObject::Update(dt);
}

void Elevator::OnCollision(eSideCollision side)
{
}

void Elevator::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ROCK_MAN || _isRun == true)
		return;

	_isRun = true;
	_pAnim->SetAnimation(0, 3, 0.05);
}

void Elevator::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!GameCollision::IsCollision(camera->GetBound(), GetBound()))
	{
		_isRun = true;
		_pAnim->SetAnimation(0, 3, 0.05);
		_posY = _starty + 65;
	}

	_pAnim->SetReverse(_isReverse);
	_pAnim->SetPosition(this->GetPosition());
	if (camera)
		_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_pAnim->Draw(_pAnim->GetPosition());

}
