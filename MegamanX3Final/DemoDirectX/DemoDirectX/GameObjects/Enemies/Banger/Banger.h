#ifndef BANGER_H
#define BANGER_H
#include <vector>
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "BangerBullet/BangerBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../../BangerData.h"

class Banger :
	public Entity
{

public:

	Banger();
	~Banger();

	void NewEntity() override;

	enum BangerStateName
	{
		STAND,
		JUMP,
		FALL,
		ATTACK,
		DIE,
		NONE
	};

	void ChangeAnimation(BangerStateName state);

	Animation* GetAnim() const { return pCurrentAnim; }

	void SetState(BangerState* newState);
	RECT GetBound() override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255))override;

	void Update(float gameTime) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	void OnNoCollisionWithBottom() override;

protected:
	BangerData* pData;
	Animation* pCurrentAnim;
	Animation* pAnimationDie;

	BangerStateName currentState;
};
#endif // !BANGER_H
