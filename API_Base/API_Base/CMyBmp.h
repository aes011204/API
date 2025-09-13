#pragma once
class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();
public:
	HDC Get_MenDC() { return m_hMemDC; }

public:
	void LoadBmp(const TCHAR* pFilePath);
	void Release();

private:

	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBmp;

};

