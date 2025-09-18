#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	
	void RenderBG(HDC hdc, HDC hGroundDC, Vector2 startPos, Vector2 size);
};

