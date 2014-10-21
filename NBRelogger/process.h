#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string>

#pragma once

using namespace std;

class Process{
	STARTUPINFO si;	//in param
	PROCESS_INFORMATION pi;	//out param
	LPCWSTR path;
	//LPTSTR args = TEXT("wow.exe -noautolaunch64bit -nosound -windowed -800x600");
	LPTSTR args;
	
public:
	void setPath(LPCWSTR);
	LPCWSTR getPath();
	void setArgs(LPTSTR);
	LPTSTR getArgs();
	int getPID();
	boolean isAlive();

	Process();
	~Process();
	void startProcess();
};