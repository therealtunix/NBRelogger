#include "stdafx.h"
#include "process.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
//#include <afx.h>
//#include <afxwin.h>

using namespace std;

Process::Process(void){
	ZeroMemory(&si, sizeof(si));	//STARTUPINFO
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));	//PROCESSINFO like PID etc..
}

Process::~Process(void){
	/* kills process and removes handles */

	printf("----try to kill Process\n");

	//send close request to window
	EnumWindows(EnumWindowsProc, pi.dwProcessId);
	//wait for process to exit, when timeout is reached force close
	//TODO handle the case if process did not close on forceclose
	if (WAIT_OBJECT_0 != WaitForSingleObject(pi.hProcess, 15000))
	{
		printf("sendMessage did not work, try to forceclose\n");
		TerminateProcess(pi.hProcess, NULL); //forceclose
	}

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

BOOL CALLBACK Process::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	/* c&P from http://www.codeproject.com/Articles/44/Creating-a-process-and-then-killing-it*/
	DWORD wndPid;
	// lParam = procInfo.dwProcessId;

	// This gets the windows handle and pid of enumerated window.
	GetWindowThreadProcessId(hwnd, &wndPid);

	//  this makes sure that the PID matches that PID we started, and window
	// text exists, before we kill it . I don't think this is really needed, 
	// I included it because some apps have more than one window.
	if (wndPid == (DWORD)lParam)
	{
		//  Please kindly close this process
		::PostMessage(hwnd, WM_CLOSE, 0, 0);
		return false;
	}
	else
	{
		// Keep enumerating
		return true;
	}
}

void Process::setPath(LPCWSTR s){
		this->path = s;
	}

LPCWSTR Process::getPath(){
		return this->path;
	}

void Process::setArgs(LPTSTR s){
		this->args = s;
	}

LPTSTR Process::getArgs(void){
		/* return set arguments for the process */
		return this->args;
	}

int Process::getPID(void){
		return pi.dwProcessId;
	}

boolean Process::isAlive(void){
		/* check if Process is still alive, if it is alive return TRUE, else FALSE
		WaitForSingleObject checks if Proces is in signaled state
		if WAIT_TIMEOUT is returned process is in nonsignaled state
		meaning it is still reachable, so it is alive */
		printf("check if process is alive worked\n");
		if (WaitForSingleObject(this->pi.hProcess, 0) == WAIT_TIMEOUT){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}

void Process::startProcess(void){
	printf("trying to start Process\n");
	// Start the child process. 
	if (!CreateProcess(path,   // No module name (use command line)
		args,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
	}
	else {
		/* check if Process is able to start up and completely
		load within 60 seconds */
		if (WaitForInputIdle(pi.hProcess, 60000)){
			printf("Error starting wow\n");
			exit(EXIT_FAILURE);
		}
		else{
			/* else launch was successful */
			// WaitForSingleObject(pi.hProcess, INFINITE);
			//CloseHandle(pi.hThread);
			//CloseHandle(pi.hProcess);
			printf("Yohoo! process started\n");
		}
	}
}