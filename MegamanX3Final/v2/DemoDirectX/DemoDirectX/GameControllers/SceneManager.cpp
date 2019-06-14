#include "SceneManager.h"
#include "../GameDefines/GameDefine.h"
#include "../Scenes/IntroScene.h"
#include "../Scenes/BeginScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	// Do nothing
}

SceneManager* SceneManager::getInstance()
{
	if (!_instance)
		_instance = new SceneManager();

	return _instance;
}

Scene* SceneManager::getCurrentScene() const
{
	return _currentScene;
}

void SceneManager::update(float dt) const
{
	_currentScene->update(dt);
}

void SceneManager::setScene(eSceneType sceneType)
{
	SAFE_DELETE(_currentScene);

	switch (sceneType)
	{
		case SceneManager::INTRO_SCENE:
			_currentScene = new IntroScene();
			break;

		case SceneManager::BEGIN_SCENE:
			_currentScene = new BeginScene();
			break;

		default:
			break;
	}
}
