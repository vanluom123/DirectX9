#include "Scene.h"
#include <iostream>

D3DCOLOR Scene::GetBackColor()
{
	return mBackColor;
}

Scene::~Scene()
{}

Scene::Scene()
{
	mBackColor = 0x4866ff;
	Scene::LoadContent();
}

void Scene::LoadContent()
{
	std::cout << "Content is loaded in class Scene" << std::endl;
}

void Scene::KeyDown(int keyCode)
{}

void Scene::KeyUp(int keyCode)
{}

void Scene::MouseDown(float x, float y)
{}
