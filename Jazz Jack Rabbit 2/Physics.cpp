#include "Physics.h"
#include "Image.h"
#include "Player.h"


HRESULT Physics::Init()
{
	//rect = ImageManager::GetSingleton()->FindImage("Image/character/collisionRect.bmp");

	//tileMapPixel = ImageManager::GetSingleton()->FindImage("Image/tilemap/CollisionPixel.bmp");

	pos.x = 0;
	pos.y = 0;

	fallingSpeed = 0.0f;
	fallingMaxSpeed = 500.0f;

	accelate = 100;

	return S_OK;
}

void Physics::Update()
{
}

void Physics::Render(HDC hdc)
{
}

void Physics::Release()
{
}

void Physics::PhysicsUpdate()
{
}

void Physics::FallingPhysics(float posf)
{
	POINTFLOAT tempPos;
	
	tempPos.y = posf;

	fallingSpeed += accelate * Timer::GetDeltaTime();
	fallingSpeed = min(fallingSpeed, fallingMaxSpeed);

	tempPos.y = pos.y + fallingSpeed * Timer::GetDeltaTime();
}