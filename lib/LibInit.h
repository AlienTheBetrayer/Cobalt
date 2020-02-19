#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <vector>
#include <tchar.h>
#include <sstream>
#include <random>

#define READ PROCESS_VM_READ
#define WRITE PROCESS_VM_WRITE
#define OPERATION PROCESS_VM_OPERATION
#define ALL PROCESS_ALL_ACCESS
#define TERMINATE PROCESS_TERMINATE

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3		
#define RED	4			
#define MAGENTA	5		
#define BROWN 6			
#define LIGHTGRAY 7	
#define DARKGRAY 8		
#define LIGHTBLUE 9		
#define LIGHTGREEN 10		
#define LIGHTCYAN 11		
#define LIGHTRED 12		
#define LIGHTMAGENTA 13	
#define YELLOW 14			
#define WHITE 15			
#define NEGATIVE COMMON_LVB_REVERSE_VIDEO

#define SHOW SW_SHOW
#define HIDE SW_HIDE
#define MINIMIZE SW_MINIMIZE

#define MOUSE INPUT_MOUSE
#define KEYBOARD INPUT_KEYBOARD

#define MOUSELEFTDOWN MOUSEEVENTF_LEFTDOWN
#define MOUSELEFTUP MOUSEEVENTF_LEFTUP
#define MOUSERIGHTDOWN MOUSEEVENTF_RIGHTDOWN
#define MOUSERIGHTUP MOUSEEVENTF_RIGHTUP
#define MOUSEMIDDLEDOWN MOUSEEVENTF_MIDDLEDOWN
#define MOUSEMIDDLEUP MOUSEEVENTF_MIDDLEUP




class Cobalt {
public:

	class String {
	public: 
		std::string tolowercase(std::string str);
		std::string touppercase(std::string str);
		std::string toloweruppercase(std::string str);
	private:

	};
	

	class Memory {	
	public: 
		DWORD GetModuleBaseAddress32b(std::string moduleName, DWORD PID);
		uintptr_t GetModuleBaseAddress64b(std::string moduleName, DWORD PID);
		void WriteMemory(uintptr_t address, DWORD buffer, HANDLE handle);
		DWORD ReadMemory(uintptr_t address, HANDLE handle);
	private:

	};

	class Process {
	public: 
		HANDLE AttachPID(DWORD access, DWORD PID);
		HANDLE AttachName(DWORD access, std::string windowName);	
	private:

	};

	class Window {
	public: 
		HWND GetWindow(std::string procName);
		HWND GetHWNDFromHandle(HANDLE handle);
		HANDLE GetHandleFromHWND(DWORD access, HWND hwnd);
		DWORD GetPidFromHWND(HWND hwnd);
		std::string GetNameFromHWND(HWND hwnd);
	private:

	};

	class Misc {
	public: 
		std::string getclipboardtext();
		bool iskeydown(DWORD key);
		void keypress(DWORD key, DWORD type_);
		void toclipboard(const std::string& str);
		int rand(int min, int max);
	private:

	};

	class Console {
	public:
		void gotoaxis(int x, int y);
		void axiscout(int x, int y, std::string text);
		void setcolor(DWORD color);
		void colorcout(DWORD color, std::string text);
		void removescrollbar();
		void showconsole(DWORD setting);
	private:


	};


private:

};