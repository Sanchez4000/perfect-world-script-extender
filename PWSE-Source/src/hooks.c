#include "hooks.h"

#include <stdint.h>

#ifndef SUBHOOK_STATIC
#define SUBHOOK_STATIC
#endif
#include "subhook.h"

int pwse_hook_install(unsigned addr, void* detour, void** original)
{
    subhook_t hook;

    if (addr == 0 || detour == 0)
        return -1;

    hook = subhook_new((void*)(uintptr_t)addr, detour, SUBHOOK_TRAMPOLINE);
    if (hook == 0)
        return -2;

    if (subhook_install(hook) != 0)
    {
        subhook_free(hook);
        return -3;
    }

    if (original != 0)
    {
        void* tramp = subhook_get_trampoline(hook);
        if (tramp == 0)
        {
            subhook_remove(hook);
            subhook_free(hook);
            return -4;
        }
        *original = tramp;
    }

    return 0;
}
