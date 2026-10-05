#include "addresses.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PWSE_ADDR_MAX 512
#define PWSE_NAME_MAX 160

typedef struct
{
    char     name[PWSE_NAME_MAX];
    unsigned addr;
} AddrEntry;

static AddrEntry g_entries[PWSE_ADDR_MAX];
static int       g_count;

static char* skip_ws(char* s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}

static void rstrip(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\r' || s[n - 1] == '\n'))
        s[--n] = 0;
}

int pwse_addresses_load(const char* path)
{
    FILE* f;
    char  line[256];

    f = fopen(path, "r");
    if (f == 0)
        return -1;

    g_count = 0;
    while (fgets(line, sizeof(line), f) != 0)
    {
        char*    p;
        char*    eq;
        char*    name;
        char*    val;
        unsigned addr;

        p = skip_ws(line);
        if (*p == 0 || *p == '#' || *p == ';' || *p == '\r' || *p == '\n')
            continue;

        eq = strchr(p, '=');
        if (eq == 0)
            continue;

        *eq = 0;
        name = p;
        rstrip(name);

        val = skip_ws(eq + 1);
        addr = (unsigned)strtoul(val, 0, 0);
        if (addr == 0)
            continue;

        if (g_count >= PWSE_ADDR_MAX)
            break;

        strncpy(g_entries[g_count].name, name, PWSE_NAME_MAX - 1);
        g_entries[g_count].name[PWSE_NAME_MAX - 1] = 0;
        g_entries[g_count].addr = addr;
        g_count++;
    }

    fclose(f);
    return g_count;
}

unsigned pwse_addresses_resolve(const char* name)
{
    int i;

    if (name == 0)
        return 0;

    for (i = 0; i < g_count; i++)
    {
        if (strcmp(g_entries[i].name, name) == 0)
            return g_entries[i].addr;
    }
    return 0;
}
