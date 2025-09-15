#pragma once
class CObj;

class CCamera
{
private:
	CCamera();
	virtual ~CCamera();
public:
	void SetLookAt(Vector2 vLook);

	void Bootstrap(const Vector2& startLookAt);

	void SetTarget(CObj* obj) { m_tTargetObj = obj; }
	void CalDiff();


	void SetBackSize(Vector2 _backSize) {m_vBackSize = _backSize;}

	//Vector2 GetRenderPos(Vector2 vPos) { return (vPos - m_vDiff); }
	//Vector2 GetRealPos(Vector2 vRenderPos) { return vRenderPos + m_vDiff; }

	Vector2 GetRenderPos(Vector2 WorldPos) {
		Vector2 center = vWinResolution * 0.5f;
		return (WorldPos - m_vCurLookAt) * m_fZoom + center;
	}

	Vector2 GetRenderSize(Vector2 WorldSize) {
		// 목적지(그려질) 크기 = 원본 프레임 크기 * 줌
		Vector2 RenderSize = {};
		RenderSize.x = (int)(WorldSize.x * m_fZoom);
		RenderSize.y = (int)(WorldSize.y * m_fZoom);
		return RenderSize;
	}

	Vector2 GetRealPos(Vector2 vRenderPos) {
		Vector2 center = vWinResolution * 0.5f;
		return (vRenderPos - center) / m_fZoom + m_vCurLookAt;
	}
	Vector2 GetLookAt() { return m_vCurLookAt; }
	float GetZoom() { return m_fZoom; }

	void Update();
private:
	Vector2 m_vLookAt; // 카메라가 보는 목표 위치
	Vector2 m_vPrevLookAt; // 카메라가 보는 이전프레임 위치
	Vector2 m_vCurLookAt; // 카메라가 보는 현제 프레임 위치
	CObj* m_tTargetObj; // 카메라 타겟 오브젝트

	float m_fTime; // 타겟을 따라가는데 걸리는 시간
	float m_fSpeed;
	float m_fAccTime;
	Vector2 m_vDiff;

	Vector2 vWinResolution = {WINCX, WINCY};

	float m_fZoom ;

	Vector2 m_vBackSize;

#pragma region Singleton
public:
	static CCamera* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CCamera m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion
};

