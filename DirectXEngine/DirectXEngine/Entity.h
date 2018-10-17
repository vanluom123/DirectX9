#ifndef _ENTITY_H
#define _ENTITY_H
#include <windows.h>
#include <d3dx9.h>

class Entity
{
protected:
	// It has called when it inherited
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	// Size of entity
	int height, width;

	// Position center posX, PosY
	float posX, posY;

	// Speed vx, vy
	float vx, vy;

public:
	Entity();

	enum SideCollision
	{
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Unknown
	};

	struct CollisionReturn
	{
		bool isCollided;
		RECT RegionCollision;
	};

	enum EntityTypes
	{
		None, 
		Brick, 
		Enemy, 
		Mario, 
		Static, 
		BrickGoldNormal,
		BrickGold
	};

	EntityTypes Tag;

	virtual ~Entity();

	virtual RECT GetBound();

	virtual D3DXVECTOR3 GetPosition();

	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);

	virtual void AddPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(float x, float y);
	virtual void AddPosition(D3DXVECTOR2 pos);

	virtual int GetWidth();
	virtual void SetWidth(int width);

	virtual int GetHeight();
	virtual void SetHeight(int height);

	virtual float GetVx();
	virtual void SetVx(float vx);

	virtual float GetVy();
	virtual void SetVy(float vy);

	virtual void AddVx(float vx);
	virtual void AddVy(float vy);

	virtual void Update(float dt);

	virtual void OnCollision(Entity* entityCollision, CollisionReturn data, SideCollision side);

};

#endif