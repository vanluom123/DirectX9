#ifndef _CAMERA_H
#define _CAMERA_H
#include <d3dx9.h>

class Camera
{
public:
	Camera(int width, int height);
	~Camera() = default;

	int GetWidth() const;
	int GetHeight() const;

	RECT GetBound() const;

	D3DXVECTOR3 GetPosition() const;

	//Center camera
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
private:
	int mHeight;
	int mWidth;
	D3DXVECTOR3 mPosition;
};

#endif