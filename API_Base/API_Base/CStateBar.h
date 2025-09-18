#pragma once
#include "CUI.h"
#include "CCreature.h"
class CStateBar :
    public CUI
{
public:
    CStateBar();
    ~CStateBar();

    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl() override;

 

private:
    int TargetCurInfo;
    int TargetMaxInfo;
    int OtherInfo;


};

