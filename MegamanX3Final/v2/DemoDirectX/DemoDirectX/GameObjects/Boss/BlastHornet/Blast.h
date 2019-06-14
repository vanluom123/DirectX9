#ifndef _BLAST_HORNET_H
#define _BLAST_HORNET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Bar/HPBar.h"
#include <vector>
#include "BlastBullet.h"
#include "BlastData.h"
#include <map>

// The Blast Hornet state
enum class eBlastState
{
	BLAST_STATE_APPEAR = 0,
	BLAST_STATE_STAND = 1,
	BLAST_STATE_ATTACK = 2,
	BLAST_STATE_SHOOT = 3,
	BLAST_STATE_SINE_MOVEMENT = 4,
	BLAST_STATE_DEATH = 5,
	BLAST_STATE_UNKNOWN = 6
};

class Blast : public BaseObject
{
public:
	Blast();
	~Blast();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(eSideCollision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void setState(BlastState* newState);
	void changeAnimation(eBlastState state);

	void loadResource();

	// SUB-FUNCTION
public:
	std::vector<BlastBullet*>* getListBullet();
	Animation* getAnimation(eBlastState e);

private:
	Animation* _pAnim;
	HPBar* _HPBar;
	eBlastState _currentState;
	BlastData* _data;
	std::vector<BlastBullet*> _listBullet;
	std::map<eBlastState, Animation*> _animation;
};


#endif // _BLAST_HORNET_H
