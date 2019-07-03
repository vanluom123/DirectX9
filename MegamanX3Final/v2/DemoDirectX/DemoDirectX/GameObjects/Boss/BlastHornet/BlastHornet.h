#ifndef __BLAST_HORNET_H__
#define __BLAST_HORNET_H__

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../Bar/HPBar.h"
#include "BlastBullet.h"
#include "../../Player/Player.h"
#include <map>

class BlastHornetState;

class BlastHornet :
	public BaseObject
{
public:

	BlastHornet();
	~BlastHornet();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void setState(BlastHornetState* newState);
	void loadResource();
	void changeAnimation(Hornet_State state);

	// GETTER - SETTER
public:
	vector<BlastBullet*>* getListBullet();
	Animation* getAnimBlast();

	Player* getPlayer() const;
	void setPlayer(Player* val);

	float getDx() const;
	float getDy() const;

private:
	// Distance from BOSS to Rock Man
	float m_Dx;
	float m_Dy;
	HPBar* m_HPBar;
	Player* m_pPlayer;
	BlastHornetState* m_pState;
	vector<BlastBullet*> m_listBullets;
	Animation* m_pCurrentAnimation;
	Animation* m_pAppear;
	Animation* m_pIdle;
	Animation* m_pAttack;
	Animation* m_pShoot;
	Animation* m_pMove;
	Animation* m_pDeath;

	Hornet_State m_currentState;
};

#endif // !__BLAST_HORNET_H__