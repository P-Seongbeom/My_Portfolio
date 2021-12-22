#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage1.bmp", 320, 192, 10, 6, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage2.bmp", 160, 160, 5, 5, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage3.bmp", 160, 160, 5, 5, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage4.bmp", 288, 960, 9, 30, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage5.bmp", 288, 320, 9, 10, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage6.bmp", 320, 224, 10, 7, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/CollisionPixel.bmp", 96, 192, 3, 6, true, RGB(87, 0, 203));

    ImageManager::GetSingleton()->AddImage("Image/character/jazz_stand.bmp", 1296, 110, 27, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jazz_walk.bmp", 448, 106, 8, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jazz_run.bmp", 277, 106, 4, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jump.bmp", 32, 32, 1, 1, true, RGB(44, 102, 150));

    ImageManager::GetSingleton()->AddImage("Image/object/temp_Ammo.bmp", 10, 10, false, RGB(255, 0, 255));
}

void ImageManager::Release()
{
    map<string, Image*>::iterator it;
    for (it = mapImages.begin(); it != mapImages.end();)
    {
        SAFE_RELEASE(it->second);
        it = mapImages.erase(it);
    }
    mapImages.clear();
}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    if (FindImage(fileName))
    {
        return nullptr;
    }

    Image* img = new Image;
    if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
    {
        SAFE_RELEASE(img);
        return nullptr;
    }

    mapImages.emplace(make_pair(fileName, img));

    return img;
}

Image* ImageManager::AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (FindImage(fileName))
    {
        return nullptr;
    }

    Image* img = new Image;
    if (FAILED(img->Init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_RELEASE(img);
        return nullptr;
    }

    mapImages.emplace(make_pair(fileName, img));

    return img;
}

Image* ImageManager::FindImage(const char* fileName)
{
    map<string, Image*>::iterator it = mapImages.find(fileName);
    if (it == mapImages.end())
    {
        return nullptr;
    }

    return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
    map<string, Image*>::iterator it = mapImages.find(fileName);
    if (it == mapImages.end())
    {
        return;
    }

    SAFE_RELEASE(it->second);
    mapImages.erase(it);
}
