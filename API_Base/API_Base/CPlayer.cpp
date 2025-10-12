#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CColliderComp.h"
#include "CMonsterBullet.h"
#include "CBoss.h"
#include "CAbstractFactory.h"
#include "CSword01.h"
#include "CAccecery.h"
#include "CInventoryUI.h"
#include "CUIMgr.h"
#include "CStateBar.h"
#include "CQuest.h"
#include "CSoundManager.h"
#include "CCoin.h"
#include "CPlayerBullet.h"

CPlayer::CPlayer() :
	m_eCurState(PS_END), m_ePreState(PS_END), m_fInvincibleTime(0.f), m_bDash(false), m_DashDuration(0.f), m_DashSpeed(0.f), m_DashTime(0.f),
	m_bDropDown(false), m_dropRemain(0.f)
	,m_bStop(false)
{
	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 48.f,60.f }, this));
	m_vCollider.push_back(CColliderComp(ColliderType::ATTACK, { 0,0 }, { 110.f,110.f },this, true));
	m_Equipweapon01.fill(nullptr);
	m_Equipweapon02.fill(nullptr);
	m_EquipAcc.fill(nullptr);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
    m_vSize = { 78.f, 60.f };
    m_vPosition = { WINCX*.5f,WINCY*.5f };
    m_fSpeed = 500.f;
	m_fSpeedY = 500.f;
	m_iMaxHP = 80;
	m_iHP = m_iMaxHP;

	m_iDamage = 10;
    m_ID = PLAYER;

	m_fInvincibleTime = 0.5f;

	m_iMoney = 1000;

	m_DashSpeed = 500.f;
	m_DashDuration = 5.f;
	m_DashTime = .5f;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerIdle.bmp", L"PlayerIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerRun.bmp", L"PlayerRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerJump.bmp", L"PlayerJump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerDie.bmp", L"PlayerDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RunEffectL.bmp", L"RushDust");

	m_pFrameKey = L"PlayerIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 78.f, 60.f };

	
	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 5;
	m_tEFFrame.dwSpeed = .1f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 48,48 };

	EffTime = .5f;
	EffTimeMax = EffTime;

	m_AttackTime = 0.f;
	m_AttackTimeMax = m_AttackTime;
	m_iMoney = 1000 ;

	m_ChangeEquip = 0;
	//ZCWeapon* tmp = dynamic_cast<CWeapon*>(CAbstractFactory<CSword01>::Create());
	//tmp->Set_Target(this);
	//tmp->SetItemState(CItem::EQUIP);
	//weapon = tmp;

	m_Inven = new CInventory();
	m_Inven->Initialize();
	m_Inven->Set_Player(this);

	CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI(this));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CInventoryUI>::CreateUI(this));

}

int CPlayer::Update()
{

	if (m_bDead)
	{
		m_pFrameKey = L"PlayerDie";
		//return OBJ_DEAD;// 일단 플레이어는 삭제 하면 안되는데 일단 임시로
	}

	// 누적시간 제는용
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();
	accTime += dt;

	m_AttackTime -= dt;
	if (m_AttackTime <= 0 && m_bOnAttack == true)
	{
		m_bOnAttack = false;
		m_AttackTime = m_AttackTimeMax;
	}

    Key_Input();

    __super::Update_Rec();
	LimitPlayerPos();
	CCreature::Update();

	if (m_bDash)
	{
		Dash(m_vDashDir);
	}

	m_vBarrelPos = m_vPosition + (m_vBarrelDir * 20);
	//weapon->Update();

	{
		// 장착 무기 업데이트
		if (!m_ChangeEquip)
		{
			for (auto& wep : m_Equipweapon01)
			{
				if (wep == nullptr)
					continue;
				wep->Update();
			}
		}
		else
		{
			for (auto& wep : m_Equipweapon02)
			{
				if (wep == nullptr)
					continue;
				wep->Update();
			}
		}
	
		for (auto& acc : m_EquipAcc)
		{
			if (acc == nullptr)
				continue;
			acc->Update();
		}
	}



	
	__super::UpdateColl(m_vPosition);
	__super::EffUpdate();


	
	/*for (auto& inven : EquipInven)
	{
		inven != nullptr
	}*/






	Motion_Change(); 

	CCreature::Move_Frame();
	//CCreature::Move_EffectFrame();

	m_Inven->Update();


	if (m_quest == true)
	{
		//CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CQuest>::CreateUI(this));
		m_quest = false;
	}

    return 0;

}

