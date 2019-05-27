#ifndef ENTITIES_H
#define ENTITIES_H

#include <vector>
#include "../../GameComponents/Camera.h"

class BaseObject
{
public:
	BaseObject();

	enum eSideCollision
	{
		SIDE_COLLISION_LEFT,
		SIDE_COLLISION_RIGHT,
		SIDE_COLLISION_TOP,
		SIDE_COLLISION_BOTTOM,
		SIDE_COLLISION_TOP_LEFT,
		SIDE_COLLISION_TOP_RIGHT,
		SIDE_COLLISION_BOTTOM_LEFT,
		SIDE_COLLISION_BOTTOM_RIGHT,
		SIDE_COLLISION_NONE
	};

	enum eObjectType
	{
		OBJECT_ROCK_MAN,
		OBJECT_ROCK_MAN_BULLET,
		OBJECT_ENEMY,
		OBJECT_ENEMY_BULLET,
		OBJECT_BOSS,
		OBJECT_ELEVATOR,
		OBJECT_CONVEYOR,
		OBJECT_STATIC,
		OBJECT_PORT,
		OBJECT_THORN,
		OBJECT_BOX,
		OBJECT_ITEM,
		OBJECT_UNKNOWN
	};

	struct CollisionReturn
	{
		bool isCollision;
		RECT regionCollision;
	};

	virtual void NewEntity() { }

	void CheckTimeCollision(float collisionTime, eSideCollision side, BaseObject* other);

	virtual void Update(float dt);
	virtual void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) { };

	//Control collision
	//When entity collide, this function will be called
	virtual void OnCollision(eSideCollision side);
	virtual void OnCollision(BaseObject* obj);
	virtual void OnNoCollisionWithBottom();

	// SUB-FUNCTION
public:
	virtual RECT GetBound();

	GVec3 GetPosition()
	{
		return GVec3(m_posX, m_posY, 0);
	}

	void SetPosition(float x, float y)
	{
		SetPosition(GVec2(x, y));
	}

	void SetPosition(GVec2 pos)
	{
		SetPosition(GVec3(pos.x, pos.y, 0));
	}

	void SetPosition(GVec3 pos)
	{
		this->m_posX = pos.x;
		this->m_posY = pos.y;
		OnSetPosition(pos);
	}

	GVec3 GetPositionStart()
	{
		return GVec3(this->m_startx, this->m_starty, 0);
	}

	void SetPositionStart(float x, float y)
	{
		SetPositionStart(GVec2(x, y));
	}

	void SetPositionStart(GVec2 pos)
	{
		SetPositionStart(GVec3(pos.x, pos.y, 0));
	}

	void SetPositionStart(GVec3 pos) 
	{
		this->m_startx = pos.x;
		this->m_starty = pos.y;
		OnSetPosition(pos);
	}

	void AddPosition(float x, float y)
	{
		AddPosition(GVec2(x, y));
	}

	void AddPosition(GVec2 pos)
	{
		AddPosition(GVec3(pos.x, pos.y, 0));
	}

	void AddPosition(GVec3 pos)
	{
		SetPosition(this->GetPosition() + pos);
	}

	void SetWidth(int width) { this->m_width = width; }
	int GetWidth() { return this->m_width; }

	void SetHeight(int height) { this->m_height = height; }
	int GetHeight() { return this->m_height; }

	void SetHP(int hp) { this->m_HP = hp; }
	int GetHP() { return this->m_HP; }

	void SetMaxHP(int hp) { this->m_MaxHP = hp; }
	int GetMaxHP() { return this->m_MaxHP; }

	void SetDamage(int dame) { this->m_Damage = dame; }
	int GetDamage() { return this->m_Damage; }

	float GetVx() { return this->m_vx; }
	void SetVx(float vx) { this->m_vx = vx; }
	void AddVx(float vx) { this->m_vx += vx; }

	float GetVy() { return this->m_vy; }
	void SetVy(float vy) { this->m_vy = vy; }
	void AddVy(float vy) { this->m_vy += vy; }

	void SetDraw(bool isDraw) { this->m_isAllowDraw = isDraw; }
	bool GetDraw() { return this->m_isAllowDraw; }

	void SetObjectType(eObjectType objectType) { this->m_objectType = objectType; }
	eObjectType GetObjectType() { return this->m_objectType; }

	void SetReverse(bool reverse) { m_isReverse = reverse; }
	bool GetReverse() { return m_isReverse; }

	void SetDie(bool die) { m_isDie = die; }
	bool GetDie() { return m_isDie; }

	std::vector<BaseObject*>* GetListBullet();

	void SetId(int id);
	int GetId() const;

protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(GVec3 pos) { }

	//vi tri tam position x va y
	float m_posX, m_posY, m_startx, m_starty;

	//phan toc vx, vy
	float m_vx, m_vy;
	int m_HP, m_Damage, m_MaxHP;
	//size cua entity
	float m_width, m_height;

	float m_collisionTimeMinX;
	float m_collisionTimeMinY;

	bool m_isAllowDraw;	// allow to draw the sprite when the Camera contain Enemies

	eSideCollision m_sideX;
	eSideCollision m_sideY;
	BaseObject* m_entityX;
	BaseObject* m_entityY;
	eObjectType m_objectType;

	std::vector<BaseObject*> m_listBullet;

	bool m_isReverse;
	bool m_isDie;

	int m_id;
};

#endif // !ENTITIES_H
