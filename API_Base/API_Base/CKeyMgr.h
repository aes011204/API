#pragma once
class CKeyMgr
{
private:

	CKeyMgr();
	CKeyMgr(CKeyMgr& rhs) = delete;
	CKeyMgr& operator = (CKeyMgr& rMgr) = delete;
	~CKeyMgr();

public:
	bool Key_Pressing(int iKey); // 누르고 있을떄
	bool Key_Up(int iKey); // 눌렀다가 뗏을 떄
	bool Key_Down(int iKey); // 누르자 마자

	Vector2 GetMousePos() { return m_vCurMousePos; }

	void Key_Update();
private:
	bool m_bCurKeyState[VK_MAX];
	bool m_bPrevKeyState[VK_MAX];

	Vector2 m_vCurMousePos;


#pragma region Singleton
public:
	static CKeyMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CKeyMgr m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion

};

