#pragma once

#include "../GameComponents/Scene.h"

class SceneManager
{
private:
	SceneManager();
	static SceneManager     *mInstance;
	Scene                   *mCurrentScene;
public:
    static SceneManager *GetInstance();
    ~SceneManager();

    Scene* GetCurrentScene();
    void Update(float dt);
    void ReplaceScene(Scene *scene);
};