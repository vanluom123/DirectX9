#include "Camera.h"

Camera::Camera(int width, int height)
{
	this->mWidth = width;
	this->mHeight = height;
	this->mPosition = D3DXVECTOR3(0, 0, 0);
}

int Camera::GetWidth() const
{
	return mWidth;
}

int Camera::GetHeight() const
{
	return mHeight;
}

RECT Camera::GetBound() const
{
	RECT bound;

	bound.left = long(mPosition.x - float(mWidth) / 2);
	bound.right = bound.left + long(mWidth);
	bound.top = long(mPosition.y - float(mHeight) / 2);
	bound.bottom = bound.top + long(mHeight);

	return bound;
}

D3DXVECTOR3 Camera::GetPosition() const
{
	return mPosition;
}

void Camera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}
