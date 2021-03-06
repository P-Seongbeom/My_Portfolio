#pragma once

class Game
{
	enum { MAX_LOADSTRING = 100 };

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	~Game() noexcept;

	bool				Init(HINSTANCE hInst);
	INT32				Run();
	void				Release();

private:
	int					windowMaxSizeX = 0;
	int					windowMaxSizeY = 0;

	ATOM				registerClass();

	void				processInput();
	void				update();
	void				physicsUpdate();
	void				render();
private:
	CHAR				_title[MAX_LOADSTRING] = {};
	CHAR				_windowName[MAX_LOADSTRING] = {};
	HDC					_hDC = {};
	HDC					_backDC = {};
	HBITMAP				_backBitmap = {};
};