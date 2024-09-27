#pragma once
#include "Windows.h"
//#include <iostream>
//#include <string>
#pragma warning(disable : 4996) // freopen unsafe

//#define MY_ALLOC
extern bool gbIsConsoleOpened;
void OpenConsole();
HANDLE InitConsole();
void LeaveConsole(HANDLE);
