#include "pch.h"
#include "CItem.h"


CItem::CItem() 
{
	iQuantity++;
}

CItem::~CItem()
{
}

void CItem::AddQuantity(int _iQuantity)
{
	iQuantity += _iQuantity;
}

void CItem::MinusQuantity(int _iQuantity)
{
	iQuantity -= _iQuantity;
}

void CItem::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}

