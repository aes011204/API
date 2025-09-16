#pragma once

#define	WINCX			1280
#define	WINCY			720

#define PURE			= 0

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0

#define	PI				3.14f

#define VK_MAX			0xff

/////////////////////////////////

extern HWND g_hWnd;

/////////////////////////////////
#include "Vector2.h"

template<typename T>
void	Safe_Delete(T& P) { if (P) { delete P; P = nullptr; } }

typedef struct tagFrame
{
	int		iStart;
	int		iEnd;
	double	dwSpeed;
	double	dwTime;
	Vector2 vSize;

}FRAME;


enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_END
};

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

typedef struct tagLine
{
	Vector2 tLeft;
	Vector2 tRight;

	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}

	tagLine(Vector2 _tLeft, Vector2 _tRight)
		: tLeft(_tLeft), tRight(_tRight)
	{
	}
}
LINE;



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
