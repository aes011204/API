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

	const Vector2& Get_StartCurser() const { return m_vStartCurser; }
	const Vector2& Get_EndCurser()   const { return m_vEndCurser; }

	void Set_StartCurser(const Vector2& vStart) { m_vStartCurser = vStart; }
	void Set_EndCurser(const Vector2& vEnd) { m_vEndCurser = vEnd; }

	bool Is_Selecting() const { return m_bSelecting; }

	void Set_Selecting(bool bFlag) { m_bSelecting = bFlag; }


public:
	void		Save_Data();
	void		Load_Data();
	//void Picking(Vector2 pt, Vector2 iDrawID, int iOption, bool isLeft);
	void Picking(Vector2 pt, Vector2 iDrawID, int iOption, TILEDIR dir);
	void FillRec();

	void Set_PipetID(Vector2 mos);


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
	Vector2 m_vOriTileSize;
	Vector2 m_vTileSiteSize = {512,512};
	Vector2 m_vTotalTileNum;
	Vector2 m_vMapSize;

	Vector2 m_vStartCurser, m_vEndCurser;

	Vector2 m_vPipetID;

	bool m_bSelecting;
};

