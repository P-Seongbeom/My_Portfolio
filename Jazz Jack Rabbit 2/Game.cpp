#include "Config.h"
#include "CommonFunction.h"
#include "resource.h"
#include "Game.h"

#include "Timer.h"
//#include "Manager/SceneManager.h"

POINT				g_ptMouse;
HINSTANCE			_hInst;
HWND				_hWnd;
int                 windowSizeX;
int                 windowSizeY;

LRESULT Game::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

Game::~Game() noexcept
{
    DeleteObject(_backBitmap);
    DeleteDC(_backDC);
    ReleaseDC(_hWnd, _hDC);
}

bool Game::Init(HINSTANCE hInst)
{
    windowSizeX = WIN_SIZE_X;
    windowSizeY = WIN_SIZE_Y;

    hTimer = (HANDLE)SetTimer(_hWnd, 0, 10, NULL);

    LoadStringW(hInst, IDS_APP_TITLE, _title, MAX_LOADSTRING);
    LoadStringW(hInst, IDC_BASICGAMEFRAMEWORK, _windowName, MAX_LOADSTRING);

    _hInst = hInst;

    if (0 == registerClass())
    {
        return false;
    }

    _hWnd = CreateWindowW(_windowName, _title, WS_OVERLAPPEDWINDOW,
        WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y, NULL, NULL, _hInst, NULL);

    if (_hWnd == NULL)
    {
        return false;
    }

    SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

    //RECT cr = { 0, 0, _res.Width, _res.Height };
    //AdjustWindowRect(&cr, WS_OVERLAPPEDWINDOW, FALSE);
    //SetWindowPos(_hWnd, HWND_TOPMOST, 100, 100, cr.right - cr.left, cr.bottom - cr.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(_hWnd, SW_SHOW);
    UpdateWindow(_hWnd);

    windowMaxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
    windowMaxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;

    _hDC = GetDC(_hWnd);
    _backDC = CreateCompatibleDC(_hDC);
    _backBitmap = CreateCompatibleBitmap(_hDC, windowMaxSizeX, windowMaxSizeY);
    SelectObject(_backDC, _backBitmap);

    Input::Init(_hWnd);
    //SceneManager::GetInstance()->Init();
    ImageManager::GetSingleton()->Init();
    SceneManager::GetSingleton()->Init();
    //TimeManager::GetSingleton()->Init();

    return true;
}

INT32 Game::Run()
{
    Timer::Init();

    MSG msg;

    while (TRUE)
    {
        if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (Timer::CanUpdate())
            {
                processInput();
                update();
                //physicsUpdate();
                render();
            }
        }
    }

    return static_cast<INT32>(msg.wParam);
}

ATOM Game::registerClass()
{

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = LoadIcon(_hInst, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _windowName;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

void Game::processInput()
{
    Input::Update();
}

void Game::update()
{
    SceneManager::GetSingleton()->Update();
}

//void Game::physicsUpdate()
//{
//    SceneManager::GetSingleton()->PhysicsUpdate();
//}

void Game::render()
{
    RECT rect;
    SetMapMode(_hDC, MM_ANISOTROPIC);
    SetWindowExtEx(_hDC, windowSizeX, windowSizeY, NULL);
    GetClientRect(_hWnd, &rect);
    SetViewportExtEx(_hDC, rect.right, rect.bottom, NULL);

    PatBlt(_backDC, 0, 0, windowMaxSizeX, windowMaxSizeY, WHITENESS);

    SceneManager::GetSingleton()->Render(_backDC);

    BitBlt(_hDC, 0, 0, windowMaxSizeX, windowMaxSizeY,
        _backDC, 0, 0, SRCCOPY);
}