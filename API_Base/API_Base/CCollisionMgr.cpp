#include "pch.h"
#include "CCollisionMgr.h"
#include "CObj.h"

void CCollisionMgr::Collision_Rect(list<CObj*> src, list<CObj*> dst)
{

	RECT tmpRc = {};
	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			if (IntersectRect(&tmpRc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->On_Collision(Src);
				Src->On_Collision(Dst);
			}
		}
	}
}

void CCollisionMgr::Collision_Circle(list<CObj*> src, list<CObj*> dst)
{
	// 정사각형, 원 만 가능함
	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->On_Collision(Src);
				Src->On_Collision(Dst);
			}
		}
	}
}

bool CCollisionMgr::Check_Circle(CObj* src, CObj* dst)
{

	// 정사각형, 원 만 가능함
	float width = fabsf(src->GetPosition().x - dst->GetPosition().x);
	float height = fabsf(src->GetPosition().y - dst->GetPosition().y);

	float distance = sqrt((width * width) + (height * height));

	if (distance <= (src->GetSize().x * .5f) + (dst->GetSize().x * .5f))
	{
		return true;
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> src, list<CObj*> dst)
{
	float fx = 0.f;
	float fy = 0.f;

	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			if (Check_Rect(Src, Dst, &fx, &fy))
			{
				if (fy>fx) // 좌우 충돌
				{
					if (Src->GetPosition().x > Dst->GetPosition().x) // 우 충돌
					{
						Src->SetPosition({ Src->GetPosition().x + fx,Src->GetPosition().y });
					}
					else // 좌충돌
					{
						Src->SetPosition({ Src->GetPosition().x - fx,Src->GetPosition().y });

					}
				}
				else // 상하 충돌
				{
					if (Src->GetPosition().y > Dst->GetPosition().y) // 하 충돌
					{
						Src->SetPosition({ Src->GetPosition().x,Src->GetPosition().y +fy});
					}
					else // 상 충돌
					{
						Src->SetPosition({ Src->GetPosition().x ,Src->GetPosition().y -fy});

					}
				}

			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj* src, CObj* dst, float* pX, float* pY)
{
	float distanceX = abs(src->GetPosition().x - dst->GetPosition().x);
	float distanceY = abs(src->GetPosition().y - dst->GetPosition().y);

	float radiusX = (src->GetSize().x * .5f + dst->GetSize().x * .5f);
	float radiusY = (src->GetSize().y * .5f + dst->GetSize().y * .5f);

	if (distanceX <= radiusX && distanceY <= radiusY)
	{
		*pX = radiusX - distanceX;
		*pY = radiusY - distanceY;

		return true;
	}

	return false;
}
