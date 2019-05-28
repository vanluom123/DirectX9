#include "Port.h"
#include "../../GameComponents/GameCollision.h"

// INCLUDE PLAYER AND PLAYER'S STATE
#include "../Player/Player.h"
#include "../Player/GameState/StandState/StandState.h"


Port::Port()
{
	_objectType = BaseObject::PORT;
	_pAnim = new Animation("Resources/MapObject/Port.png", 1, 17, 16, 48, 0.1);

	_pAnim->SetAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_isOpen = false;
	_isClose = false;
	_isMove = false;
	_HP = 0;
	_Damage = 0;
	_vx = 0;
	_vy = 0;

	// INITIALIZE BOUNDING BOX
	_bound = RECT();
}

Port::~Port()
{
	delete _pAnim;
}

RECT Port::GetBound()
{
	if (!_isOpen)
		return BaseObject::GetBound();

	RECT bound;
	bound.left = _posX - _width;
	bound.right = _posX + _height;
	bound.top = _posY - _height/2;
	bound.bottom = _posY + _height / 2;
	return bound;
}

void Port::Update(float dt)
{
	if (_pAnim->GetPause() && _isOpen)
	{
		if (_isClose)
		{
			_HP = 2;
			_Damage = 1;
			_isOpen = false;
			_isMove = false;
			_pAnim->SetAnimation(0, 1);
			
		}
		else
		{
			_isMove = true;
			_Damage = 1;
		}
	}

	_pAnim->Update(dt);
}

void Port::OnCollision(eSideCollision side)
{}

void Port::OnCollision(BaseObject* obj)
{
	if ((obj->GetObjectType() != ROCK_MAN)
		|| (_HP > 0)
		|| (obj->GetBound().top < GetBound().top))
	{
		return;
	}

	if ((!_isOpen) && (!_isClose))
	{
		_HP = -1;
		_isOpen = true;
		_isMove = false;
		_Damage = 0;
		_pAnim->SetAnimation(0, 17, 0.1f, false);
	}

	if (_isMove)
	{
		if (obj->GetReverse())
			obj->SetVx(-40);
		else
			obj->SetVx(40);

		_bound.top = _posY - _height / 2;
		_bound.bottom = _posY + _height / 2;
		_bound.left = _posX - 20;
		_bound.right = _posX + 20;

		if (!GameCollision::IsCollision(_bound, obj->GetBound()))
		{
			_isClose = true;
			_pAnim->SetAnimation(1, 17, 0.1f, false);
			_isMove = false;
			_Damage = 0;

			// Improved DashState of Player when Player was dashing though Port
			Player* player = (Player*)obj;
			player->SetState(new StandState(player->GetPlayerData()));
		}
	}
	else
		obj->SetVx(0);
}

void Port::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_pAnim->GetPause())
		return;

	_pAnim->SetReverse(_isReverse);

	_pAnim->SetPosition(_startx - 8, _starty);
	_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

	_pAnim->SetPosition(_startx + 8, _starty);
	_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
}