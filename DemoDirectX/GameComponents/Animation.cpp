#include "Animation.h"


Animation::Animation(const char* filePath,
					 int rows,
					 int columns,
					 int frameWidth,
					 int frameHeight,
					 float timePerFrame,
					 D3DCOLOR colorKey) :
	Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	m_nRow = rows;
	m_nCols = columns;
	m_nCurrentRow = 0;
	m_nCurrentIndex = 0;
	m_nFramePerRow = columns;
	m_nFrameWidth = frameWidth;
	m_nFrameHeight = frameHeight;
	m_timePerFrame = timePerFrame;
	m_bLoop = true;
	m_bPause = false;
	m_bShoot = false;
	m_currentTotalTime = 0.0f;
	m_SrcRect = RECT();
}

void Animation::setFrame(int frameW, int frameH)
{
	m_nFrameWidth = frameW;
	m_nFrameHeight = frameH;
	setWidth(frameW);
	setHeight(frameH);
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	m_nCurrentRow = currentRow;
	m_nFramePerRow = framePerRow;
	m_timePerFrame = timePerFrame;
	m_bLoop = loopAnimation;
	m_currentTotalTime = 0.0f;
	m_nCurrentIndex = 0;
	m_bPause = false;
}

void Animation::update(float dt)
{
	m_SrcRect.left = m_nCurrentIndex * m_nFrameWidth;
	m_SrcRect.right = m_SrcRect.left + m_nFrameWidth;
	m_SrcRect.top = (m_nCurrentRow + m_bShoot) * m_nFrameHeight;
	m_SrcRect.bottom = m_SrcRect.top + m_nFrameHeight;

	this->setSourceRect(m_SrcRect);

	if (m_nFramePerRow <= 1 || m_bPause)
		return;

	m_currentTotalTime += dt;

	if (m_currentTotalTime < m_timePerFrame)
		return;

	m_currentTotalTime = 0.0f;
	m_nCurrentIndex++;

	if (m_nCurrentIndex < m_nFramePerRow)
		return;

	if (m_bLoop)
		m_nCurrentIndex = 0;
	else
	{
		m_nCurrentIndex = m_nFramePerRow - 1;
		m_bPause = true;
	}
}

void Animation::fixUpdate(float dt)
{
	m_SrcRect.left = m_nCurrentIndex * m_nFrameWidth;
	m_SrcRect.right = m_SrcRect.left + m_nFrameWidth;
	m_SrcRect.top = (m_nCurrentRow + m_bShoot) * m_nFrameHeight;
	m_SrcRect.bottom = m_SrcRect.top + m_nFrameHeight;

	this->setSourceRect(m_SrcRect);

	if (m_nFramePerRow <= 1 || m_bPause)
		return;

	m_currentTotalTime += dt;

	if (m_currentTotalTime < m_timePerFrame)
		return;

	m_currentTotalTime = 0.0f;
	m_nCurrentIndex++;

	if (m_nCurrentIndex < m_nFramePerRow)
		return;

	m_nCurrentRow++;
	m_nCurrentIndex = 0;

	if (m_nCurrentRow < m_nRow)
		return;

	if (m_bLoop)
	{
		m_nCurrentIndex = 0;
		m_nCurrentRow = 0;
	}
	else
	{
		m_nCurrentIndex = m_nFramePerRow - 1;
		m_nCurrentRow = m_nRow - 1;
		m_bPause = true;
	}
}

void Animation::draw(GVec3 position, RECT sourceRect, GVec2 scale, GVec2 transform,
					 float angle, GVec2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::draw(GVec2 translate)
{
	Sprite::draw(GVec3(), RECT(), GVec2(), translate);
}

int Animation::getCurrentRow() const
{
	return m_nCurrentRow;
}

int Animation::getCurrentColumn() const
{
	return m_nCurrentIndex;
}

void Animation::setShoot(bool shoot)
{
	m_bShoot = shoot;
}

void Animation::setPause(bool pause)
{
	m_bPause = pause;
}

bool Animation::getPause() const
{
	return m_bPause;
}

void Animation::setLoop(bool isLoop)
{
	m_bLoop = isLoop;
}
