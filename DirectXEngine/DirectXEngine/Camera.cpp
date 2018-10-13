#include "Camera.h"

Camera::Camera()
{}

Camera::Camera(int width, int height)
{
	this->mWidth = width;
	this->mHeight = height;
	this->mPosition = D3DXVECTOR3(0, 0, 0);
}

Camera::~Camera()
{}

int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = long(mPosition.x - float(mWidth) / 2);
	bound.right = bound.left + mWidth;
	bound.top = long(mPosition.y - float(mHeight) / 2);
	bound.bottom = bound.top + mHeight;

	return bound;
}

D3DXVECTOR3 Camera::GetPosition()
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
