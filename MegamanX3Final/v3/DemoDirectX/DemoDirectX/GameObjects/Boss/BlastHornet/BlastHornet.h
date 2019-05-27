#ifndef BLAST_HORNET_H
#define BLAST_HORNET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Bar/HPBar.h"
#include <vector>
#include "BlastBullet.h"
#include "../../../BlastHornetData.h"


class BlastHornet :
	public BaseObject
{

public:

	// The Blast Hornet state
	enum eBlastState
	{
		BLAST_STATE_APPEAR,
		BLAST_STATE_STAND,
		BLAST_STATE_ATTACK,
		BLAST_STATE_SHOOTER,
		BLAST_STATE_MOVE,
		BLAST_STATE_DIE,
		BLAST_STATE_UNKNOWN
	};


	bool m_isMoveRandom = false;
	bool m_isAllowMove = false;
	bool m_isAllowMoveUp = false;

	BlastHornet();
	~BlastHornet();

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void SetState(BlastHornetState* newState);
	void ChangeAnimation(eBlastState state);

	// SUB-FUNCTION
public:
	Animation* GetAnimation() const;
	std::vector<BlastBullet*>* GetListBullet();


private:
	Animation* m_anim;
	HPBar* m_HPBar;
	eBlastState m_currentState;
	BlastHornetData* m_blastHornetData;

	std::vector<BlastBullet*> m_listBlastBullet;
};


#endif // !BLAST_HORNET_H
