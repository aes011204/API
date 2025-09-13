#pragma once

#define	WINCX			800//1280
#define	WINCY			600//720

#define PURE			= 0

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0

#define	PI				3.14f

#define VK_MAX			0xff

/////////////////////////////////

extern HWND g_hWnd;

/////////////////////////////////

template<typename T>
void	Safe_Delete(T& P) { if (P) { delete P; P = nullptr; } }



enum CREATURE_ID
{
	PLAYER,
	MONSTER,
	PET,
	CID_END
};
enum NONCREATURE_ID
{
	ITEM,
	WEAPON,
	BULLET,
	PLATFORM,
	EFFECT,
	NCID_END
};



enum SCENEID
{
	SC_MAINMENU, SC_VILLAGE, SC_STAGE, SC_END
};

#include "Vector2.h"
typedef struct tagLine
{
	Vector2 LPoint;
	Vector2 RPoint;

	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}

	tagLine(Vector2 left, Vector2 right)
		: LPoint(left), RPoint(right) {
	}
}LINE;


typedef struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(MyPair.first, m_pTag);
	}

	const TCHAR* m_pTag;
};
