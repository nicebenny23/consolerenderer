#include "debug.h"
#pragma warning(disable: 4996)//will not compile without
void debug::reset()
{

    FILE* fp = fopen("debug.txt", "w");
    if (fp == NULL)
    {
        std::exit(-664);
    }
    fclose(fp);
}

void debug::writestring(std::string string)
{
    if (DEBUG)
    {


        FILE* fp = fopen("debug.txt", "a+");
        if (fp == NULL)
        {
            std::exit(-664);
        }
        for (int i = 0; i < string.length(); i++)
        {
            fputc(int(string[i]), fp);
        }
        fclose(fp);
    }
}
