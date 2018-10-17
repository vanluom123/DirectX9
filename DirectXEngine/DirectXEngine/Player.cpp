#include "Player.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "GameGlobal.h"
#include "PlayerFallingState.h"

Player::Player()
{
	mAnimationStanding = new Animation("Resources/mario/standingright.png", 1, 1, 1, 0);
	mAnimationJumping = new Animation("Resources/mario/jumpingright.png", 1, 1, 1, 0);
	mAnimationRunning = new Animation("Resources/mario/runningright.png", 2, 1, 2, 0.15f);

	mPlayerData = new PlayerData();
	mPlayerData->player = this;

	isJumping = false;

	vx = 0;
	vy = 0;

	SetState(new PlayerStandingState(mPlayerData));
}

Player::~Player()
{}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void Player::SetCamera(Camera* camera)
{
	this->mCamera = camera;
}

void Player::Update(float dt)
{
	mCurrentAnimation->Update(dt);
	if (mPlayerData->state)
		mPlayerData->state->Update(dt);

	Entity::Update(dt);
}

void Player::Draw(D3DXVECTOR3 pos, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle,
	D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(isCurrentReverse);
	mCurrentAnimation->SetPosition(GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(float(GameGlobal::GetWidth()) / 2 - mCamera->GetPosition().x, float(GameGlobal::GetHeight()) / 2 - mCamera->GetPosition().y);
		mCurrentAnimation->Draw(D3DXVECTOR3(pos.x, pos.y, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
}

void Player::SetState(PlayerState* newState)
{
	delete mPlayerData->state;
	mPlayerData->state = newState;
	ChangedAnimation(newState->GetState());			// Relative status with that status of an animation

	mCurrentState = newState->GetState();
}

void Player::HandlerKeyboard(std::map<int, bool> keys)
{
	if (mPlayerData->state)
		mPlayerData->state->HandlerKeyBoard(keys);
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (!isJumping)
		{
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
				SetState(new PlayerJumpingState(mPlayerData));

			isJumping = true;
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
	{
		if (isJumping)
			isJumping = false;
	}
}

void Player::SetReverse(bool flag)
{
	isCurrentReverse = flag;
}

Player::MoveDirection Player::goMoveDirection()
{
	if (vx > 0)
		return MoveToRight;
	if (vx < 0)
		return MoveToLeft;

	return None;
}

PlayerState::StateName Player::GetState()
{
	return mCurrentState;
}

void Player::OnCollision(Entity* entityCollision, CollisionReturn data, SideCollision side)
{
	mPlayerData->state->OnCollision(entityCollision, data, side);
}

void Player::OnCollisionWithBottom()
{
	if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling)
		this->SetState(new PlayerFallingState(this->mPlayerData));
}

void Player::ChangedAnimation(PlayerState::StateName state)
{
	switch (state)
	{
		case PlayerState::Running:
			mCurrentAnimation = mAnimationRunning;
			break;

		case PlayerState::Standing:
			mCurrentAnimation = mAnimationStanding;
			break;

		case PlayerState::Falling:
			mCurrentAnimation = mAnimationJumping;
			break;

		case PlayerState::Jumping:
			mCurrentAnimation = mAnimationJumping;
			break;
		default: break;
	}

	width = mCurrentAnimation->GetWidth();
	height = mCurrentAnimation->GetHeight();
}