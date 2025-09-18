#pragma once

#define	WINCX			900//1280
#define	WINCY			600//720

#define TILECX		16
#define TILECY		16

#define TILEX		100
#define TILEY		100

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
enum DR
{
	RIGHT,
	LEFT,
	DIR_END
};
typedef struct tagFrame
{
	int		iStart;
	int		iEnd;
	DR		dir;
	double	dwSpeed;
	double	dwTime;
	Vector2 vSize;

}FRAME;






enum OBJID
{
	PLAYER,
	MONSTER,
	BOSS,
	PET,
	ITEM,
	WEAPON,
	BULLET,
	PLATFORM,
	EFFECT,

	OBJ_END
};


enum SCENEID
{
	SC_MAINMENU, SC_VILLAGE, SC_STAGE01, SC_STAGE02, SC_BOSS, SC_EDIT, SC_END
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
