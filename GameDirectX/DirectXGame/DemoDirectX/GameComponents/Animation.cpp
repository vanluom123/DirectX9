#include "Animation.h"

Animation::Animation(const char* ImagePath, int TotalFrame, int Rows, int Columns, float TimePerFrame, D3DCOLOR Transcolor) : Sprite(ImagePath)
{
	_IndexColumn = 0;
	_IndexRow = 0;
	_NumberRow = Rows;
	_NumberColumn = Columns;
	_TimePerFrame = TimePerFrame;
	_TotalFrame = TotalFrame;

	////_Width - _Height luc nay la cua sprite sheet
	_FrameWidth = (float)GetWidth() / _NumberColumn;
	_FrameHeight = (float)GetHeight() / _NumberRow;

	SetWidth(_FrameWidth);
	SetHeight(_FrameHeight);

	_Rect.top = 0;
	_Rect.left = 0;
	_Rect.right = _FrameWidth;
	_Rect.bottom = _FrameHeight;

	SetSourceRect(_Rect);
}

void Animation::Update(float dt)
{
	if (_TotalFrame <= 1)
		return;

	if (_CurrentTotalFrame >= _TimePerFrame)
	{
		_CurrentTotalFrame = 0;
		_CurrentIndex++;
		_IndexColumn++;

		if (_CurrentIndex >= _TotalFrame)
		{
			_CurrentIndex = 0;
			_IndexColumn = 0;
			_IndexRow = 0;
		}

		if (_IndexColumn >= _NumberColumn)
		{
			_IndexColumn = 0;
			_IndexRow++;

			if (_IndexRow >= _NumberRow)
				_IndexRow = 0;
		}

		_Rect.left = (_IndexColumn % _NumberColumn)*(_FrameWidth);
		_Rect.top = (_IndexColumn / _NumberColumn)*(_FrameHeight);
		_Rect.right = _Rect.left + _FrameWidth;
		_Rect.bottom = _Rect.top + _FrameHeight;

		SetSourceRect(_Rect);
	}
	else
		_CurrentTotalFrame += dt;
}

void Animation::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale,
	D3DXVECTOR2 Translate, float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	Sprite::Draw(Position, SourceRect, Scale, Translate, Angle, RotationCenter, Transcolor);
}

void Animation::Draw(D3DXVECTOR2 Translate)
{
	Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), Translate);
}