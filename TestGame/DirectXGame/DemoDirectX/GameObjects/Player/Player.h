#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/Camera.h"
#include "PlayerData.h"
#include "PlayerState.h"

class Player : public Entity
{
protected:

	Camera      *_Camera;

	PlayerData *_PlayerData;

	Animation   *_CurrentAnim,
				*_AnimStanding,
				*_AnimRunning,
				*_AnimJumping,
				*_AnimFalling;

	void changeAnimation(PlayerState::StateName state);
	void _LoadResources();

	PlayerState::StateName _CurrentState;

	//chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool _AllowJump, _CurrentReverse;

public:
    Player();
    ~Player() = default;

    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void SetCamera(Camera *camera);

    void Update(float dt) override;

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(),
		D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(),
		D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(PlayerState *newState);

    void OnCollision(CollisionReturn data, SideCollisions side) override;

    void OnNoCollisionWithBottom();

    MoveDirection getMoveDirection() const;

    RECT GetBound() override;     

    PlayerState::StateName getState() const;

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys) const;

    void OnKeyPressed(int key);

    void OnKeyUp(int key);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);

    bool allowMoveLeft;
    bool allowMoveRight;

};