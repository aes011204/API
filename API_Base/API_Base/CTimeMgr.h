#pragma once
class CTimeMgr
{
private:
	CTimeMgr();
	CTimeMgr(CTimeMgr& rhs) = delete;
	CTimeMgr& operator = (CTimeMgr& rMgr) = delete;
	~CTimeMgr();

public:
	void Initialize();
	int Update();


private:
	LARGE_INTEGER m_llCurCount; // 현재 시점의 QPC 값
	LARGE_INTEGER m_llPrevCount; // 이전 프레임 시점의 QPC 값
	LARGE_INTEGER m_llFrequency; // 초당 카운터 증가 횟수 (QPC 주파수)

	double m_dDeltaTime; // (float or double으로) 
	//한 프레임 도는 동안의 시간 값(처음 인잇 시간 - 한바퀴 돌고 업뎃 시간 / 1초당 카운트)
	double m_dAcc; // 1초 체크를 위한 누적 시간 값

	UINT m_iCallCount; // 초당 호출 횟수
	UINT m_iFPS;

public:
	double GetDeltaTime() { return m_dDeltaTime; }

#pragma region Singleton
public:
	static CTimeMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CTimeMgr m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion

};

