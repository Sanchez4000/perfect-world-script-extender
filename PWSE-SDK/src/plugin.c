#include "pwse.h"

static const PwseApi* g;

/* Example hook (uncomment and adapt):
typedef void (*SomeFunc_t)(void* self, int arg);
static SomeFunc_t SomeFunc_orig;

static void SomeFunc_hook(void* self, int arg)
{
    g->Log("[myplugin] SomeFunc");
    SomeFunc_orig(self, arg);
}
*/

int PwsePluginLoad(const PwseApi* api)
{
    g = api;

    g->Log("[myplugin] loaded");

    /* g->Hook("some::Function", SomeFunc_hook, (void**)&SomeFunc_orig); */

    /*
    typedef int (*GetSomething_t)(void);
    GetSomething_t f = (GetSomething_t)g->Resolve("some::GetSomething");
    if (f != 0)
        f();
    */

    return 0;
}
