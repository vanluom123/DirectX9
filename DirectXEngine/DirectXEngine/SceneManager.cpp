#include "SceneManager.h"

SceneManager* SceneManager::mInstance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (!mInstance)
		mInstance = new SceneManager();

	return mInstance;
}

Scene* SceneManager::GetCurrentScene() const
{
	return mCurrentScene;
}

void SceneManager::Update(float dt) const
{
	mCurrentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene* scene)
{
	//delete mCurrentScene;
	mCurrentScene = scene;
}

SceneManager::~SceneManager()
{
	if (mCurrentScene)
	{
		delete mCurrentScene;
		mCurrentScene = nullptr;
	}
}