void CPlayer::Late_Update()
{
	if (m_bDropDown)
	{
		m_dropRemain -= CTimeMgr::Get_Instance()->GetDeltaTime();

		if (m_dropRemain <= 0)
			m_bDropDown = false;
	}
	{
		
			// 장착 무기 업데이트
			if (!m_ChangeEquip)
			{
				for (auto& wep : m_Equipweapon01)
				{
					if (wep == nullptr)
						continue;
					wep->Late_Update();
				}
			}
			else
			{
				for (auto& wep : m_Equipweapon02)
				{
					if (wep == nullptr)
						continue;
					wep->Late_Update();
				}
			}

			for (auto& acc : m_EquipAcc)
			{
				if (acc == nullptr)
					continue;
				acc->Late_Update();
			}
		
	}

	//m_Inven->Late_Up
}

void CPlayer::Render(HDC hdc)
{
	if (m_visible == false)
		return;
	{
		// 장착 무기 업데이트
		if (!m_ChangeEquip)
		{
			for (auto& wep : m_Equipweapon01)
			{
				if (wep == nullptr)
					continue;
				wep->Render(hdc);
			}
		}
		else
		{
			for (auto& wep : m_Equipweapon02)
			{
				if (wep == nullptr)
					continue;
				wep->Render(hdc);
			}
		}

		for (auto& acc : m_EquipAcc)
		{
			if (acc == nullptr)
				continue;
			acc->Render(hdc);
		}
	}

    //Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

   // Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	
		
		Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
		Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);
	
		// 스프라이트시트에서 가져올 소스 사각형(프레임)
		int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스


		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			centerS.x - RenderSize.x * 0.5f,
			centerS.y - RenderSize.y * 0.5f,
			RenderSize.x, RenderSize.y,
			hMemDC, srcX, m_vSize.y*(int)m_eDir, (int)m_vSize.x, (int)m_vSize.y,
			RGB(255, 0, 255));
	

		//Move_EffectFrame(hdc);
	//
		Vector2 RenderBarrelPos = CCamera::Get_Instance()->GetRenderPos(m_vBarrelPos);

	//m_vBarrelPos = centerS + ( m_vBarrelDir*30);

	//MoveToEx(hdc, static_cast<int>(centerS.x) , static_cast<int>(centerS.y) , nullptr);
	//LineTo(hdc, static_cast<int>(RenderBarrelPos.x) , static_cast<int>(RenderBarrelPos.y));

	
	{
		// 원래 거
    //GdiTransparentBlt(hdc,
    //    RenderPos.x - m_vSize.x*.5f,
    //    RenderPos.y - m_vSize.y*.5f,
    //    (int)m_vSize.x,
    //    (int)m_vSize.y,
    //    hMemDC,
	//	m_tFrame.iStart * (int)m_vSize.x,
	//	m_tFrame.iMotion * (int)m_vSize.y,
    //    (int)m_vSize.x,
    //    (int)m_vSize.y,
    //    RGB(255, 0, 255));
	}

   // BitBlt(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom, hMemDC, 0, 0, SRCCOPY); // 지우는 거 안쓸거면 이거 해야 랜더링됨

	__super::RenderColl(hdc, m_vPosition);
	__super::EffRender(hdc);

	
}

void CPlayer::Release()
{
	m_Inven->Release();
}

