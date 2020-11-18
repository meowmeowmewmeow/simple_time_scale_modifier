/* ###########################################################

simple QueryPerformanceCounter hook using microsoft detours v3

* discord rémi#0609
* twitter @meowmeowmewmeow
* githacks.org @x

free of use, i would appreciate if you didn't delete this text

########################################################### */

#include "pch.h"

#include "time_scale_modifier.hpp"

//example: stops target process clock until NUMPAD0 is pressed
DWORD WINAPI time_scale_modifier_thread(LPVOID lp_param) {
    time_scale_modifier::setup();
    time_scale_modifier::set_speed(0.0);
    while (!GetAsyncKeyState(VK_NUMPAD0))
        Sleep(1);
    time_scale_modifier::detach();
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD  ul_reason_for_call, LPVOID lp_reserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, &time_scale_modifier_thread, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}