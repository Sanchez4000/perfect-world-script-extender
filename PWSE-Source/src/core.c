#define _GNU_SOURCE
#include "pwse.h"
#include "log.h"
#include "addresses.h"
#include "hooks.h"
#include "loader.h"

#include <stdlib.h>

#define PWSE_PLUGINS_DIR   "plugins"
#define PWSE_ADDRESSES_INI "plugins/_addresses.ini"

static unsigned api_resolve(const char* name)
{
    return pwse_addresses_resolve(name);
}

static int api_hook(const char* name, void* detour, void** original)
{
    unsigned addr = pwse_addresses_resolve(name);
    if (addr == 0)
    {
        pwse_log("hook: name not found in address library");
        return -1;
    }
    return pwse_hook_install(addr, detour, original);
}

static const PwseApi g_api =
{
    PWSE_ABI,
    pwse_log,
    api_resolve,
    api_hook
};

__attribute__((constructor))
static void pwse_init(void)
{
    unsetenv("LD_PRELOAD");

    pwse_log("loader start");

    if (pwse_addresses_load(PWSE_ADDRESSES_INI) < 0)
        pwse_log("address library not found");

    pwse_loader_load_all(PWSE_PLUGINS_DIR, &g_api);

    pwse_log("loader done");
}
