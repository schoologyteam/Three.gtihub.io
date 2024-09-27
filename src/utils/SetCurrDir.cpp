#pragma once
#include "Windows.h"
#include <iostream>

static bool gbIsSettedCurrDir = false;
void
U_SetCurrentDirectory()
{
	// mod by diktor SET CURRENT PATH
	// char currentDir[MAX_PATH]; // STATIC PATH
	// GetCurrentDirectory(MAX_PATH, currentDir);
	// printf("DIR: %s\n", currentDir);
	// memset(currentDir, 0, MAX_PATH);
	// strncpy(currentDir, "C:\\_GTA_RE\\revc\\reVC_GAME", MAX_PATH);
	// currentDir[MAX_PATH - 1] = '\0'; // Ensure null-termination
	// SetCurrentDirectory(currentDir);

	char currentDir[MAX_PATH]; // dynamic set curr dir to exe
	GetModuleFileName(NULL, currentDir, MAX_PATH);
	std::string::size_type pos = std::string(currentDir).find_last_of("\\/");
	SetCurrentDirectory(std::string(currentDir).substr(0, pos).c_str());
	gbIsSettedCurrDir = true;
}