void CPlayer::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	
	switch (obj->Get_ID())
	{
	case BOSS:
		//
			if (my.GetType() == ColliderType::ATTACK&&other.GetType()== ColliderType::BODY)
			{
				if (m_bOnAttack == true)
				{
					if (CBoss* creature = dynamic_cast<CBoss*>(obj))
						creature->Take_Damage(m_iDamage);
					float m_fVolume = 20.f;
					CSoundManager::Get_Instance()->PlayFX(L"Hit_Monster.wav", SOUND_EFFECT, m_fVolume);

				}
			}
			break;

	case MONSTER:
	{
		//if(CMonster* creature = dynamic_cast<CMonster*>(obj))
		//	Take_Damage(creature->Get_Damage());
		if (my.GetType() == ColliderType::ATTACK && other.GetType() == ColliderType::BODY)
		{
			if (m_bOnAttack == true)
			{
				if (CCreature* creature = dynamic_cast<CCreature*>(obj))
					creature->Take_Damage(m_iDamage);
				float m_fVolume = 20.f;
				CSoundManager::Get_Instance()->PlayFX(L"Hit_Monster.wav", SOUND_EFFECT, m_fVolume);

			}
		}
	
	}
	break;
	case BULLET:
	{
		if (dynamic_cast<CPlayerBullet*>(obj))
			return;
		else
		{
			Take_Damage(dynamic_cast<CCreature*>(obj)->Get_Damage());
	
			//Vector2 dir = m_vPosition - mon->Get_Position();
			//dir = Vector2::Nomalize(dir);
			//
			//m_vPosition.x += dir.x * 15.f;
			//m_vPosition.y += dir.y * 30.f;
		}
	}
	break;
	case ITEM:
	{
		if (dynamic_cast <CCoin*>(obj))
		{
			m_iMoney += obj->Get_Money();
			obj->Set_Dead(true);
		}

	}
	break;
	case PLATFORM:
	{
			//CObj::Update_Rec();
		
		
		if (!m_bDropDown)
		{
			if(my.GetType()==ColliderType::BODY)
 				Landed_Platform(obj, my, other);
		//m_bPlayerLanded = true;
			//// 충돌판정용 RECT 갱신
		}
	}
	break;
	default:
		break;
	}

	
}

void CPlayer::Key_Input()
{
	if (m_bStop == true)
	{
		m_pFrameKey = L"PlayerIdle";
		m_eCurState = IDLE;
		return;
	}

	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();

	float fY(0.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		Vector2 mos = CKeyMgr::Get_Instance()->GetMousePos();
		mos = CCamera::Get_Instance()->GetRealPos(mos);
		m_vDashDir = (mos - m_vPosition).GetNomalized();
		m_bDash = true;
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"Dash.wav", SOUND_EFFECT, m_fVolume);

	}
	else if ( CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && (CKeyMgr::Get_Instance()->Key_Pressing('S')))
	{
		m_bDropDown = true;
		m_dropRemain = .2f;
			m_pFrameKey = L"PlayerJump";
		m_eCurState = JUMP;
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"Jumping.wav", SOUND_EFFECT, m_fVolume);
		CSoundManager::Get_Instance()->StopSound(CHANNELID::WALK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"Jumping.wav", SOUND_EFFECT, m_fVolume);
		CSoundManager::Get_Instance()->StopSound(CHANNELID::WALK);
	}
	 else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
        m_vPosition.x -= m_fSpeed * dt;
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;
		EffTime -= dt;
		if (EffTime < 0.f)
		{
			m_vEffect.push_back(CEffectComp({ 24,10 }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y },L"RushDust"));
			EffTime = EffTimeMax;
		}
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlaySound(L"step_lth1.wav", CHANNELID::WALK, m_fVolume);


	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
        m_vPosition.x += m_fSpeed * dt;
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;
		EffTime -= dt;
		if (EffTime < 0.f)
		{
			m_vEffect.push_back(CEffectComp({ -24,10 }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"RushDust"));
			EffTime = EffTimeMax;
		}
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlaySound(L"step_lth1.wav", CHANNELID::WALK, m_fVolume);

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}
	else
	{
		m_pFrameKey = L"PlayerIdle";
		m_eCurState = IDLE;
	}



	if (m_bJump||m_bDash)
	{
	m_pFrameKey = L"PlayerJump";
	m_eCurState = JUMP;

	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{

		if (!m_ChangeEquip)
		{
			for (auto& wep : m_Equipweapon01)
			{
				if (wep == nullptr)
					continue;
				if (dynamic_cast<CWeapon*>(wep)->GetWeaponType() == CWeapon::SWORD)
				{
					m_bOnAttack = true;
					/*float m_fVolume = 20.f;
					CSoundManager::Get_Instance()->PlayFX(L"Equip.wav", SOUND_EFFECT, m_fVolume);*/

				}
			}
		}
		else
		{
			for (auto& wep : m_Equipweapon02)
			{
				if (wep == nullptr)
					continue;
				//if (wep->GetItemType() == CItem::ONEHAND || wep->GetItemType() == CItem::TWOHAND)
				//	m_bOnAttack = true;
				if (dynamic_cast<CWeapon*>(wep)->GetWeaponType() == CWeapon::SWORD)
				{
					m_bOnAttack = true;
					//float m_fVolume = 20.f;
					//CSoundManager::Get_Instance()->PlayFX(L"Equip.wav", SOUND_EFFECT, m_fVolume);

				}
			}
		}

		
	}


	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		// 능력치 정보창
	}
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_ChangeEquip = !m_ChangeEquip;
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"Swap_weapon.wav", SOUND_EFFECT, m_fVolume);

	}

	// 마우스 정보 가져오기
	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	
	//CCamera::Get_Instance()->GetRealPos(LeftRight);
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 worldmouse = CCamera::Get_Instance()->GetRealPos(mouse);
	{
		m_vBarrelDir = Vector2::Nomalize(worldmouse - m_vPosition);
	}
	if (worldmouse.x > m_vPosition.x)
	{
		m_eDir = RIGHT;
	}
	else
	{
		m_eDir = LEFT;
	}
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 78.f, 60.f };
			m_vSize = m_tFrame.vSize;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			
			m_tFrame.dwSpeed = .1f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 78.f, 60.f };
			m_vSize = m_tFrame.vSize;
			break;

		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;			
			m_tFrame.dwSpeed = 2.f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 75.f, 60.f };
			m_vSize = m_tFrame.vSize;

			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;

			break;

		case DASH:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;
			break;

		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.dwSpeed =.2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 78.f, 75.f };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}



}



