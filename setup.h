#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#define clear system("cls")
#else
#include <unistd.h>
#define clear system("clear")
#endif

void setup();