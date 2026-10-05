#include "log.h"

#include <unistd.h>
#include <string.h>

void pwse_log(const char* msg)
{
    static const char prefix[] = "[pwse] ";

    if (msg == 0)
        return;

    (void)write(1, prefix, sizeof(prefix) - 1);
    (void)write(1, msg, strlen(msg));
    (void)write(1, "\n", 1);
}
