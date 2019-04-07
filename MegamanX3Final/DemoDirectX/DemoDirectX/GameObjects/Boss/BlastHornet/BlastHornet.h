#ifndef BLAST_HORNET_H
#define BLAST_HORNET_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Bar/HPBar.h"
#include <vector>
#include "BlastBullet.h"
#include "../../../BlastHornetData.h"

// The Blast Hornet state
enum class BlastState
{
	Appear,
	Stand,
	Attack,
	Shooter,
	Move,
	Die,
	None
};

class BlastHornet :
	public Entity
{
	Animation* anim;
	HPBar* hpbar;
	BlastState curState;
	BlastHornetData* pData;

	std::vector<BlastBullet*> list_bullets_;

public:
	bool moveRandom = false;
	bool allowMove = false;
	bool moveUp = false;

	BlastHornet();
	~BlastHornet();

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	void Draw(Camera* camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotate = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void SetState(BlastHornetState* newState);
	void ChangeAnimation(BlastState state);

	Animation* GetAnimation() const {
		return anim; 
	}

	std::vector<BlastBullet*>* GetListBullet() {
		return &list_bullets_;
	}
};


#endif // !BLAST_HORNET_H
