#ifndef BLAST_HORNET_H
#define BLAST_HORNET_H

#include "../../Entity/BaseObject.h"
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
	public BaseObject
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
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
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
