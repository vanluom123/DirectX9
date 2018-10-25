#include "SceneManager.h"

SceneManager* SceneManager::mInstance = NULL;

SceneManager::SceneManager()
{
    mCurrentScene = NULL;
}

SceneManager::~SceneManager()
{}

SceneManager* SceneManager::GetInstance()
{
    if (!mInstance)
        mInstance = new SceneManager();

    return mInstance;
}

Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

void SceneManager::Update(float dt)
{}

void SceneManager::ReplaceScene(Scene *scene)
{
    delete mCurrentScene;
    mCurrentScene = scene;
}