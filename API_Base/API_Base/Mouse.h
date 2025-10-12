#pragma once
#include "CObj.h"
class Mouse :  public CObj
{
public:
	Mouse();
	virtual ~Mouse();
	
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	int  GetIsShoot() const { return isShoot; }
	void SetIsShoot(int value) { isShoot = value; }
	
	int isShoot = 0;

	// CObj을(를) 통해 상속됨
	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;


#pragma region Singleton
public:
	static Mouse* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static Mouse m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion

};

