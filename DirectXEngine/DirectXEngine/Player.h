#ifndef _PLAYER_H
#define _PLAYER_H
#include "Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "Animation.h"

class Player :public Entity
{
public:
	Player();
	~Player();

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(D3DXVECTOR3 pos = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(PlayerState* newState);

	//xu ly input
	//gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
	void HandlerKeyboard(std::map<int, bool> keys);

	void OnKeyPressed(int key);

	void OnKeyUp(int key);

	//true thi se lat nguoc anh theo truc y
	void SetReverse(bool flag);

	MoveDirection goMoveDirection();

	PlayerState::StateName GetState();
protected:
	
	void ChangedAnimation(PlayerState::StateName state);
	PlayerState::StateName mCurrentState;

	// isJumping = false similar player is Standing, isJumping = true similar player is Jumping 
	bool isJumping, isCurrentReverse;

	Animation *mCurrentAnimation, *mAnimationStanding, *mAnimationRunning, *mAnimationJumping;

	PlayerData *mPlayerData;
};
#endif