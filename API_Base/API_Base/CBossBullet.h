#pragma once
#include "CBullet.h"
class CBossBullet :
    public CBullet
{
public:


	CBossBullet();
	~CBossBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	//void Start();

public:

	virtual void Do_Attack() {}
	virtual void Take_Damage(float _fDamage) {}

	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
	void Take_Damage(int _damage) override;
	void Motion_Change();

private:
	float delayT =0.f;
	float delayTMax=0.f;

	Vector2 tmpDir;
	FRAME m_tEffFrame;

	float endtime;
	float endtimeMax;

	bool tmpboo;


	//회전 이미지

	Vector2 RealCorners[4];
	Vector2 half;
	Vector2 corners[4];
	POINT plgCorner[3];
	
};

