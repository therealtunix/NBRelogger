#include "stdafx.h"
#include "process.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string>

using namespace std;

Process::Process(void){
	ZeroMemory(&si, sizeof(si));	//STARTUPINFO
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));	//PROCESSINFO like PID etc..
}

Process::~Process(void){
	return;
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

LPTSTR Process::getArgs(){
		/* return set arguments for the process */
		return this->args;
	}

int Process::getPID(){
		return pi.dwProcessId;
	}

boolean Process::isAlive(){
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

void Process::startProcess(){
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