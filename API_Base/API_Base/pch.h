#pragma once


#include "framework.h"
#include <cmath>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

#include "Define.h"
#include "Vector2.h"
//#include "CUtility.h"
using namespace std;


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif
