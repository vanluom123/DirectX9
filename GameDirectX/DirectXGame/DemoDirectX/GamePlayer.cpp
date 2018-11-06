#include "GamePlayer.h"
#include "StandState.h"
#include "RunState.h"
#include "GameComponents/GameGlobal.h"
#include "FallState.h"
#include "JumpState.h"


void GamePlayer::_ChangeAnimation(MegaManState::StateName stateName)
{
	switch (stateName)
	{
	case MegaManState::Running:
		_CurrentAnim = _AnimRunning;
		break;

	case MegaManState::Standing:
		_CurrentAnim = _AnimStanding;
		break;

	case MegaManState::Falling:
		_CurrentAnim = _AnimJumping;
		break;

	case MegaManState::Jumping:
		_CurrentAnim = _AnimJumping;
		break;

	default:
		break;
	}

	_Width = _CurrentAnim->GetWidth();
	_Height = _CurrentAnim->GetHeight();
}

GamePlayer::GamePlayer()
{
	_AnimStanding = new Animation(Define::ANIMATION_STANDING, 1, 1, 1, 0);
	_AnimRunning = new Animation(Define::ANIMATION_RUNNING, 2, 1, 2, 0.15f);
	_AnimJumping = new Animation(Define::ANIMATION_JUMPING, 1, 1, 1, 0.15f);

	_isJumping = false;
	_Vx = 0;
	_Vy = 0;
	setState(new FallState(this));
}

bool GamePlayer::getAllowLeft() const
{
	return _AllowLeft;
}

void GamePlayer::setAllowLeft(bool allowleft)
{
	_AllowLeft = allowleft;
}

bool GamePlayer::getAllowRight() const
{
	return _AllowRight;
}

void GamePlayer::setAllowRight(bool allowright)
{
	_AllowRight = allowright;
}

void GamePlayer::setState(GameState* newState)
{
	_AllowLeft = true;
	_AllowRight = true;

	SAFE_DELETE(pState);
	pState = newState;
	_ChangeAnimation(newState->getState());
	_CurrentState = newState->getState();
}

MegaManState::StateName GamePlayer::getState() const
{
	return _CurrentState;
}

void GamePlayer::SetCamera(Camera* camera)
{
	pCamera = camera;
}

GamePlayer::MoveDirection GamePlayer::getMoveDirection() const
{
	if (_Vx > 0) return MoveToRight;
	if (_Vx < 0) return MoveToLeft;
	return None;
}

void GamePlayer::HandleKeyboard(const std::map<int, bool>& keys) const
{
	if (pState)
		pState->HandleKeyboard(keys);
}

void GamePlayer::OnKeyPressed(int Key)
{
	if (Key == VK_SPACE)
	{
		if (!_isJumping)
		{
			if (_CurrentState == MegaManState::Running || _CurrentState == MegaManState::Standing)
				setState(new JumpState(this));

			_isJumping = true;
		}
	}
}

void GamePlayer::OnKeyUp(int Key)
{
	if(Key == VK_SPACE)
	{
		if (_isJumping)
			_isJumping = false;
	}
}

void GamePlayer::SetReverse(bool flag)
{
	_isCurrentReverse = flag;
}

RECT GamePlayer::GetBound()
{
	RECT rect;
	rect.left = _X - _CurrentAnim->GetWidth() / 2.0f;
	rect.right = rect.left + _CurrentAnim->GetWidth();
	rect.top = _Y - _CurrentAnim->GetHeight() / 2.0f;
	rect.bottom = rect.top + _CurrentAnim->GetHeight();

	return rect;
}

void GamePlayer::Update(float dt)
{
	_CurrentAnim->Update(dt);

	if (pState)
		pState->Update(dt);
	
	Entity::Update(dt);
}

void GamePlayer::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate, float Angle,
	D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	_CurrentAnim->SetFlip(_isCurrentReverse);
	_CurrentAnim->SetPosition(GetPosition());

	if (pCamera)
	{
		const auto trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - pCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2.0f - pCamera->GetPosition().y);

		_CurrentAnim->Draw(D3DXVECTOR3(_X, _Y, 0), SourceRect, Scale, trans, Angle, RotationCenter, Transcolor);
	}
	else
		_CurrentAnim->Draw(D3DXVECTOR3(_X, _Y, 0));
}

void GamePlayer::OnCollision(CollisionReturn data, SideCollisions side)
{
	pState->OnCollision(data, side);
}

void GamePlayer::OnNoCollisionWithBottom()
{
	if (_CurrentState != MegaManState::Jumping && _CurrentState != MegaManState::Falling)
		setState(new FallState(this));
}
