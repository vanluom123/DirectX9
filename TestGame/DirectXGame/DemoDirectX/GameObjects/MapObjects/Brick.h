#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity/Entity.h"

//vien gach
class Brick : public Entity
{
protected:
	Brick() = default;

	bool init(D3DXVECTOR3 position);

	void OnSetPosition(D3DXVECTOR3 pos) override;

	virtual const char* FileName() = 0;
	virtual int TotalFrame() = 0; // Total frame
	virtual int Row() = 0; //Number of resource animation row 
	virtual int Column() = 0; //Number of resource animation column
	virtual float SecondPerFrame() = 0; //Number of seconds to transform animation

	Animation *mAnimation;

public:
	virtual ~Brick() = default;

    void Update(float dt) override;

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(),
		D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(),
		D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) const;

    void Draw(D3DXVECTOR2 transform) const;

};
