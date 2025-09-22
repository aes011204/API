#include "pch.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CCamera.h"
//#include "ScrollMgr.h"



CTileMgr::CTileMgr() : m_bSelecting(false)
{

	
	m_vecTile.reserve(m_vTotalTileNum.x * m_vTotalTileNum.y);

	m_vOriTileSize = { 16,16 };
	m_vTileSize = m_vOriTileSize * 3;
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	m_vMapSize = { 1050,1050 };
	//m_vTotalTileNum = { 32, 32 };


	m_vTotalTileNum.x = 22;// (int)ceil(m_vMapSize.x / m_vTileSize.x);
		m_vTotalTileNum.y = 22;//(int)ceil(m_vMapSize.y / m_vTileSize.y);

	for (int i = 0; i < m_vTotalTileNum.y; ++i)
	{
		for (int j = 0; j < m_vTotalTileNum.x; ++j)
		{
			float fX = (float)(m_vTileSize.x /2) + (m_vTileSize.x * j);
			float fY = (float)(m_vTileSize.y /2) + (m_vTileSize.y * i);
			//사이즈는 원래 16 시트, 값을 넘겨주고 위치는 32기준으로 계산한것을 넣어준다
			CObj* pTile = CAbstractFactory<CTile>::CreateTile({ fX, fY }, { m_vOriTileSize });
			m_vecTile.push_back(pTile);
		}
	}

}

void CTileMgr::Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Update();

}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	Vector2 look = CCamera::Get_Instance()->GetLookAt();

	Vector2 center = { WINCX * 0.5f, WINCY * 0.5f };
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vTileSize);

	//화면에 보이는 화면의 좌 상단을 타일 좌표로 지점 의 시작점 센다
	//Vector2  LeftTop = {(int)floor( (look.x - center.x)/ RenderSize.x),(int)floor((look.y - center.y )/ RenderSize.y)};
	//Vector2 m_vScreenTileNum = { (int)ceil(WINCX / RenderSize.x)+2 ,(int)ceil(WINCY / RenderSize.y)+2 };
	//Vector2  RightBottom = m_vScreenTileNum + LeftTop;

	Vector2  screenStart = CCamera::Get_Instance()->GetRealPos({ 0.f, 0.f });
	Vector2  screenEnd = CCamera::Get_Instance()->GetRealPos({WINCX, WINCY});

	Vector2  LeftTop;
	LeftTop.x = (int)floor(screenStart.x / m_vTileSize.x) - 1;
	LeftTop.y = (int)floor(screenStart.y / m_vTileSize.y) - 1;
	Vector2  RightBottom;
	RightBottom.x = (int)ceil(screenEnd.x / m_vTileSize.x) + 1;
	RightBottom.y = (int)ceil(screenEnd.y / m_vTileSize.y) + 1;

	// 맵 경계로 클램프(TILEX / TILEY = 전체 타일 수)
	LeftTop.x = max(0, LeftTop.x);
	LeftTop.y = max(0, LeftTop.y);
	RightBottom.x = min(m_vTotalTileNum.x, RightBottom.x);
	RightBottom.y = min(m_vTotalTileNum.y, RightBottom.y);


	for (int i = LeftTop.y; i < RightBottom.y; ++i)
	{
		for (int j = LeftTop.x; j < RightBottom.x; ++j)
		{
			int iIndex = i * m_vTotalTileNum.x + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

	//_________________________________________________________________

	if (m_bSelecting)
	{
		Vector2 WorldStart = CCamera::Get_Instance()->GetRealPos(m_vStartCurser);
		Vector2 WorldEnd = CCamera::Get_Instance()->GetRealPos(m_vEndCurser);

		//float StartIdx = { WorldStart.y * TILEX + WorldStart.x };
		//float EndIdx = { WorldEnd.y * TILEX + WorldEnd.x };

		Vector2  LeftTop;
		LeftTop.x = (int)floor(WorldStart.x / m_vTileSize.x);
		LeftTop.y = (int)floor(WorldStart.y / m_vTileSize.y);
		Vector2  RightBottom;
		RightBottom.x = (int)ceil(WorldEnd.x / m_vTileSize.x);
		RightBottom.y = (int)ceil(WorldEnd.y / m_vTileSize.y);

		for (int i = LeftTop.y; i < RightBottom.y; ++i)
		{
			for (int j = LeftTop.x; j < RightBottom.x; ++j)
			{
				int iIndex = i * m_vTotalTileNum.x + j;

				if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
					continue;

				
				
				Vector2 pos = CCamera::Get_Instance()->GetRenderPos(m_vecTile[iIndex]->GetPosition());
				Vector2 size =	CCamera::Get_Instance()->GetRenderSize(m_vTileSize);

				RECT r = { pos.x - size.x * .5,pos.y - size.y * .5,pos.x + size.x * .5, pos.y + size.y * .5 };

				HPEN   pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
				HBRUSH hatch = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 255));
				HGDIOBJ oldP = SelectObject(hDC, pen);
				HGDIOBJ oldB = SelectObject(hDC, hatch);
				Rectangle(hDC, r.left, r.top, r.right, r.bottom);
				SelectObject(hDC, oldP);  DeleteObject(pen);
				SelectObject(hDC, oldB);  DeleteObject(hatch);

			}
		}
	}

}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](auto& p) {if (p) { delete p; p = nullptr; }});
	m_vecTile.clear();
}


