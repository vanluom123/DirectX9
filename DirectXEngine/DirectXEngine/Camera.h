#ifndef _CAMERA_H
#define _CAMERA_H
#include <d3dx9.h>

class Camera
{
public:
	Camera();
	Camera(int width, int height);
	~Camera();

	int GetWidth();
	int GetHeight();

	RECT GetBound();

	D3DXVECTOR3 GetPosition();

	// Camera center
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
private:
	// Size of camera
	int mHeight, mWidth;
	// Position of camera
	D3DXVECTOR3 mPosition;
};

#endif