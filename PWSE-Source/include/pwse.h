#ifndef PWSE_H
#define PWSE_H

#ifdef __cplusplus
extern "C" {
#endif

#define PWSE_ABI 1

typedef struct PwseApi PwseApi;

struct PwseApi
{
    int abi_version;
    void     (*Log)(const char* msg);
    unsigned (*Resolve)(const char* name);
    int      (*Hook)(const char* name, void* detour, void** original);
};

int PwsePluginLoad(const PwseApi* api);

#ifdef __cplusplus
}
#endif

#endif
