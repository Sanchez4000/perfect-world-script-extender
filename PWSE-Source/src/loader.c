#define _GNU_SOURCE
#include "loader.h"
#include "log.h"

#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

static int ends_with_so(const char* name)
{
    size_t n = strlen(name);
    return n > 3 && strcmp(name + n - 3, ".so") == 0;
}

int pwse_loader_load_all(const char* dir, const PwseApi* api)
{
    DIR*           d;
    struct dirent* e;
    int            loaded = 0;
    char           path[512];
    char           msg[640];

    d = opendir(dir);
    if (d == 0)
    {
        pwse_log("plugins directory not found");
        return 0;
    }

    while ((e = readdir(d)) != 0)
    {
        void* h;
        int (*entry)(const PwseApi*);

        if (!ends_with_so(e->d_name))
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);

        h = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
        if (h == 0)
        {
            snprintf(msg, sizeof(msg), "plugin dlopen failed: %s (%s)", e->d_name, dlerror());
            pwse_log(msg);
            continue;
        }

        entry = (int (*)(const PwseApi*))dlsym(h, "PwsePluginLoad");
        if (entry == 0)
        {
            snprintf(msg, sizeof(msg), "plugin has no PwsePluginLoad: %s", e->d_name);
            pwse_log(msg);
            dlclose(h);
            continue;
        }

        if (entry(api) == 0)
        {
            snprintf(msg, sizeof(msg), "plugin loaded: %s", e->d_name);
            pwse_log(msg);
            loaded++;
        }
        else
        {
            snprintf(msg, sizeof(msg), "plugin load returned error: %s", e->d_name);
            pwse_log(msg);
            dlclose(h);
        }
    }

    closedir(d);
    return loaded;
}
