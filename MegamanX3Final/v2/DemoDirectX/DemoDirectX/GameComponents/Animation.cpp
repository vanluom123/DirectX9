#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->_row = rows;
	this->_cols = columns;

	this->_currentRow = 0;
	this->_currentIndex = 0;

	this->_framePerRow = columns;

	this->_frameWidth = frameWidth;
	this->_frameHeight = frameHeight;

	this->_timePerFrame = timePerFrame;

	this->_isLoop = true;
	this->_isPause = false;
	this->_isShoot = false;

	// INIT CURRENT TOTAL TIME
	// INIT RECT
	this->_currentTotalTime = 0.0f;
	this->_rect = RECT();
}

void Animation::setFrame(int frameW, int frameH)
{
	this->_frameWidth = frameW;
	this->_frameHeight = frameH;
	this->setWidth(frameW);
	this->setHeight(frameH);
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->_currentRow = currentRow;
	this->_framePerRow = framePerRow;

	this->_timePerFrame = timePerFrame;

	this->_isLoop = loopAnimation;

	this->_currentTotalTime = 0.0f;
	this->_currentIndex = 0;
	this->_isPause = false;
}

void Animation::update(float dt)
{
	_rect.left = _currentIndex * _frameWidth;
	_rect.right = _rect.left + _frameWidth;
	_rect.top = (_currentRow + _isShoot) * _frameHeight;
	_rect.bottom = _rect.top + _frameHeight;

	this->setSourceRect(_rect);

	if (_framePerRow <= 1 || _isPause)
		return;

	_currentTotalTime += dt;
	if (_currentTotalTime >= _timePerFrame)
	{
		_currentTotalTime = 0.0f;
		_currentIndex++;
		if (_currentIndex >= _framePerRow)
		{
			if (_isLoop)
				_currentIndex = 0;
			else
			{
				_currentIndex = _framePerRow - 1;
				_isPause = true;
			}
		}
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