#ifndef _ENTITY_H
#define _ENTITY_H
#include <windows.h>
#include <d3dx9.h>

class Entity
{
public:
	Entity();
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
protected:
	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//Size cua entity
	int mHeight, mWidth;

	//vi tri tam position x va y
	float posX, posY;

	//phan toc vx, vy
	float vx, vy;
};

#endif