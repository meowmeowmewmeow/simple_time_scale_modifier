#pragma once

#include <Windows.h>

#define DETOURS_INTERNAL
#include "detours/detours.h"

#pragma comment(lib, "detours/detours.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Winmm.lib")

namespace time_scale_modifier {
	extern double speed;
	extern bool attached;

	typedef BOOL(WINAPI* _t_queryperformancecounter)(LARGE_INTEGER*);
	extern LARGE_INTEGER _qpc_basetime;
	extern _t_queryperformancecounter _qpc;
	DWORD WINAPI _hqueryperformancecounter(LARGE_INTEGER* lp_performancecount);

	void setup();
	void detach();
	void set_speed(float desired_speed);
}