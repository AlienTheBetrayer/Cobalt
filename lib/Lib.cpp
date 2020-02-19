#include "LibInit.h";

// ---------- String ---------- //

std::string Cobalt::String::tolowercase(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

std::string Cobalt::String::touppercase(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

std::string Cobalt::String::toloweruppercase(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		if (i % 2) {
			str[i] = tolower(str[i]);
		}
		else {
			str[i] = toupper(str[i]);
		}
	}
	return str;
}

// ---------- Process ---------- //

HANDLE Cobalt::Process::AttachPID(DWORD access, DWORD PID) {
	HANDLE handle = OpenProcess(access, NULL, PID); 
	if (handle) {
		return handle;
	}
	else {
		std::cout << "[ERROR] AttachPID function couldn't attach to the process. \n";
	}
}

HANDLE Cobalt::Process::AttachName(DWORD access, std::string windowName) {
	HWND hwnd = FindWindow(NULL, windowName.c_str());
	DWORD PID;
	GetWindowThreadProcessId(hwnd, &PID);
	HANDLE handle = OpenProcess(access, NULL, PID);
	if (handle) {
		return handle;
	}
	else {
		std::cout << "[ERROR] AttachName function couldn't attach to the process. \n";
	}
}

// ---------- Window ---------- //

HWND Cobalt::Window::GetWindow(std::string procName) {
	HWND hwnd = FindWindow(NULL, procName.c_str());
	if (hwnd) {
		return hwnd;
	}
	else {
		std::cout << "[ERROR] GetWindow function couldn't obtain the window. \n";
	}
}

HWND Cobalt::Window::GetHWNDFromHandle(HANDLE handle) {
	std::cout << "[WARN] GetHWNDFromHandle function doesn't have functionality yet. \n";

	return nullptr;
}

HANDLE Cobalt::Window::GetHandleFromHWND(DWORD access, HWND hwnd) {
	DWORD PID;
	GetWindowThreadProcessId(hwnd, &PID);
	HANDLE handle = OpenProcess(access, NULL, PID);
	if (handle) {
		return handle;
	}
	else {
		std::cout << "[ERROR] AttachName function couldn't attach to the process. \n";
	}
}

DWORD Cobalt::Window::GetPidFromHWND(HWND hwnd) {
	DWORD PID;
	GetWindowThreadProcessId(hwnd, &PID);

	return PID;
}

std::string Cobalt::Window::GetNameFromHWND(HWND hwnd) {
	int len = GetWindowTextLength(hwnd) + 1;
	std::string wName = "";
	wName.resize(len);
	GetWindowTextA(hwnd, (LPSTR)(wName.c_str()), len);

	return wName;
}

// ---------- Misc ---------- //

void Cobalt::Misc::toclipboard(const std::string& str) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
	if (!hg) {
		std::cout << "[ERROR] toclipboard function couldn't open the clipboard. \n";
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), str.c_str(), str.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int Cobalt::Misc::rand(int min, int max) {
	std::random_device rd;
	std::mt19937 eng(rd()); 
	std::uniform_int_distribution<> distr(min, max); 
	
	return distr(eng);
}

std::string Cobalt::Misc::getclipboardtext() {
		if (!OpenClipboard(nullptr));
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr);
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr);
		std::string text(pszText);
		GlobalUnlock(hData);
		CloseClipboard();

		return text;
}

bool Cobalt::Misc::iskeydown(DWORD key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void Cobalt::Misc::keypress(DWORD key, DWORD type_) {
	INPUT inp = { 0 };
	inp.type = type_;
	if (type_ == INPUT_MOUSE) {
		inp.mi.dwFlags = key;
		SendInput(1, &inp, sizeof(inp));
		ZeroMemory(&inp, sizeof(inp));
	}
	else if (type_ == INPUT_KEYBOARD) {
		inp.ki.wVk = key;
		SendInput(1, &inp, sizeof(inp));
		ZeroMemory(&inp, sizeof(inp));
	}
}

// ---------- Memory ---------- //


void Cobalt::Memory::WriteMemory(uintptr_t address, DWORD buffer, HANDLE handle) {
	WriteProcessMemory(handle, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}

DWORD Cobalt::Memory::ReadMemory(uintptr_t address, HANDLE handle) {
	DWORD tempBuffer;
	ReadProcessMemory(handle, (LPVOID)address, &tempBuffer, sizeof(tempBuffer), NULL);
	return tempBuffer;
}

DWORD Cobalt::Memory::GetModuleBaseAddress32b(std::string moduleName, DWORD PID) {
		DWORD dwModuleBaseAddress = 0;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do {
				if (_tcscmp(ModuleEntry32.szModule, moduleName.c_str()) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));


		}
		CloseHandle(hSnapshot);
		return dwModuleBaseAddress;
	}

uintptr_t Cobalt::Memory::GetModuleBaseAddress64b(std::string moduleName, DWORD PID) {
	uintptr_t dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, moduleName.c_str()) == 0)
			{
				dwModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

// ---------- Console ---------- //

void Cobalt::Console::gotoaxis(int x, int y) {
	COORD cords;
	cords.X = x;
	cords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
}

void Cobalt::Console::axiscout(int x, int y, std::string text) {
	COORD cords;
	cords.	X = x;
	cords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
	std::cout << text;
}

void Cobalt::Console::setcolor(DWORD color) {	
	HANDLE std_ = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_, color);
}

void Cobalt::Console::colorcout(DWORD color, std::string text) {
	HANDLE std_ = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_, color);
	std::cout << text;
	SetConsoleTextAttribute(std_, WHITE);
}

void Cobalt::Console::removescrollbar() {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(handle, &info);
		COORD new_size =
		{
			info.srWindow.Right - info.srWindow.Left + 1,
			info.srWindow.Bottom - info.srWindow.Top + 1
		};
		SetConsoleScreenBufferSize(handle, new_size);
}

void Cobalt::Console::showconsole(DWORD setting) {
	ShowWindow(GetConsoleWindow(), setting);
}

