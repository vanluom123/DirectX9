#ifndef BANGER_H
#define BANGER_H
#include <vector>
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "BangerBullet/BangerBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../../BangerData.h"

class Banger :
	public BaseObject
{

public:

	Banger();
	~Banger();

	void NewEntity() override;

	enum eBangerState
	{
		BANGER_STAND,
		BANGER_JUMP,
		BANGER_FALL,
		BANGER_ATTACK,
		BANGER_DIE,
		BANGER_NONE
	};

	void ChangeAnimation(eBangerState state);

	Animation* GetAnim() const { return m_currentAnim; }

	void SetState(BangerState* newState);
	RECT GetBound() override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255))override;

	void Update(float gameTime) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void OnNoCollisionWithBottom() override;

private:
	BangerData* m_bangerData;
	Animation* m_currentAnim;
	Animation* m_animDie;

	eBangerState m_currentState;
};
#endif // !BANGER_H