void CPlayer::Take_Damage(int damage)
{
	
	if (accTime > m_fInvincibleTime)
	{
	float m_fVolume = 20.f;
	CSoundManager::Get_Instance()->PlayFX(L"Hit_Player.wav", SOUND_EFFECT, m_fVolume);

		if (m_iHP - damage > 0)
			Set_HP(m_iHP - damage);
		else
		{
			Set_HP(0);
			//m_bDead = true;
			//todo 죽었어! 플레이어 사망 조건 true로 설정
		}
		accTime = 0.f;
	}
}

void CPlayer::Dash(Vector2 tmpdir)
{

		{

			m_vPosition.x += m_DashSpeed *( tmpdir.x * CTimeMgr::Get_Instance()->GetDeltaTime());
			m_vPosition.y += 1200 *( tmpdir.y * CTimeMgr::Get_Instance()->GetDeltaTime());
		
			m_DashTime -= CTimeMgr::Get_Instance()->GetDeltaTime();
			if (m_DashTime <= 0.f)
			{
				m_bDash = false;
				m_DashTime = .5f;
				//m_Stepback = false;
			}
			m_bPlayerLanded = false;

		}
	
}


void CPlayer::LimitPlayerPos()
{
	Vector2 pos = m_vPosition;
	pos.x = Clamp(pos.x, CCamera::Get_Instance()->GetLookAt().x - WINCX * .5f, CCamera::Get_Instance()->GetLookAt().x + WINCX * .5f);
	pos.y = Clamp(pos.y, CCamera::Get_Instance()->GetLookAt().y- WINCY * .5f, CCamera::Get_Instance()->GetLookAt().y + WINCY * .5f);

	m_vPosition = pos;
}



