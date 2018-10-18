#pragma once

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"

class DemoScene : public Scene
{
protected:
	~DemoScene();
	void checkCollision();
	void CheckCameraAndWorldMap();

	GameMap *mMap;
	Camera *mCamera;
	Player *mPlayer;

	std::map<int, bool> keys;

public:
	DemoScene();

	void Update(float dt) override;
	void LoadContent() override;
	void Draw() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnMouseDown(float x, float y) override;

};