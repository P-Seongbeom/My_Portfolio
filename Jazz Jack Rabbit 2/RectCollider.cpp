#include "RectCollider.h"

void RectCollider::GiveDamageObject1(GameObject* object1, int sizeX1, int sizeY1, GameObject* object2, int sizeX2, int sizeY2)
{
	if (object2->GetHpValue() <= 0) return;
	object1->GetPos();
	object2->GetPos();

	rect2.left = (LONG)(object1->GetPos().x - sizeX1 / 2);
	rect2.right = (LONG)(object1->GetPos().x + sizeX1 / 2);
	rect2.top = (LONG)(object1->GetPos().y - sizeY1);
	rect2.bottom = (LONG)object1->GetPos().y;

	rect3.left = (LONG)(object2->GetPos().x - sizeX2 / 2);
	rect3.right = (LONG)(object2->GetPos().x + sizeX2 / 2);
	rect3.top = (LONG)(object2->GetPos().y - sizeY2);
	rect3.bottom = (LONG)object2->GetPos().y;

	if (IntersectRect(&rect1, &rect2, &rect3))
	{
		object1->GetHit(true);
	}
}

void RectCollider::CollideObjects(GameObject* object1, int sizeX1, int sizeY1, GameObject* object2, int sizeX2, int sizeY2)
{
	object1->GetPos();
	object2->GetPos();

	rect2.left = (LONG)(object1->GetPos().x - sizeX1 / 2);
	rect2.right = (LONG)(object1->GetPos().x + sizeX1 / 2);
	rect2.top = (LONG)(object1->GetPos().y - sizeY1);
	rect2.bottom = (LONG)object1->GetPos().y;

	rect3.left = (LONG)(object2->GetPos().x - sizeX2 / 2);
	rect3.right = (LONG)(object2->GetPos().x + sizeX2 / 2);
	rect3.top = (LONG)(object2->GetPos().y - sizeY2);
	rect3.bottom = (LONG)object2->GetPos().y;

	if (IntersectRect(&rect1, &rect2, &rect3))
	{
		object1->SetRightCollision(true);
	}
}

