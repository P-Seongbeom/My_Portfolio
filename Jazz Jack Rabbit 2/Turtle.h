#pragma once
#include "GameObject.h"


class Image;
class Turtle : public GameObject
{
private:
	//Image* Turtle;

	
	
	void walkMotion();
	void hiddingHeadMotion();
	void attackMotion();
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Turtle() = default;
};

