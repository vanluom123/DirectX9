#include "Scene.h"

Scene::Scene()
{
	_backColor = 0x4866ff;
}

void Scene::Update(float dt) {}

void Scene::Draw() {}

void Scene::OnKeyDown(int keyCode) {}

void Scene::OnKeyUp(int keyCode) {}

void Scene::onMouseDown(float x, float y) {}

D3DCOLOR Scene::GetBackColor() const
{
	return _backColor;
}