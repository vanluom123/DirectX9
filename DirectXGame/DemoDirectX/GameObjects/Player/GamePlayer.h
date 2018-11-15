﻿#pragma once


#include "../Entity/Entity.h"
#include "../../GameComponents/Camera.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/Animation.h"
#include <map>

using namespace MegaManState;

class GameState; 

class GamePlayer : public Entity
{
	GameState		*pState;
	Camera			*pCamera;

	Animation		*pAnimation;

	bool			isCurrentReverse;
		
	StateName		currentState;

	float			mTimeShoot;
	float			mTimeCurrentShoot;
	bool			mShoot;

	bool			allowJump;
	bool			allowShoot;

public:	
	bool			allowRight;
	bool			allowLeft;
	bool			slideLeft;
	bool			slideRight;
	bool			allowSlide;


	GamePlayer();
	~GamePlayer();

	enum MoveDirection
	{
		MoveToLeft,		// Move left
		MoveToRight,	// Move right
		None			// Stand
	};

	void ChangeAnimation(StateName state);

	void setState(GameState * newState);
	StateName getState() const;

	void SetCamera(Camera *camera);

	MoveDirection getMoveDirection() const;

	
	void HandleKeyboard(const map<int, bool>& keys, float dt) const;
	void OnKeyDown(int Key);
	void OnKeyUp(int Key);
	
	void SetReverse(bool flag);
	bool getReverse() const;

	RECT getBound() override;

	void Update(float dt) override;
	void Draw(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(), D3DXVECTOR2 Scale = D3DXVECTOR2(),
		D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0, D3DXVECTOR2 RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR TransColor = D3DCOLOR_XRGB(255, 255, 255));

	void OnCollision(CollisionReturn data, SideCollisions side) override;
	void OnNoCollisionWithBottom();
};