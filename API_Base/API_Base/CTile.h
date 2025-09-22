#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    //CTile(Vector2 pos, Vector2 size) {}
    virtual ~CTile();

public:
    Vector2& Get_DrawID() { return m_iDrawID; }
    int& Get_Option() { return m_iOption; }

    void    Set_DrawID(Vector2 iDrawID) { m_iDrawID = iDrawID; }
    void    Set_Option(int iOption) { m_iOption = iOption; }
    
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    //int     m_iDrawID;
    Vector2 m_iDrawID;

    int     m_iOption;

    Vector2 m_vReSize;

    // CObj을(를) 통해 상속됨
    void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)override;

};

