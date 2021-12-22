#include "SceneManager.h"
#include "GameEntity.h"
#include "PlayInStageScene.h"
#include "TileMapToolScene.h"

//static으로 함수를 선언하면 함수외적인 곳에서 초기화를 꼭 시켜줘야한다.
GameEntity* SceneManager::currScene = nullptr;
GameEntity* SceneManager::readyScene = nullptr;
GameEntity* SceneManager::loadingScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)	//함수 이름은 바뀌어도 됨, 나머지는 맞춰야함
{
	// 레디씬을 초기화 한다.
	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

void SceneManager::Init()
{
	SceneManager::GetSingleton()->AddScene("TileMapTool", new TileMapToolScene);
	SceneManager::GetSingleton()->AddScene("PlayInStage", new PlayInStageScene);

	SceneManager::GetSingleton()->ChangeScene("PlayInStage");
}

void SceneManager::Release()
{
	for (map<string, GameEntity*>::iterator it = mapScenes.begin();
		it != mapScenes.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapScenes.erase(it);
	}
	mapScenes.clear();

	for (map<string, GameEntity*>::iterator it = mapLoadingScenes.begin();
		it != mapLoadingScenes.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapLoadingScenes.erase(it);
	}
	mapLoadingScenes.clear();

	SAFE_RELEASE(readyScene);
	SAFE_RELEASE(loadingScene);
}

void SceneManager::Update()
{
	if (currScene)
		currScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currScene)
		currScene->Render(hdc);
}

void SceneManager::AddScene(string key, GameEntity* scene)
{
	if (scene == nullptr)  return;

	if (mapScenes.find(key) != mapScenes.end())
	{
		return;
	}

	mapScenes.insert(pair<string, GameEntity*>(key, scene));

}

void SceneManager::AddLoadingScene(string key, GameEntity* scene)
{
	if (scene == nullptr)  return;

	if (mapScenes.find(key) != mapScenes.end())
	{
		return;
	}

	mapLoadingScenes.insert(pair<string, GameEntity*>(key, scene));
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	map<string, GameEntity*>::iterator it = mapScenes.find(sceneName);

	if (it == mapScenes.end()) return E_FAIL;

	if (SUCCEEDED((it->second)->Init()))	//성공여부를 판별하려면 Init의 return타입을 HRESULT로 해줘야함
	{
		//second가 초기화 되면
		if (currScene)	currScene->Release();	//기존꺼를 release하고
		currScene = it->second;	//currScene에 second를 넣는다.
		return S_OK;
	}
	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameEntity*>::iterator it = mapScenes.find(sceneName);

	if (it == mapScenes.end()) return E_FAIL;

	//로딩씬 확인
	map<string, GameEntity*>::iterator itLoading = mapLoadingScenes.find(loadingSceneName);
	if (itLoading == mapLoadingScenes.end())
	{
		return ChangeScene(sceneName);
	}

	//로딩씬 있을 때
	if (SUCCEEDED((itLoading->second)->Init()))
	{
		if (currScene)	currScene->Release();

		readyScene = it->second;
		loadingScene = itLoading->second;

		currScene = loadingScene;

		// 멀티쓰레드 처리
		DWORD loadThread;
		HANDLE hThread = CreateThread(NULL, 0,
			LoadingThread/*실행시킬 함수포인터(함수이름)*/,
			NULL /*실행 시킬 함수에 들어갈 매개변수*/,
			0, &loadThread);

		CloseHandle(hThread);

		return S_OK;
	}
	return E_FAIL;
}

void SceneManager::PhysicsUpdate()
{
	if (currScene)
		currScene->PhysicsUpdate();
}
