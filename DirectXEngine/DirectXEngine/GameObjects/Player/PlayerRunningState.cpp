#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->pData = playerData;
    
    acceleratorX = 25.0f;

    this->pData->pPlayer->allowMoveLeft = true;
    this->pData->pPlayer->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        if (pData->pPlayer->allowMoveRight)
        {
            pData->pPlayer->SetReverse(false);

            //di chuyen sang phai
            if (this->pData->pPlayer->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->pData->pPlayer->AddVx(acceleratorX);

                if (this->pData->pPlayer->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->pData->pPlayer->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else if (keys[VK_LEFT])
    {
        if (pData->pPlayer->allowMoveLeft)
        {
            pData->pPlayer->SetReverse(true);

            //di chuyen sang trai
            if (this->pData->pPlayer->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->pData->pPlayer->AddVx(-acceleratorX);

                if (this->pData->pPlayer->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->pData->pPlayer->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else
    {
        this->pData->pPlayer->SetState(new PlayerStandingState(this->pData));
        return;
    }
}

void PlayerRunningState::OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::GetSideCollision(this->pData->player, data);

    switch (side)
    {
        case Entity::Left:
        {
            //va cham phia ben trai player
            if (this->pData->pPlayer->getMoveDirection() == Player::MoveToLeft)
            {
                this->pData->pPlayer->allowMoveLeft = false;

                //day Player ra phia ben phai de cho player khong bi xuyen qua object
                this->pData->pPlayer->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

                this->pData->pPlayer->SetState(new PlayerStandingState(this->pData));
            }

			break;
        }

        case Entity::Right: 
        {
            //va cham phia ben phai player
            if (this->pData->pPlayer->getMoveDirection() == Player::MoveToRight)
            {
                this->pData->pPlayer->allowMoveRight = false;
                this->pData->pPlayer->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
                this->pData->pPlayer->SetState(new PlayerStandingState(this->pData));
            }
			break;
        }

        case Entity::Top:
            break;

        case Entity::Bottom: case Entity::BottomLeft : case Entity::BottomRight:           
        {
            this->pData->pPlayer->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

            this->pData->pPlayer->SetVy(0);

            break;
        }
		default: break;
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}
