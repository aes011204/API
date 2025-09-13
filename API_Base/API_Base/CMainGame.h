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
};

