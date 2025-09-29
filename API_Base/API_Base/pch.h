#pragma once

//GDI+

//#define NOMINMAX                 // <windows.h>의 min/max 매크로 무력화 (std::min/max 충돌 방지)
//#include <windows.h>             // 반드시 gdiplus.h보다 먼저
//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib") 

#include "framework.h"
#include <cmath>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <array>
#include <crtdbg.h>

#include "Define.h"
#include "Vector2.h"
#include < io.h >
#include <unordered_map>
//#include "CUtility.h"
using namespace std;


// 사운드 
//#include <Vfw.h>
//#pragma comment(lib, "vfw32.lib")
//
//#include "fmod.h"
//#include "fmod.hpp"
//
//#pragma comment(lib, "fmodex_vc.lib")

#include "fmod.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"

#pragma comment(lib, "fmod_vc.lib")


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif
