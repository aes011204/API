#pragma once

#include "CTile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void Picking(POINT pt, Vector2 iDrawID, int iOption);

	//void    Picking(POINT pt, int iDrawID, int iOption);
public:
	void		Save_Data();
	void		Load_Data();

#pragma region Singleton
public:
	static CTileMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CTileMgr m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion
	vector<CObj*>	m_vecTile;

	Vector2 m_vTileSize;
};

