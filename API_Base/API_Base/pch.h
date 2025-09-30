#pragma once

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


// »ç¿îµå 

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
