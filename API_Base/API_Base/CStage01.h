#pragma once
#include "CScene.h"
class CStage01 : public CScene
{
public:
	CStage01();
		~CStage01();

	// CScene을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hdc) override;
	void Release() override;


	void platformInit();
};

