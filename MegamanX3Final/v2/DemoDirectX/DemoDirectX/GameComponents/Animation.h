#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Windows.h>
#include <vector>
#include "Sprite.h"

class Animation : public Sprite
{
public:
	// ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight,
		float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	void update(float dt);
	void fixUpdate(float dt);
	void draw(GVec3 position = GVec3(), RECT sourceRect = RECT(),
		GVec2 scale = GVec2(), GVec2 transform = GVec2(), float angle = 0,
		GVec2 rotationCenter = GVec2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;
	void draw(GVec2 translate);

	// SUB-FUNCTION
public:
	int getCurrentRow() const;
	int getCurrentColumn() const;
	void setShoot(bool shoot);
	void setPause(bool pause);
	bool getPause() const;
	void setLoop(bool isLoop);

	void setFrame(int frameW, int frameH);
	void setAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool isLoop = true);

private:

	int	_row,				//so hang cua animation
		_cols,
		_framePerRow,		//so cot cua animation
		_currentIndex,		//gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
		_currentRow,		// hang hien tai
		_frameWidth,		// chieu rong cua 1 frame 
		_frameHeight;		// chieu dai cua 1 frame

	bool _isLoop,
		_isShoot,
		_isPause;

	float _timePerFrame,	//thoi gian luan chuyen 1 frame
		_currentTotalTime;	//tong thoi gian hien tai de thuc hien timeperframe

	RECT _rect{};
};
#endif