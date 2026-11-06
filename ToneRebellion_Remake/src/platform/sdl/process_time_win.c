/* Process CPU time for the benchmark (--bench-rate): user + kernel time of
   every thread, in seconds. Separate file: it needs <windows.h>, which the
   game code replaces with win32_compat.h. */
#include <windows.h>

double tone_process_cpu_seconds(void)
{
    FILETIME created, exited, kernel, user;
    ULARGE_INTEGER k, u;
    if (!GetProcessTimes(GetCurrentProcess(), &created, &exited, &kernel, &user))
        return -1.0;
    k.LowPart = kernel.dwLowDateTime;
    k.HighPart = kernel.dwHighDateTime;
    u.LowPart = user.dwLowDateTime;
    u.HighPart = user.dwHighDateTime;
    return (double)(k.QuadPart + u.QuadPart) / 1e7;
}