void CTileMgr::Save_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/BossTile3.dat", // 파일 경로(이름까지 명시)
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 모드 설정 : 공유하지 않음
		NULL,				// 보안 속성 설정 : 기본 값 설정
		CREATE_ALWAYS,		// 생성 방식 : 쓰기 전용인 경우 파일이 없으면 생성하여 저장, OPEN_EXISTING : 읽기 전용 모드일 때 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성 : 일반 파일
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일 주소(사용하지 않기 때문에 null)
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Save Failed", _T("Error"), MB_OK);
		return;
	}


	Vector2 MapSize = m_vTotalTileNum;

	DWORD	dwByte(0);
	Vector2 iDrawID{};
	Vector2 pos{};
	Vector2 size{};
	int	 iOption(0);
	
		
		WriteFile(hFile, &MapSize, sizeof(Vector2), &dwByte, nullptr);

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();
	
		pos = dynamic_cast<CTile*>(pTile)->GetPosition();
		size = dynamic_cast<CTile*>(pTile)->GetSize();

		WriteFile(hFile, &pos, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &size, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}
	
	CloseHandle(hFile);
	
	MessageBox(g_hWnd, L"Save Success", _T("축하"), MB_OK);
}

void CTileMgr::Load_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/BossTile2.dat", // 파일 경로(이름까지 명시)
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 모드 설정 : 공유하지 않음
		NULL,				// 보안 속성 설정 : 기본 값 설정
		OPEN_EXISTING,		// 생성 방식 : 쓰기 전용인 경우 파일이 없으면 생성하여 저장, OPEN_EXISTING : 읽기 전용 모드일 때 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성 : 일반 파일
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일 주소(사용하지 않기 때문에 null)
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("Error"), MB_OK);
		return;
	}
	
	Vector2 MapSize{};
	DWORD	dwByte(0);
	Vector2 iDrawID{};
	Vector2 pos{};
	Vector2 size{};
	int		 iOption(0);
	
	Release();
	
		ReadFile(hFile, &MapSize, sizeof(Vector2), &dwByte, nullptr);
	while (true)
	{
		ReadFile(hFile, &pos, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &size, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

	
		if (0 == dwByte)
			break;
	
		CObj* pTile = CAbstractFactory<CTile>::CreateTile(pos,size);
		//m_vMapSize = MapSize;
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
		m_vecTile.push_back(pTile);		
	}
	m_vTotalTileNum = MapSize;
	//m_vTotalTileNum.x = (int)ceil(m_vMapSize.x / m_vTileSize.x);
	//m_vTotalTileNum.y = (int)ceil(m_vMapSize.y / m_vTileSize.y);

	CloseHandle(hFile);
	
	MessageBox(g_hWnd, L"Load Success", _T("축하"), MB_OK);
}

void CTileMgr::Picking(Vector2 pt, Vector2 iDrawID, int iOption, TILEDIR dir)
{
	Vector2 mos = CCamera::Get_Instance()->GetRealPos(pt);

	int x = (mos.x / m_vTileSize.x);
	int y = (mos.y / m_vTileSize.y);

	int iIndex = y * m_vTotalTileNum.x + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;
	//iDrawId.y = iDrawId.y + 1;


	Vector2 id = dynamic_cast<CTile*>(m_vecTile[iIndex])->Get_DrawID();

	switch (dir)
	{	
	case TDIR_TOP:
		if (id.y  <=0)
			return;
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID({ id.x,id.y -1 });
		break;
	case TDIR_DOWN:
		if (id.y  >= (m_vTileSiteSize /m_vOriTileSize).y)
			return;
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID({ id.x,id.y + 1 });
		break;
	case TDIR_LEFT:
		if (id.x <= 0)
			return;
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID({ id.x - 1,id.y});
		break;
	case TDIR_RIGHT:
		if (id.y >= (m_vTileSiteSize / m_vOriTileSize).x)
			return;
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID({ id.x + 1,id.y });
		break;
	}

	//dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

}
void CTileMgr::FillRec()
{
	Vector2 WorldStart = CCamera::Get_Instance()->GetRealPos(m_vStartCurser);
	Vector2 WorldEnd = CCamera::Get_Instance()->GetRealPos(m_vEndCurser);

	//float StartIdx = { WorldStart.y * TILEX + WorldStart.x };
	//float EndIdx = { WorldEnd.y * TILEX + WorldEnd.x };

	Vector2  LeftTop;
	LeftTop.x = (int)floor(WorldStart.x / m_vTileSize.x) ;
	LeftTop.y = (int)floor(WorldStart.y / m_vTileSize.y) ;
	Vector2  RightBottom;
	RightBottom.x = (int)ceil(WorldEnd.x / m_vTileSize.x) ;
	RightBottom.y = (int)ceil(WorldEnd.y / m_vTileSize.y) ;

	for (int i = LeftTop.y; i < RightBottom.y; ++i)
	{
		for (int j = LeftTop.x; j < RightBottom.x; ++j)
		{
			int iIndex = i * m_vTotalTileNum.x + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			/*m_vPipetID = { 3,3 };*/
			dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(m_vPipetID);
			//dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

		}
	}
}

void CTileMgr::Set_PipetID(Vector2 mos)
{
	Vector2 WorldMos = CCamera::Get_Instance()->GetRealPos(mos);
	int x = (WorldMos.x / m_vTileSize.x);
	int y = (WorldMos.y / m_vTileSize.y);

	int iIndex = y * m_vTotalTileNum.x + x;

	m_vPipetID = dynamic_cast<CTile*>(m_vecTile[iIndex])->Get_DrawID();
	
}
