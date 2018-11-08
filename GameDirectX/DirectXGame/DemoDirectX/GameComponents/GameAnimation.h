#pragma once
#include "Sprite.h"

class GameAnimation : public Sprite
{
protected:

	int                         mRows,			//so hang cua animation
								mColumns,
								mframePerRow,	//so cot cua animation
								mCurrentIndex,	//gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
								mCurrentRow,	// hang hien tai
								mFrameWidth,	// chieu rong cua 1 frame 
								mFrameHeight;	// chieu dai cua 1 frame


	float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
								mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe

	RECT                        mRect;

public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	GameAnimation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	GameAnimation() = default;

	void setAnimation(int currentRow, int framePerRow, int currentIndex = 0, float timePerFrame = 0.1f);

	virtual void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;

	void Draw(D3DXVECTOR2 translate);

	~GameAnimation() = default;
};
