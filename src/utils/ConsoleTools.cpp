#pragma once
#include "ConsoleTools.h"
#include "Windows.h"
#include <iostream>
#include <string>

//#define MY_ALLOC
HANDLE InitConsole();


extern bool gbIsConsoleOpened = false;


void OpenConsole()
{
	if(!gbIsConsoleOpened)
	{
#ifdef MY_ALLOC
		InitConsole();
#else
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
#endif
		gbIsConsoleOpened = true;
	}
}



//------------------------------------------------------------------
HANDLE InitConsole() // with proto
{
	AllocConsole();

	//SetConsoleOutputCP(866);
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	return hConsole;
}

//void LeaveConsole(HANDLE hConsole = nullptr)
void LeaveConsole(HANDLE hConsole) // with proto
{
	if (hConsole != nullptr) { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); } // Reset to default color
	FreeConsole();
}

//void Mbox(const char* msg, const char* title)
//{
//	MessageBoxA(HWND_DESKTOP, msg, title, MB_SYSTEMMODAL | MB_ICONWARNING);
//}
//
////void MboxSTD(const std::string& msg, const std::string& title = "title")
//void MboxSTD(std::string msg, std::string title)
//{
//	MessageBoxA(HWND_DESKTOP, msg.c_str(), title.c_str(), MB_SYSTEMMODAL | MB_ICONWARNING);
//}
//void EXIT_F()
//{
//	ExitProcess(EXIT_FAILURE);
//}
//void EXIT_S()
//{
//	ExitProcess(EXIT_SUCCESS);
//}
//void RaiseError(const char* fmt, ...)
//{
//	char buf[2048];
//	va_list args;
//	va_start(args, fmt);
//	vsprintf_s(buf, fmt, args);
//	va_end(args);
//
//	MessageBoxA(HWND_DESKTOP, buf, "Fatal Error", MB_SYSTEMMODAL | MB_ICONWARNING);
//	ExitProcess(EXIT_FAILURE);
//}


//std::string ToUpper(std::string strToConvert)
//{
//	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), std::toupper); //::toupper
//	return strToConvert;
//}
//std::string ToLower(std::string strToConvert)
//{
//	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), std::tolower);
//	return strToConvert;
//}
//std::string CustomStringConcat(std::string str1, std::string str2) { return str1 + str2; }