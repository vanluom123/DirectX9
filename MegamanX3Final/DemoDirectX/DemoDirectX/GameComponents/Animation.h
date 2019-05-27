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

	void Update(float dt);
	void Draw(GVec3 position = GVec3(), RECT sourceRect = RECT(),
		GVec2 scale = GVec2(), GVec2 transform = GVec2(), float angle = 0,
		GVec2 rotationCenter = GVec2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Draw(GVec2 translate);

	// SUB-FUNCTION
public:
	int GetCurrentRow() const { return _currentRow; }
	int GetCurrentColumn() const { return _currentIndex; }
	void SetShoot(bool shoot) { this->_isShoot = shoot; }
	void SetPause(bool pause) { this->_isPause = pause; }
	bool GetPause() const { return this->_isPause; }
	void SetLoop(bool isLoop) { this->_isLoop = isLoop; }

	void SetFrame(int frameW, int frameH);
	void SetAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool isLoop = true);

private:

	int				_row,				//so hang cua animation
					_cols,
					_framePerRow,		//so cot cua animation
					_currentIndex,		//gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
					_currentRow,			// hang hien tai
					_frameWidth,			// chieu rong cua 1 frame 
					_frameHeight;		// chieu dai cua 1 frame

	bool			_isLoop,
					_isShoot,
					_isPause;

	float			_timePerFrame,		//thoi gian luan chuyen 1 frame
					_currentTotalTime;	//tong thoi gian hien tai de thuc hien timeperframe

	RECT			_rect;
};
#endif