int CPlayer::Equip_Item(int invenIndex, CItem* pInvenItem, int num, int setIndex)
{

	array<CItem*,2>& weaponSlots = (setIndex == 0) ? m_Equipweapon01 : m_Equipweapon02;

	CItem::ITEMTYPE eType = pInvenItem->GetItemType();

	//장착된 아이템이 이미 있는경우

	if (eType == CItem::ACCECERY)
	{

		if (m_EquipAcc[num] != nullptr)
		{
			Item_Ability(-m_EquipAcc[num]->GetDamage(), -m_EquipAcc[num]->Get_Defense());
			m_EquipAcc[num]->SetItemState(CItem::UNEQUIP);
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(m_EquipAcc[num], m_Inven->Check_emptySlot());
			m_EquipAcc[num] = nullptr;
		}
		
			Item_Ability(pInvenItem->GetDamage(), pInvenItem->Get_Defense());
			pInvenItem->SetItemState(CItem::EQUIP);
			m_EquipAcc[num] = pInvenItem;
			m_Inven->moved_Item(invenIndex);
	

	}
	else if (eType == CItem::SUBWEAPON)
	{
		if (num == 0)
			return-1;
	
		if (weaponSlots[0]!= nullptr && weaponSlots[0]->GetItemType() == CItem::TWOHAND) // 2번에 잩
			return-1;
	
		if (weaponSlots[num] != nullptr)
		{
			Item_Ability(-weaponSlots[num]->GetDamage(), -weaponSlots[num]->Get_Defense());
			weaponSlots[num]->SetItemState(CItem::UNEQUIP);
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(weaponSlots[num], m_Inven->Check_emptySlot());
			dynamic_cast<CWeapon*>(weaponSlots[num])->Set_Target(nullptr);//
			weaponSlots[num] = nullptr;
		}

		Item_Ability(pInvenItem->GetDamage(), pInvenItem->Get_Defense());
		pInvenItem->SetItemState(CItem::EQUIP);
		dynamic_cast<CWeapon*>(pInvenItem)->Set_Target(this);//
		weaponSlots[num] = pInvenItem;
		m_Inven->moved_Item(invenIndex);

	}
	else if(eType == CItem::ONEHAND)
	{
		if (num == 1)
			return-1;

		if (weaponSlots[num] != nullptr)
		{
			Item_Ability(-weaponSlots[num]->GetDamage(), -weaponSlots[num]->Get_Defense());
			weaponSlots[num]->SetItemState(CItem::UNEQUIP);
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(weaponSlots[num], m_Inven->Check_emptySlot());
			dynamic_cast<CWeapon*>(weaponSlots[num])->Set_Target(nullptr);//
			weaponSlots[num] = nullptr;
		}
		
		if (weaponSlots[num] != nullptr)
		{
			Item_Ability(-weaponSlots[num]->GetDamage(), -weaponSlots[num]->Get_Defense());
			weaponSlots[num]->SetItemState(CItem::UNEQUIP);
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(weaponSlots[num], m_Inven->Check_emptySlot());
			dynamic_cast<CWeapon*>(weaponSlots[num])->Set_Target(nullptr);//
			weaponSlots[num] = nullptr;
		}
		
			Item_Ability(pInvenItem->GetDamage(), pInvenItem->Get_Defense());
			pInvenItem->SetItemState(CItem::EQUIP);
			dynamic_cast<CWeapon*>(pInvenItem)->Set_Target(this);//
			weaponSlots[num] = pInvenItem;
			m_Inven->moved_Item(invenIndex);
		
	}
	else if (eType == CItem::TWOHAND)
	{
		if (num == 1) // 1번은 양손 무기 장착 안됨
			return-1;
		
		if (weaponSlots[num] != nullptr)
		{
			Item_Ability(-weaponSlots[num]->GetDamage(), -weaponSlots[num]->Get_Defense());
			weaponSlots[num]->SetItemState(CItem::UNEQUIP);
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(weaponSlots[num], m_Inven->Check_emptySlot());
			dynamic_cast<CWeapon*>(weaponSlots[num])->Set_Target(nullptr);//
			weaponSlots[num] = nullptr;
		}
		
			Item_Ability(pInvenItem->GetDamage(), pInvenItem->Get_Defense());
			pInvenItem->SetItemState(CItem::EQUIP);
			dynamic_cast<CWeapon*>(pInvenItem)->Set_Target(this);//
			weaponSlots[num] = pInvenItem;
			m_Inven->moved_Item(invenIndex);


			if (weaponSlots[1] != nullptr)
			{
				// 1번창 장착 해제
				Item_Ability(-weaponSlots[1]->GetDamage(), -weaponSlots[1]->Get_Defense());
				weaponSlots[1]->SetItemState(CItem::UNEQUIP);
				if (m_Inven->Check_emptySlot() == -1)
					return-1;
				m_Inven->Unequip_Item(weaponSlots[1], m_Inven->Check_emptySlot());
				dynamic_cast<CWeapon*>(weaponSlots[1])->Set_Target(nullptr);//
				weaponSlots[1] = nullptr;
			}
		
	}
	return 0;
}



