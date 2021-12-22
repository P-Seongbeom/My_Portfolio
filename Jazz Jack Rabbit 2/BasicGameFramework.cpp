// BasicGameFramework.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.

#include "Config.h"
#include "Game.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(305);
#endif
    Game game;

    if (false == game.Init(hInstance))
    {
        return 0;
    }

    INT32 res = game.Run();

    game.Release();

    return res;
}

