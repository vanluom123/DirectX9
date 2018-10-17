#ifndef _PLAYER_H
#define _PLAYER_H
#include "Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "Animation.h"
#include "Camera.h"

class Player :public Entity
{
protected:

	void ChangedAnimation(PlayerState::StateName state);

	PlayerState::StateName mCurrentState;

	// isJumping = false similar player is Standing, isJumping = true similar player is Jumping 
	bool isJumping, isCurrentReverse;

	Animation *mCurrentAnimation, *mAnimationStanding, *mAnimationRunning, *mAnimationJumping;

	PlayerData *mPlayerData;

	Camera* mCamera;

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

	void SetCamera(Camera* camera);

	void Update(float dt) override;

	void Draw(D3DXVECTOR3 pos = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(PlayerState* newState);

	// Input Handler
	// KeyBoard contain 256 character. If keys[KeyCode] is true, it is pressed. Else keys[KeyCode] is false, it doesn't press
	void HandlerKeyboard(std::map<int, bool> keys);

	void OnKeyPressed(int key);

	void OnKeyUp(int key);

	// If flag is True, it will flip image by y
	void SetReverse(bool flag);

	MoveDirection goMoveDirection();

	PlayerState::StateName GetState();

	void OnCollision(Entity* impact, CollisionReturn data, SideCollision side) override;

	void OnCollisionWithBottom();

	bool allowMoveToLeft;
	bool allowMoveToRight;

};
#endif