#ifndef PWSE_HOOKS_H
#define PWSE_HOOKS_H

int pwse_hook_install(unsigned addr, void* detour, void** original);

#endif
