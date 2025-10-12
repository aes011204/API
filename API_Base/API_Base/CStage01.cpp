#include "pch.h"
#include "CStage01.h"
#include "CBmpMgr.h"
#include "CCamera.h"
#include "CObjMgr.h"
#include "CLineManager.h"
#include "CSoundManager.h"
#include "CUIMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CStateBar.h"
#include "CDoor.h"
#include "CMonsterBat.h"
#include "CMonsterBigSkull.h"
#include "CKeyMgr.h"
#include "CMonsterBow.h"

CStage01::CStage01()
{
}

CStage01::~CStage01()
{
	Release();
}

void CStage01::Initialize()
{
	m_vSceneSize = { 640.f * 3.5f, 320.f * 3.5f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/untitled.bmp", L"Stage01");
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetStop(false);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetVisible(true);
	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Get_Player()->SetPosition({ 100,400 });
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBat>::Create({ 475, 310 }, { 60,66 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBat>::Create({ 1779,252 }, { 60,66 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBat>::Create({ 2057,608 }, { 60,66 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBat>::Create({1459,613 }, { 60,66 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBigSkull>::Create({ 550, 400 }, { 99,144 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBow>::Create({ 1759, 400 }, { 99,144 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBow>::Create({ 1259, 400 }, { 99,144 }));
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBigSkull>::Create({ 1973,608 } , { 99,144 }));

	CCamera::Get_Instance()->Bootstrap(CObjMgr::Get_Instance()->Get_Player()->GetPosition());
	CCamera::Get_Instance()->SetBackSize(m_vSceneSize);
	CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	//
	//CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI((CCreature*)CObjMgr::Get_Instance()->Get_Player()));
	//CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CInventoryUI>::CreateUI(dynamic_cast<CCreature*>(CObjMgr::Get_Instance()->Get_Player())));

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CDoor>::Create({ m_vSceneSize.x-50,m_vSceneSize.y - 300 }, { 100,300 }));


	float m_fVolume = 20.f;
	CSoundManager::Get_Instance()->PlayBGM(L"JailField.wav", m_fVolume);

	platformInit();
}

int CStage01::Update()
{
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	//Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	//Vector2 worldmouse = CCamera::Get_Instance()->GetRealPos(mouse);
	//cout << worldmouse.x << " , " << worldmouse.y << endl;
	return 0;
}

void CStage01::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CStage01::Render(HDC hdc)
{

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01");
	Vector2 ImgSize={640,320};
	Vector2 RnederSize = CCamera::Get_Instance()->GetRenderSize(m_vSceneSize);
	Vector2 RnederPos = CCamera::Get_Instance()->GetRenderPos({0,0});
	StretchBlt(hdc, RnederPos.x, RnederPos.y, RnederSize.x, RnederSize.y, hGroundDC, 0, 0, ImgSize.x, ImgSize.y, SRCCOPY);
	//GdiTransparentBlt(hdc, RenderPos1.x+size.x, RenderPos1.y+size.y, size.x, size.y, hGroundDC2, 0, 0, 320, 142, RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(hdc);

	//Line Å×½ºÆ®
	CLineManager::Get_Instance()->Render(hdc);
	CUIMgr::Get_Instance()->Render(hdc);

	HDC h = CBmpMgr::Get_Instance()->Find_Img(L"BatBullet");
	if (h == nullptr)
	{
		printf("");
	}

	GdiTransparentBlt(
		hdc,
		/*centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,*/WINCX * .5f, WINCY * .5f,
		42, 42,
		h, 0, 0, 42, 42,
		RGB(255, 0, 255));


}

void CStage01::Release()
{
	CObjMgr::Get_Instance()->Release();

	//CUIMgr::Get_Instance()->Release();
	CLineManager::Get_Instance()->Release();
	CSoundManager::Get_Instance()->StopAll();
}

void CStage01::platformInit()
{
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 475, 345 }, { 170.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 868, 345 }, { 170.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1765,346 }, { 611.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1455,680 }, { 112.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 2072,680 }, { 112.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1765,680 }, { 273.f,20.f }));



	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1764,849 }, { 170.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1795,963 }, { 880.f,20.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 1795,968 }, { 880.f,20.f }));


	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 85, 140 }, { 190,295 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 1264,180 }, { 290,186 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 1260,740 }, { 290,450 }));

	//CObjMgr::Get_Instance()
	//	->Add_Object(CAbstractFactory<CWall>::Create({ 1056, 388 }, { 195,670 }));
	//

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ m_vSceneSize.x * .5f , 60.f }, { m_vSceneSize.x,109.f }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ m_vSceneSize.x,  m_vSceneSize.y * .3f }, { 220.f,m_vSceneSize.y * .7f }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ WINCX * .5f, 570.f }, { 1250,90 }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ m_vSceneSize.x * .5f , 517.f }, { m_vSceneSize.x,25.f }));

}
