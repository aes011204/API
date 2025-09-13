#pragma once
class CMyBmp;
class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();
	CBmpMgr(CBmpMgr& rhs) = delete;
	CBmpMgr& operator= (CBmpMgr& rMgr) = delete;

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release();

private:
	map<const TCHAR*, CMyBmp*> m_mapBit;


#pragma region Singleton
public:
	static CBmpMgr* Get_Instance()
	{
		static CBmpMgr* s_Instance = new CBmpMgr();

		return s_Instance;
	}
#pragma endregion
};

