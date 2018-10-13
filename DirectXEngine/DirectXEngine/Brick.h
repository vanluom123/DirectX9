#ifndef _BRICK_H
#define _BRICK_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Entity.h"
#include "Animation.h"

class Brick :public Entity
{
public:
	Brick();
	~Brick();

	void Update(float dt) override;

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 trans);

protected:
	void OnSetPosition(D3DXVECTOR3 pos) override;

	bool Init(D3DXVECTOR3 position);

	virtual const char* FileName() = 0;				//Duong dan den file resource
	virtual int TotalFrame() = 0;					//To so frame trong animation
	virtual int Row() = 0;							//So dong cua resource hinh anh animtion
	virtual int Columns() = 0;						//So cot cua resource hinh anh animation
	virtual float SecondsPerFrame() = 0;			//So giay de chuyen frame cua animation

	Animation* mAnimation;
};

#endif