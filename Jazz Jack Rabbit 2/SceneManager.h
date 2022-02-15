#pragma once
#include "Config.h"
#include "Singleton.h"

class GameEntity;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameEntity*>	mapScenes;
	map<string, GameEntity*>	mapLoadingScenes;

public:
	static GameEntity* currScene;	
	static GameEntity* readyScene;	
	static GameEntity* loadingScene;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddScene(string key, GameEntity* scene);
	void AddLoadingScene(string key, GameEntity* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	void PhysicsUpdate();
};

