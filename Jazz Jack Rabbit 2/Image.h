#pragma once
#include "Config.h"

class Image
{
public:
	enum ImageLoadType
	{
		Resource,		// ���α׷��� ���ԵǴ� ������
		File,			// ���� �ð��� �ܺο��� �ε��ϴ� ������
		Empty,			// �� ��Ʈ�� �̹��� ����
		End
	};

	// class�� struct�� �������� ����
	// ���������ڰ� public�̳� private�̳�
	typedef struct tagImageInfo
	{
		HDC hMemDc;		// �̹��� �����͸� �����ϴ� �ڵ�(�޸� ������)
		HBITMAP hBitmap;// �̹��� ������
		HBITMAP hOldBit;// ���� �̹��� ������
		int width;		// ���� ũ��
		int height;		// ���� ũ��
		BYTE loadType;	// �ε� Ÿ��

		// �ִϸ��̼� �� ������
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			hMemDc = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = ImageLoadType::Empty;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	HRESULT Init(int width, int height);	
	HRESULT Init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL); 
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,bool isTrans = false, COLORREF transColor = NULL); 

	void Release();	// �޸� ����

	void Render(HDC hdc);
	void Render(HDC hdc, float destX, float destY);	// �̹��� �����͸� ȭ�鿡 ����
	void Render(HDC hdc, float destX, float destY, int frameX, int frameY, float scale = 1.0f);	// �̹��� �����͸� ȭ�鿡 ����

	HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDc; return NULL; }

	int GetCurrFrameX() { return imageInfo->currFrameX; }
	void SetCurrFrameX(int frame) { imageInfo->currFrameX = frame; }
	int GetCurrFrameY() { return imageInfo->currFrameY; }
	void SetCurrFrameY(int frame) { imageInfo->currFrameY = frame; }

	int GetWidth() { return imageInfo->width; }
	int GetHeight() { return imageInfo->height; }

	int GetFrameWidth() { return imageInfo->frameWidth; }
	void SetFrameWidth(int frame) { imageInfo->frameWidth = frame; }
	int GetFrameHeight() { return imageInfo->frameHeight; }
	void SetFrameHeight(int frame) { imageInfo->frameHeight = frame; }
};

