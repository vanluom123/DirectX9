#ifndef CAMERA_H
#define CAMERA_H
#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int width, int height);

	//center of camera
	D3DXVECTOR3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR3 pos);

	D3DXVECTOR2 getTrans() const;

	RECT getBound() const;

	int getWidth() const { return mWidth; }
	void setWidth(int val) { mWidth = val; }
	int getHeight() const { return mHeight; }
	void setHeight(int val) { mHeight = val; }

private:
	int mWidth, mHeight;
	D3DXVECTOR3 mPositionWorld;
};

#endif // !CAMERA_H
