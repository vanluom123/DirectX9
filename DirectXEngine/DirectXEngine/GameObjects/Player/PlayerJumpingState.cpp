#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->pData = playerData;
    this->pData->pPlayer->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = 15.0f;
    acceleratorX = 14.0f;

    noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    this->pData->pPlayer->AddVy(acceleratorY);   

    if (pData->pPlayer->GetVy() >= 0)
    {
        pData->pPlayer->SetState(new PlayerFallingState(this->pData));

        return;
    }

    if (noPressed)
    {
        if (pData->pPlayer->getMoveDirection() == Player::MoveToLeft)
        {
            //pPlayer dang di chuyen sang ben trai      
            if (pData->pPlayer->GetVx() < 0)
            {
                this->pData->pPlayer->AddVx(acceleratorX);

                if (pData->pPlayer->GetVx() > 0)
                    this->pData->pPlayer->SetVx(0);
            }
        }
        else if (pData->pPlayer->getMoveDirection() == Player::MoveToRight)
        {
            //pPlayer dang di chuyen sang phai   
            if (pData->pPlayer->GetVx() > 0)
            {
                this->pData->pPlayer->AddVx(-acceleratorX);

                if (pData->pPlayer->GetVx() < 0)
                    this->pData->pPlayer->SetVx(0);
            }
        }
    }
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
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

        noPressed = false;
    }
    else if (keys[VK_LEFT])
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

        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

void PlayerJumpingState::OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data)
 {
    switch (side)
    {
        case Entity::Left:
        {
            this->pData->pPlayer->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
            this->pData->pPlayer->SetVx(0);
            break;
        }     

        case Entity::Right:
        {
            this->pData->pPlayer->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->pData->pPlayer->SetVx(0);
            break;
        }

        case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
        {          
            this->pData->pPlayer->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);            
            this->pData->pPlayer->SetVy(0);
            break;
        }

        case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
        {
            this->pData->pPlayer->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
        }

        default:
            break;
    }
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}
