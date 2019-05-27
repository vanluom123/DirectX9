#ifndef GENJIBO_H
#define GENJIBO_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"


// Trang thai cua Shurikein
enum class GenjiboState
{
	MOVE,
	JUMP,
	NONE
};

// Attack1: Shurikein se xoay vong tron
// Attack2: Shurikein se xoay quanh truc y
enum class Shurikein
{
	APPEAR,
	STAND,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3,
	DIE
};

class Genjibo :
	public BaseObject
{
protected:
	Animation* anim;
	Animation* animGenjinbo;
	Animation* animDie;
	GenjiboState currentState;
	Shurikein shurikeinState;
	eSideCollision sideGen;
	float timeStand;
	bool change;
	float posY;
	float transY;
	int count;
	float timeMove;

public:
	Genjibo();
	~Genjibo();

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(BaseObject* obj) override;
	void OnCollision(eSideCollision side) override;

	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = NULL) override;
	void SetState(Shurikein keinState);

	void ManageState(float dt);
};

#endif // !GENJIBO_H
