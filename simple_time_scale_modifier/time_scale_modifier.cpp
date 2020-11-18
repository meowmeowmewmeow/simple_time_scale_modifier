#include "pch.h"

#include "time_scale_modifier.hpp"

namespace time_scale_modifier {
	double speed = 1.0;
	bool attached = false;

	extern _t_queryperformancecounter _qpc = nullptr;
	extern LARGE_INTEGER _qpc_basetime = LARGE_INTEGER();

	DWORD WINAPI _hqueryperformancecounter(LARGE_INTEGER* lp_performance_count) {
		LARGE_INTEGER x; 
		_qpc(&x);
		lp_performance_count->QuadPart = _qpc_basetime.QuadPart + ((x.QuadPart - _qpc_basetime.QuadPart) * speed);
		return TRUE;
	}

	void setup() {
		if (attached)
			return;

		HMODULE h_mod = GetModuleHandle(L"Kernel32.dll");
		if (!h_mod)
			return;

		_qpc = (_t_queryperformancecounter)GetProcAddress(h_mod, "QueryPerformanceCounter");
		_qpc(&_qpc_basetime);

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)_qpc, _hqueryperformancecounter);
		DetourTransactionCommit();

		attached = true;
	}

	void detach() {
		if (!attached)
			return;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)_qpc, _hqueryperformancecounter);
		DetourTransactionCommit();

		attached = false;
	}

	void set_speed(float desired_speed) {
		if (attached)
			_hqueryperformancecounter(&_qpc_basetime);
		speed = desired_speed;
	}
}