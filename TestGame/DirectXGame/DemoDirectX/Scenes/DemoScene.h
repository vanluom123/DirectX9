#pragma once

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"

class DemoScene : public Scene
{
protected:
	void _IsCheckCollision() const;
	void _CheckCameraAndWorldMap() const;

	GameMap*	pMap;
	Camera*		pCamera;
	Player*		pPlayer;

	std::map<int, bool> keys;

public:
	DemoScene();
	~DemoScene() = default;

	void Update(float dt) override;
	void LoadContent() override;
	void Draw() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnMouseDown(float x, float y) override;

};