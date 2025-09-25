#include "pch.h"
#include "CLineManager.h"
#include "Vector2.h"

#include "CStage01.h"



CLineManager::CLineManager()
{
}

CLineManager::~CLineManager()
{
	Release();
}

void CLineManager::Initialize()
{
}

int CLineManager::Update()
{
	return 0;
}

void CLineManager::Late_Update()
{
}

void CLineManager::Render(HDC hDC)
{
	for (auto& line : m_LineList)
	{
		line->Render(hDC);
	}
}

void CLineManager::Release()
{
	for (auto& pLine : m_LineList) {

		Safe_Delete(pLine);
	}
	m_LineList.clear();
}

bool CLineManager::Collision_Line(Vector2 PlayerPos, float* pY)
{
	if (m_LineList.empty())
		return false;

	list<CLine*> targetLine;

	for (auto& line : m_LineList)
	{
		if (PlayerPos.x >= line->Get_Info().tLeft.x &&
			PlayerPos.x <= line->Get_Info().tRight.x)
		{
			targetLine.push_back(line);
		}
	}

	if (targetLine.empty())
		return false;

	prevDistance = FLT_MAX;

	if (targetLine.size() == 1)
	{
		float x1 = targetLine.front()->Get_Info().tLeft.x;
		float y1 = targetLine.front()->Get_Info().tLeft.y;

		float x2 = targetLine.front()->Get_Info().tRight.x;
		float y2 = targetLine.front()->Get_Info().tRight.y;

		*pY = ((y2 - y1) / (x2 - x1)) * (PlayerPos.x - x1) + y1;

		return true;
	}
	else
	{
		for (auto& line : targetLine)
		{
			float x1 = line->Get_Info().tLeft.x;
			float y1 = line->Get_Info().tLeft.y;

			float x2 = line->Get_Info().tRight.x;
			float y2 = line->Get_Info().tRight.y;

			*pY = ((y2 - y1) / (x2 - x1)) * ((PlayerPos.x) - x1) + y1;

			Distance = *pY - PlayerPos.y;

			if (Distance >= 0.f && Distance < prevDistance)
			{
				prevDistance = Distance;
				prevY        = *pY;
			}
		}
		if (prevDistance == FLT_MAX)
			return false;

		*pY = prevY; // 최종 Y좌표 반영
		return true;
	}
}

void CLineManager::Create_Line(Vector2* tPoint, int Num)
{
	for (int i = 0;i < Num - 1; i++)
	{
		m_LineList.push_back(new CLine(tPoint[i], tPoint[i + 1]));
	}
}
