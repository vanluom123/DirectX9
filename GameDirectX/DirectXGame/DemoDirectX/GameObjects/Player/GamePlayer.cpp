#include "GamePlayer.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "../../GameComponents/GameGlobal.h"

void GamePlayer::ChangeAnimation(StateName state)
{
	switch (state)
	{
		case Standing:
		{
			pGameAnimation->setAnimation(1, 4, 0, 0.15);
			break;
		}
		case StandingShoot:
		{
			pGameAnimation->setAnimation(2, 2, 0, 0.15);
			break;
		}
		case Running:
		{
			pGameAnimation->setAnimation(3, 10, 0, 0.05);
			break;
		}
		case RunningShoot:
		{
			pGameAnimation->setAnimation(4, 10, 0, 0.05);
			break;
		}
		case Jumping:
		{
			pGameAnimation->setAnimation(5, 3, 2, 0.5);
			break;
		}
		case JumpingShoot:
		{
			pGameAnimation->setAnimation(6, 3, 0, 0.5);
			break;
		}
		case Falling:
		{
			pGameAnimation->setAnimation(7, 3, 0, 0.5);
			break;
		}
		default:
			break;
	}

	this->_Width = pGameAnimation->GetWidth();
	this->_Height = pGameAnimation->GetHeight();
}

GamePlayer::GamePlayer()
{
	pGameAnimation = new GameAnimation("Resources/mario/Rockman_49x49_backfround(100,100,100).png", 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	_Vx = 0;
	_Vy = 0;
	setState(new FallState(this));
}

void GamePlayer::setState(GameState* newState)
{
	allowLeft = true;
	allowRight = true;

	SAFE_DELETE(pState);
	pState = newState;
	ChangeAnimation(newState->getState());
	currentState = newState->getState();
}
StateName GamePlayer::getState() const
{
	return currentState;
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
	if(Key == VK_X) {
		if(isJumping) {
			if (currentState == Running || currentState == Standing)
				setState(new JumpState(this));
			isJumping = false;
		}
	}
}

void GamePlayer::OnKeyUp(int Key)
{
	if(Key == VK_X) {
		if (!isJumping)
			isJumping = true;
	}
}

void GamePlayer::SetReverse(bool flag)
{
	isCurrentReverse = flag;
}

RECT GamePlayer::getBound()
{

	RECT rect;
	rect.left = _X - pGameAnimation->GetWidth() / 2.0f;
	rect.right = rect.left + pGameAnimation->GetWidth();
	rect.top = _Y - pGameAnimation->GetHeight() / 2.0f;
	rect.bottom = rect.top + pGameAnimation->GetHeight();

	return rect;
}

void GamePlayer::Update(float dt)
{
	pGameAnimation->Update(dt);

	if (pState)
		pState->Update(dt);

	Entity::Update(dt);
}

void GamePlayer::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate,
	float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	pGameAnimation->SetFlip(isCurrentReverse);
	pGameAnimation->SetPosition(getPosition());

	if (pCamera)
	{
		const auto trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - pCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2.0f - pCamera->GetPosition().y);

		pGameAnimation->Draw(D3DXVECTOR3(_X, _Y, 0), SourceRect, Scale, trans, Angle, RotationCenter, Transcolor);
	}
	else
		pGameAnimation->Draw(D3DXVECTOR3(_X, _Y, 0));
}

void GamePlayer::OnCollision(CollisionReturn data, SideCollisions side)
{
	pState->OnCollision(data, side);
}

void GamePlayer::OnNoCollisionWithBottom()
{
	if (currentState != MegaManState::Jumping && currentState != MegaManState::Falling)
		setState(new FallState(this));
}
