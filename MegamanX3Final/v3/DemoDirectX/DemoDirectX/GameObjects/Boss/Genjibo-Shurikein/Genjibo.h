#ifndef GENJIBO_H
#define GENJIBO_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"


class Genjibo :
	public BaseObject
{

public:

	// Trang thai cua Shurikein
	enum eGenjiboState
	{
		GENJIBO_MOVE,
		GENJIBO_JUMP,
		GENJIBO_UNKNOWN
	};

	// Attack1: Shurikein se xoay vong tron
	// Attack2: Shurikein se xoay quanh truc y
	enum eShurikeinState
	{
		SHURIKEIN_APPEAR,
		SHURIKEIN_STAND,
		SHURIKEIN_ATTACK_1,
		SHURIKEIN_ATTACK_2,
		SHURIKEIN_ATTACK_3,
		SHURIKEIN_DIE
	};

	Genjibo();
	~Genjibo();

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(BaseObject* obj) override;
	void OnCollision(eSideCollision side) override;

	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = NULL) override;
	void SetState(eShurikeinState keinState);

	void UpdateState(float dt);

private:
	Animation* m_anim;
	Animation* m_animGenjinbo;
	Animation* m_animDie;
	eGenjiboState m_genjiboState;
	eShurikeinState m_shurikeinState;
	eSideCollision m_sideGen;
	float m_timeStand;
	bool m_change;
	float m_posY;
	float m_transY;
	int m_count;
	float m_timeMove;
};

#endif // !GENJIBO_H
