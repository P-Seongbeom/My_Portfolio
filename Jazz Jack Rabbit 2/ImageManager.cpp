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
    ImageManager::GetSingleton()->AddImage("Image/tilemap/CollisionPixel.bmp", 96, 224, 3, 7, true, RGB(87, 0, 203));
    ImageManager::GetSingleton()->AddImage("Image/tilemap/pixelMap1.bmp", 1280, 960, 1, 1, true, RGB(87, 0, 203));

    ImageManager::GetSingleton()->AddImage("Image/character/jazz_idle.bmp", 1296, 110, 27, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jazz_walk.bmp", 448, 106, 8, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jazz_run.bmp", 277, 106, 4, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/jump.bmp", 522, 168, 9, 3, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/rope.bmp", 360, 268, 8, 4, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/falling.bmp", 174, 168, 3, 3, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/quick_down.bmp", 400, 124, 8, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/uppercut.bmp", 680, 122, 10, 2, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/character/shooting.bmp", 100, 348, 2, 6, true, RGB(44, 102, 150));

    ImageManager::GetSingleton()->AddImage("Image/character/helth_icon.bmp", 15, 12, 1, 1, true, RGB(0, 128, 255));

    ImageManager::GetSingleton()->AddImage("Image/enemy/turtle/turtlegoon_walk.bmp", 1488, 126, 12, 2, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/turtle/turtlegoon_hide.bmp", 1488, 252, 12, 4, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/turtle/turtlegoon_die.bmp", 124, 126, 1, 2, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queen_idle.bmp", 756, 62, 9, 1, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queen_shouting.bmp", 672, 62, 8, 1, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queen_stompfoot.bmp", 756, 62, 9, 1, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queen_wobble.bmp", 924, 62, 11, 1, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queen_die.bmp", 1092, 62, 13, 1, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/enemy/boss/queens_brick.bmp", 28, 24, true, RGB(0, 128, 255));


    ImageManager::GetSingleton()->AddImage("Image/character/collisionRect.bmp", 20, 32, 1, 1, false, RGB(127, 127, 127));

    ImageManager::GetSingleton()->AddImage("Image/object/Ammo.bmp", 10, 10, true, RGB(0, 128, 255));
    ImageManager::GetSingleton()->AddImage("Image/object/ammo_effect.bmp", 176, 20, 8, 1, true, RGB(0, 128, 255));

    ImageManager::GetSingleton()->AddImage("Image/title/title_x-mas.bmp", 640, 480, false, RGB(149, 177, 200));
    ImageManager::GetSingleton()->AddImage("Image/title/press_space.bmp", 482, 40, true, RGB(0, 128, 255));

    ImageManager::GetSingleton()->AddImage("Image/scene/stage_clear.bmp", 482, 682, 2, 11, true, RGB(44, 102, 150));
    ImageManager::GetSingleton()->AddImage("Image/scene/background_black.bmp", 640, 480, false, RGB(255, 0, 255));

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
