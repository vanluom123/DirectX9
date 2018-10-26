#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Entity
{
protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	float posX, posY;

	//phan toc vx, vy
	float vx, vy;

	//size cua entity
	float width, height;

public:
	virtual ~Entity();

	Entity();

    enum SideCollisions
    {
        Left, //0
        Right, //1
        Top, //2
        Bottom, //3
        TopLeft, //4
        TopRight, //5
        BottomLeft, //6
        BottomRight, //7
        Unknown
    };

    struct CollisionReturn
    {
        bool IsCollided;
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
    	BrickGoldBeEaten
    };

	//To confirm type of Entity
    EntityTypes Tag;

    virtual RECT GetBound();

	virtual D3DXVECTOR3 GetPosition();
    virtual void SetPosition(float x, float y);
    virtual void SetPosition(D3DXVECTOR2 pos);
    virtual void SetPosition(D3DXVECTOR3 pos);

	virtual void AddPosition(float x, float y);
	virtual void AddPosition(D3DXVECTOR2 pos);
    virtual void AddPosition(D3DXVECTOR3 pos);

    virtual void SetWidth(int width);
    virtual int GetWidth();

    virtual void SetHeight(int height);
    virtual int GetHeight();

    virtual float GetVx();
    virtual void SetVx(float vx);
    virtual void AddVx(float vx);

    virtual float GetVy();
    virtual void SetVy(float vy);
    virtual void AddVy(float vy);

    virtual void Update(float dt);

    //Control collision
	//When entity collide, this function will be called
    virtual void OnCollision(CollisionReturn data, SideCollisions side);

};