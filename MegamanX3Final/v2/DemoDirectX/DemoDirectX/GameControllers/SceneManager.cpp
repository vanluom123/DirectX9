#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	if(_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (!_instance)
		_instance = new SceneManager();

	return _instance;
}

Scene* SceneManager::GetCurrentScene() const
{
	return _currentScene;
}

void SceneManager::Update(float dt) const
{
	_currentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene* scene)
{
	delete _currentScene;
	_currentScene = scene;
}
