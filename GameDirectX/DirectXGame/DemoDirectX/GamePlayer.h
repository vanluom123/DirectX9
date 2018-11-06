#pragma once
#include "GameComponents/Animation.h"
#include "StandState.h"
#include "GameComponents/Camera.h"
#include "GameComponents/GameAnimation.h"

class GameState; 

class GamePlayer : public Entity
{
	GameState	*pState;
	Camera		*pCamera;
	/*Animation   *_CurrentAnim,
				*_AnimStanding,
				*_AnimRunning,
				*_AnimJumping,
				*_AnimFalling;*/

	GameAnimation *_PlayerAnimation;

	bool _isJumping, _isCurrentReverse;
	bool _AllowRight, _AllowLeft;
	MegaManState::StateName _CurrentState;

	void _ChangeGameAnimation(MegaManState::StateName state);
	//void _ChangeAnimation(MegaManState::StateName stateName);

public:

	GamePlayer();
	~GamePlayer() = default;

	enum MoveDirection
	{
		MoveToLeft,		// Move left
		MoveToRight,	// Move right
		None			// Stand
	};

	bool getAllowLeft() const;
	void setAllowLeft(bool allowleft);

	bool getAllowRight() const;
	void setAllowRight(bool allowright);

	void setState(GameState * newState);
	MegaManState::StateName getState() const;

	void SetCamera(Camera *camera);

	MoveDirection getMoveDirection() const;

	
	void HandleKeyboard(const std::map<int, bool>& keys) const;
	void OnKeyPressed(int Key);
	void OnKeyUp(int Key);
	
	void SetReverse(bool flag);

	RECT GetBound() override;

	void Update(float dt) override;
	void Draw(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(), D3DXVECTOR2 Scale = D3DXVECTOR2(),
		D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0, D3DXVECTOR2 RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR Transcolor = D3DCOLOR_XRGB(255, 255, 255));

	void OnCollision(CollisionReturn data, SideCollisions side) override;
	void OnNoCollisionWithBottom();

};