int CPlayer::Unequip_Item(int num, CInventoryUI::INVENTYPE type, int dst)
{


	//CItem::ITEMTYPE eType = pInvenItem->GetItemType();
	int i = m_Inven->Check_IsEmpty(dst);

	if (i == -1)
		return -1;

	if (type == CInventoryUI::EQUIP01)
	{
		if (m_Equipweapon01[num] != nullptr)
		{
			Item_Ability(-m_Equipweapon01[num]->GetDamage(), -m_Equipweapon01[num]->Get_Defense());
			m_Equipweapon01[num]->SetItemState(CItem::UNEQUIP);
			dynamic_cast<CWeapon*>(m_Equipweapon01[num])->Set_Target(nullptr);//
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(m_Equipweapon01[num], dst);

			m_Equipweapon01[num] = nullptr;
		}
		//m_Inven->Unequip_Item(m_Equipweapon01[num], dst);

	}
	else if (type == CInventoryUI::EQUIP02)
	{
		if (m_Equipweapon02[num] != nullptr)
		{
			Item_Ability(-m_Equipweapon02[num]->GetDamage(), -m_Equipweapon02[num]->Get_Defense());
			m_Equipweapon02[num]->SetItemState(CItem::UNEQUIP);
			dynamic_cast<CWeapon*>(m_Equipweapon02[num])->Set_Target(nullptr);//
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(m_Equipweapon02[num], dst);
			m_Equipweapon02[num] = nullptr;
		}
		//m_Inven->Unequip_Item(m_Equipweapon02[num],dst);

	}
	else if (type == CInventoryUI::ACC)
	{
		if (m_EquipAcc[num] != nullptr)
		{
			Item_Ability(-m_EquipAcc[num]->GetDamage(), -m_EquipAcc[num]->Get_Defense());
			m_EquipAcc[num]->SetItemState(CItem::UNEQUIP);
			dynamic_cast<CWeapon*>(m_EquipAcc[num])->Set_Target(nullptr);//
			if (m_Inven->Check_emptySlot() == -1)
				return-1;
			m_Inven->Unequip_Item(m_EquipAcc[num], dst);
			m_EquipAcc[num] = nullptr;
		}
		//m_Inven->Unequip_Item(m_EquipAcc[num], dst);
	}
	//else // 인밴인 경우
	//{
	//	if (m_EquipAcc[num] != nullptr)
	//	{
	//		Item_Ability(-m_EquipAcc[num]->GetDamage(), -m_EquipAcc[num]->Get_Defense());
	//		m_EquipAcc[num]->SetItemState(CItem::UNEQUIP);
	//		dynamic_cast<CWeapon*>(m_EquipAcc[num])->Set_Target(nullptr);//
	//		m_EquipAcc[num] = nullptr;
	//	}
	//m_Inven->Unequip_Item(m_EquipAcc[num], dst);
	//
	//
	//}
	return 0;
}

void CPlayer::Item_Ability(int _Attack, int _Hp)
{
	m_iDamage += _Attack;
	m_iMaxHP += _Hp;
	m_iHP = min(m_iHP, m_iMaxHP);
}

CItem* CPlayer::Get_InvenItem(int index, int EquipInvenNum)
{
	if (EquipInvenNum == 0)
	{
		if (index <0 || index > m_Equipweapon01.size())
			return nullptr;
		else
			return m_Equipweapon01[index];
	}
	else if (EquipInvenNum == 1)
	{
		if (index <0 || index > m_Equipweapon02.size())
			return nullptr;
		else
			return m_Equipweapon02[index];
	}
	else if (EquipInvenNum == 2)
	{
		if (index <0 || index > m_EquipAcc.size())
			return nullptr;
		else
			return m_EquipAcc[index];
	}
	else
		return nullptr;

}

