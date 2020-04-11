#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Windows.h>
#include "Sprite.h"

class Animation : public Sprite
{
public:
	Animation(const char* filePath,
			  int rows,
			  int columns,
			  int frameWidth,
			  int frameHeight,
			  float timePerFrame = 0.1f,
			  D3DCOLOR colorKey = NULL);

	void update(float dt);
	void fixUpdate(float dt);

	void draw(GVec3 position = GVec3(),
			  RECT sourceRect = RECT(),
			  GVec2 scale = GVec2(),
			  GVec2 transform = GVec2(),
			  float angle = 0,
			  GVec2 rotationCenter = GVec2(),
			  D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;

	void draw(GVec2 translate);


private:
	int m_nRow;
	int m_nCols;
	int m_nFramePerRow;
	int m_nCurrentIndex;
	int m_nCurrentRow;
	int m_nFrameWidth;
	int m_nFrameHeight;

	bool m_bLoop;
	bool m_bShoot;
	bool m_bPause;

	float m_timePerFrame;
	float m_currentTotalTime;

	RECT m_SrcRect;

public:
	int getCurrentRow() const;
	int getCurrentColumn() const;
	void setShoot(bool shoot);
	void setPause(bool pause);
	bool getPause() const;
	void setLoop(bool isLoop);

	void setFrame(int frameW, int frameH);
	void setAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool isLoop = true);

};
#endif