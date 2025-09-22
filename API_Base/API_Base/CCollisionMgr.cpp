#include "pch.h"
#include "CCollisionMgr.h"
#include "CObj.h"
#include "CCreature.h"
#include "CColliderComp.h"

//void CCollisionMgr::Collision_Rect(list<CObj*> src, list<CObj*> dst)
//{
//
//	RECT tmpRc = {};
//	for (auto& Dst : dst)
//	{
//		for (auto& Src : src)
//		{
//			if (IntersectRect(&tmpRc, Dst->Get_Rect(), Src->Get_Rect()))
//			{
//				Dst->On_Collision(Src);
//				Src->On_Collision(Dst);
//			}
//		}
//	}
//}

void CCollisionMgr::Collision_Rect(list<CObj*> src, list<CObj*> dst)
{

	RECT tmpRc = {};
	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			for (auto& colDst : Dst->Get_Collider())
			{
				for (auto& colSrc : Src->Get_Collider())
				{
					if (IntersectRect(&tmpRc, colDst.Get_Rect(), colSrc.Get_Rect()))
					{
						//	CColliderComp::[ColliderType] tmp =colDst.GetType();
						Dst->On_Collision(Src, colDst, colSrc);
						Src->On_Collision(Dst, colSrc, colDst);
					}
				}
			}

		}
	}
}


//void CCollisionMgr::Collision_Circle(list<CObj*> src, list<CObj*> dst)
//{
//	// 정사각형, 원 만 가능함
//	for (auto& Dst : dst)
//	{
//		for (auto& Src : src)
//		{
//			if (Check_Circle(Dst, Src))
//			{
//				Dst->On_Collision(Src);
//				Src->On_Collision(Dst);
//			}
//		}
//	}
//}

void CCollisionMgr::Collision_Circle(list<CObj*> src, list<CObj*> dst)
{
	// 정사각형, 원 만 가능함
	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			for (auto& colDst : Dst->Get_Collider())
			{
				for (auto& colSrc : Src->Get_Collider())
				{
					if (Check_Circle(colDst, colSrc))
					{
						Dst->On_Collision(Src, colDst, colSrc);
						Src->On_Collision(Dst, colSrc, colDst);
					}
				}
			}
		}
	}
}


bool CCollisionMgr::Check_Circle(CColliderComp& src, CColliderComp& dst)
{

	// 정사각형, 원 만 가능함
	float width = fabsf(src.GetColPosition().x - dst.GetColPosition().x);
	float height = fabsf(src.GetColPosition().y - dst.GetColPosition().y);

	float distance = sqrt((width * width) + (height * height));

	if (distance <= (src.GetColSize().x * .5f) + (dst.GetColSize().x * .5f))
	{
		return true;
	}
}

//void CCollisionMgr::Collision_RectEx(list<CObj*> src, list<CObj*> dst)
//{
//	float fx = 0.f;
//	float fy = 0.f;
//
//	for (auto& Dst : dst)
//	{
//		for (auto& Src : src)
//		{
//			if (Check_Rect(Src, Dst, &fx, &fy))
//			{
//				if (fy > fx) // 좌우 충돌
//				{
//					if (Src->GetPosition().x > Dst->GetPosition().x) // 우 충돌
//					{
//						Src->SetPosition({ Src->GetPosition().x + fx,Src->GetPosition().y });
//					}
//					else // 좌충돌
//					{
//						Src->SetPosition({ Src->GetPosition().x - fx,Src->GetPosition().y });
//
//					}
//				}
//				else // 상하 충돌
//				{
//					if (Src->GetPosition().y > Dst->GetPosition().y) // 하 충돌
//					{
//						Src->SetPosition({ Src->GetPosition().x,Src->GetPosition().y + fy });
//					}
//					else // 상 충돌
//					{
//						Src->SetPosition({ Src->GetPosition().x ,Src->GetPosition().y - fy });
//
//					}
//				}
//
//			}
//		}
//	}
//
//}


void CCollisionMgr::Collision_RectEx(list<CObj*> src, list<CObj*> dst)
{
	float fx = 0.f;
	float fy = 0.f;

	for (auto& Dst : dst)
	{
		for (auto& Src : src)
		{
			for (auto& colDst : Dst->Get_Collider())
			{
				for (auto& colSrc : Src->Get_Collider())
				{
					if (colSrc.GetType() != ColliderType::BODY)
						continue;
					 
					if (Check_Rect(colSrc, colDst, &fx, &fy))
					{
						if (fy > fx) // 좌우 충돌
						{
							if (Src->GetPosition().x > Dst->GetPosition().x) // 우 충돌
							{
								Src->SetPosition({ Src->GetPosition().x + fx, Src->GetPosition().y });
							}
							else // 좌충돌
							{
								Src->SetPosition({ Src->GetPosition().x - fx, Src->GetPosition().y });
						
							}
						}
						else // 상하 충돌
						{
							if (Src->GetPosition().y > Dst->GetPosition().y) // 하 충돌
							{
								Src->SetPosition({ Src->GetPosition().x,Src->GetPosition().y + fy });
							}
							else // 상 충돌
							{
								Src->SetPosition({ Src->GetPosition().x ,Src->GetPosition().y - fy });
						
							}
						}
					}
				}
			}
		}
	}

}
//bool CCollisionMgr::Check_Rect(CObj* src, CObj* dst, float* pX, float* pY)
//{
//	float distanceX = abs(src->GetColPosition().x - dst->GetColPosition().x);
//	float distanceY = abs(src->GetColPosition().y - dst->GetColPosition().y);
//
//	float radiusX = (src->GetColSize().x * .5f + dst->GetColSize().x * .5f);
//	float radiusY = (src->GetColSize().y * .5f + dst->GetCOlSize().y * .5f);
//
//	if (distanceX <= radiusX && distanceY <= radiusY)
//	{
//		*pX = radiusX - distanceX;
//		*pY = radiusY - distanceY;
//
//		return true;
//	}
//
//	return false;
//}
bool CCollisionMgr::Check_Rect(CColliderComp& src, CColliderComp& dst, float* pX, float* pY)
{
	float distanceX = abs(src.GetColPosition().x - dst.GetColPosition().x);
	float distanceY = abs(src.GetColPosition().y - dst.GetColPosition().y);

	float radiusX = (src.GetColSize().x * .5f + dst.GetColSize().x * .5f);
	float radiusY = (src.GetColSize().y * .5f + dst.GetColSize().y * .5f);

	if (distanceX <= radiusX && distanceY <= radiusY)
	{
		*pX = radiusX - distanceX;
		*pY = radiusY - distanceY;

		return true;
	}

	return false;
}
