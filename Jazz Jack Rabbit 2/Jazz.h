#pragma once
#include "PlayerManager.h"


class Jazz : public PlayerManager
{
private:
	int diameter = 0;


public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Jazz() = default;

};

