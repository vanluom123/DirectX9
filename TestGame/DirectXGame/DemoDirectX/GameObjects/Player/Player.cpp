#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameDefines/GameDefine.h"

Player::Player()
{
	_LoadResources();
	_PlayerData = new PlayerData();
	_PlayerData->player = this;
	vx = 0;
	vy = 0;
	SetState(new PlayerFallingState(_PlayerData));
	_AllowJump = true;
}


void Player::Update(float dt)
{
	_CurrentAnim->Update(dt);

	if (_PlayerData->state)
		_PlayerData->state->Update(dt);

	Entity::Update(dt);
}

void Player::HandleKeyboard(std::map<int, bool> keys) const
{
	if (_PlayerData->state)
		_PlayerData->state->HandleKeyboard(keys);
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (_AllowJump)
		{
			if (_CurrentState == PlayerState::Running || _CurrentState == PlayerState::Standing)
				SetState(new PlayerJumpingState(_PlayerData));
			
			_AllowJump = false;
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
		_AllowJump = true;
}

void Player::SetReverse(bool flag)
{
	_CurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
	_Camera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	_CurrentAnim->FlipVertical(_CurrentReverse);
	_CurrentAnim->SetPosition(GetPosition());

	if (_Camera)
	{
		const auto trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - _Camera->GetPosition().x,
			GameGlobal::GetHeight() / 2.0f - _Camera->GetPosition().y);

		_CurrentAnim->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
		_CurrentAnim->Draw(D3DXVECTOR3(posX, posY, 0));
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;

	delete _PlayerData->state;

	_PlayerData->state = newState;

	changeAnimation(newState->GetState());

	_CurrentState = newState->GetState();
}

void Player::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	_PlayerData->state->OnCollision(side, data);
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = posX - _CurrentAnim->GetWidth() / 2.0f;
	rect.right = rect.left + _CurrentAnim->GetWidth();
	rect.top = posY - _CurrentAnim->GetHeight() / 2.0f;
	rect.bottom = rect.top + _CurrentAnim->GetHeight();

	return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Running:
		_CurrentAnim = _AnimRunning;
		break;

	case PlayerState::Standing:
		_CurrentAnim = _AnimStanding;
		break;

	case PlayerState::Falling:
		_CurrentAnim = _AnimFalling;
		break;

	case PlayerState::Jumping:
		_CurrentAnim = _AnimJumping;
		break;

	default:
		break;
	}

	width = _CurrentAnim->GetWidth();
	height = _CurrentAnim->GetHeight();
}

void Player::_LoadResources()
{
	_AnimStanding = new Animation(Define::MEGAMAN_STAND, 4, 4, 1, 0);
	_AnimJumping = new Animation(Define::MEGAMAN_JUMP, 3, 1, 3, 0.15f);
	_AnimRunning = new Animation(Define::MEGAMAN_RUN, 11, 3, 4, 0.15f);
	_AnimFalling = new Animation(Define::MEGAMAN_FALL, 3, 3, 1, 0.15f);
}

Player::MoveDirection Player::getMoveDirection() const
{
	if (vx > 0)
		return MoveDirection::MoveToRight;

	if (vx < 0)
		return MoveDirection::MoveToLeft;
	
	return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
	if (_CurrentState != PlayerState::Jumping && _CurrentState != PlayerState::Falling)
		SetState(new PlayerFallingState(_PlayerData));
}

PlayerState::StateName Player::getState() const
{
	return _CurrentState;
}
