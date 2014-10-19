// NBRelogger.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "process.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>

#define SLEEPTIME 500 //defines sleeptime in ms between each check cycle

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int x = 0;
	LPCWSTR execProg = TEXT("C:\\Windows\\system32\\calc.exe");
	//LPCWSTR execProg = TEXT("C:\\Spiele\\World of Warcraft\\Wow.exe");
	//Process aProcess(execProg);
	//while (x < 1)
	//{
	//	aProcess.startProcess();
	//	x++;
	//	printf("run number %d\n", x);
	//}
	Process aProcess = Process(execProg);
	aProcess.startProcess();
	//boolean keepAlive = TRUE;
	while (x <= 100)
	{
		//if (x >= 10000){
		//	keepAlive = FALSE;
		//}
//		aProcess.isAlive() ? printf("yeaaah! still alive\n") : aProcess.startProcess();
		if (aProcess.isAlive() == FALSE)
		{
			printf("process is dead! :'( \n");
			aProcess.startProcess();
		}
		else{
			printf("yeeeeah still alive! \n");
		}
		printf("still alive at run %d\n", x);
		Sleep(SLEEPTIME);
		x++;
		//cin.get();
	}
	system("pause");
	
	return 0;
}

