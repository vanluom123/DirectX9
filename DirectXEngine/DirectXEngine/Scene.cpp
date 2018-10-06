#include "Scene.h"
#include <iostream>

D3DCOLOR Scene::GetBackColor() const
{
	return mBackColor;
}

Scene::Scene()
{
	mBackColor = 0x4866ff;
	Scene::LoadContent();
}

void Scene::LoadContent()
{
	std::cout << "Content is loaded in class Scene" << std::endl;
}