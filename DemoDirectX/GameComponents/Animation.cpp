#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	_row = rows;
	_cols = columns;
	_currentRow = 0;
	_currentIndex = 0;
	_framePerRow = columns;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_timePerFrame = timePerFrame;
	_isLoop = true;
	_isPause = false;
	_isShoot = false;
	_currentTotalTime = 0.0f;
	_rect = RECT();
}

void Animation::setFrame(int frameW, int frameH)
{
	_frameWidth = frameW;
	_frameHeight = frameH;
	setWidth(frameW);
	setHeight(frameH);
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	_currentRow = currentRow;
	_framePerRow = framePerRow;
	_timePerFrame = timePerFrame;
	_isLoop = loopAnimation;
	_currentTotalTime = 0.0f;
	_currentIndex = 0;
	_isPause = false;
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

	if (_currentTotalTime < _timePerFrame)
		return;
	
	_currentTotalTime = 0.0f;
	_currentIndex++;

	if (_currentIndex < _framePerRow)
		return;

	if (_isLoop)
		_currentIndex = 0;
	else
	{
		_currentIndex = _framePerRow - 1;
		_isPause = true;
	}
}

void Animation::fixUpdate(float dt)
{
	_rect.left = _currentIndex * _frameWidth;
	_rect.right = _rect.left + _frameWidth;
	_rect.top = (_currentRow + _isShoot) * _frameHeight;
	_rect.bottom = _rect.top + _frameHeight;

	this->setSourceRect(_rect);

	if (_framePerRow <= 1 || _isPause)
		return;

	_currentTotalTime += dt;

	if (_currentTotalTime < _timePerFrame)
		return;

	_currentTotalTime = 0.0f;
	_currentIndex++;

	if (_currentIndex < _framePerRow)
		return;

	_currentRow++;
	_currentIndex = 0;

	if (_currentRow < _row)
		return;

	if (_isLoop)
	{
		_currentIndex = 0;
		_currentRow = 0;
	}
	else
	{
		_currentIndex = _framePerRow - 1;
		_currentRow = _row - 1;
		_isPause = true;
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
	return _currentRow;
}

int Animation::getCurrentColumn() const
{
	return _currentIndex;
}

void Animation::setShoot(bool shoot)
{
	_isShoot = shoot;
}

void Animation::setPause(bool pause)
{
	_isPause = pause;
}

bool Animation::getPause() const
{
	return _isPause;
}

void Animation::setLoop(bool isLoop)
{
	_isLoop = isLoop;
}
