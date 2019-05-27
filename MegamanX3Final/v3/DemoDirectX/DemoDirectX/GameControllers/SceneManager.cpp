#include "SceneManager.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	m_currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	delete m_instance;
	m_instance = nullptr;
}

SceneManager* SceneManager::GetInstance()
{
	if (!m_instance)
		m_instance = new SceneManager();

	return m_instance;
}

Scene* SceneManager::GetCurrentScene() const
{
	return m_currentScene;
}

void SceneManager::Update(float dt)
{
	m_currentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene* scene)
{
	delete m_currentScene;
	m_currentScene = scene;
}
