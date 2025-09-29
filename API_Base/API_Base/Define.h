#pragma once

#define	WINCX			 950//1280
#define	WINCY			550//720

//#define TILECX		16
//#define TILECY		16

//#define TILEX		32
//#define TILEY		32

#define PURE			= 0

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0

#define	PI				3.14f

#define VK_MAX			0xff

enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEBOJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };
enum CHANNELID { SOUND_BGM, SOUND_EFFECT, SOUND_EAT1, SOUND_EAT2, MAXCHANNEL };

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

enum TILEDIR
{
	TDIR_TOP,
	TDIR_DOWN, 
	TDIR_LEFT,
	TDIR_RIGHT
};




enum OBJID
{
	DOOR,
	MONSTER,
	PLAYER,
	BOSS,
	PET,
	ITEM,
	BULLET,
	PLATFORM,
	EFFECT,
	WALL,
	NPC,
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


template <typename T>
T Clamp(const T& value, const T& minVal, const T& maxVal)
{
	return (value < minVal) ? minVal : (value > maxVal ? maxVal : value);
}

#include <cstdlib>
#include <ctime>

inline void InitRand() { std::srand((unsigned)std::time(nullptr)); } // 게임 시작 시 1번

inline int RandInt(int a, int b) { return a + std::rand() % (b - a + 1); }        // [a, b]
inline float RandFloat(float a, float b) { return a + (std::rand() / (float)RAND_MAX) * (b - a); } // [a, b]