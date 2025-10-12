#pragma once
class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC m_hDC;


	// 더블 버퍼링 추가
	RECT	    m_rect = {};
	HDC			hBackDC = {};
	HBITMAP		m_bmpBack = {};
	
};

