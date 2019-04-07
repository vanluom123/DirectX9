#ifndef GENJIBO_H
#define GENJIBO_H
#include "../../Entity/Entity.h"
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
	public Entity
{
protected:
	Animation* anim;
	Animation* animGenjinbo;
	Animation* animDie;
	GenjiboState currentState;
	Shurikein shurikeinState;
	SideCollisions sideGen;
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
	void OnCollision(Entity* obj) override;
	void OnCollision(SideCollisions side) override;

	void Draw(Camera* camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotate = D3DXVECTOR2(), D3DCOLOR color = NULL) override;
	void SetState(Shurikein keinState);

	void ManageState(float dt);
};

#endif // !GENJIBO_H
