#include "log.h"

int main()
{
    Log::Instance();
    Log::Instance()->init(1,"./log", ".log", 0);
    int a = 10;
    float b = 12.5;
    const char str[] = "china china";
    LOG_BASE(3, "%s 11111111", str)
    return 0;
}