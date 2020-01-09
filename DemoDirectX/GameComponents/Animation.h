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

	int	_row,				// the number of row of sprite sheet
		_cols,
		_framePerRow,		// the number of column of sprite sheet
		_currentIndex,		// The value of current frame - start from 0 -> The total frame - 1
		_currentRow,		// current row in frame of sprite sheet
		_frameWidth,		// The width of frame
		_frameHeight;		// The height of frame

	bool _isLoop,
		_isShoot,
		_isPause;

	float _timePerFrame,	// time to translate one frame
		_currentTotalTime;	// The total current time to execute time per frame

	RECT _rect;
};
#endif