#include "pch.h"
#include "CPlatform.h"


CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
	Release();
}

void CPlatform::Initialize()
{

	m_ID = PLATFORM;
}

int CPlatform::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	__super::Update_Rec();

	return OBJ_NOEVENT;

}

void CPlatform::Late_Update()
{
}

void CPlatform::Render(HDC hdc)
{
	CNonCreature::Render(hdc);
}

void CPlatform::Release()
{
}

void CPlatform::On_Collision(CObj* obj)
{
}