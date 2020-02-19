![enter image description here](https://lh3.googleusercontent.com/Fw5qyv05-FRxkAgIeGdMJsIl6hAu8hnJiqh_g_0_XLLiHWt7qxwINeUsV75S9NmI0xefBTv4pCKbsfriRW8v=w1920-h1007-rw)


# About Cobalt

**Cobalt** is a C++ library, created and designed to be easy and fast to use, to help you in your development process. You can find many functions, which are super easy to type, even without this library, but it is much faster to use this library instead of typing all of it by yourself.  The library is one main class, which contains a lot of subclasses: **String, Memory, Process, Window, Misc, Console**, each of subclasses contain it's unique functions and methods.

## Updates

Library gets updated whenever I feel like there is something missed. If you want to get your own idea in this library or anything you would like to see, feel free to comment this repository, and I'll think if I want to make it.

## Bugs

If you find any bugs, please let me know as fast as possible so I can fix them by posting a message in **Issues** tab in this repository.


# How to use it?

At first, using this library may seem a bit complicated and slow, but with time, you will understand that it is much better that way.

## Initialization

I am going to show how to install them on Visual Studio 2019. There are 2 files: **LibInit.h** and **Lib.cpp**, you have to put **LibInit.h** in **Header Files**, and **Lib.cpp** in **Source Files**. Also put them in your project folder.(Project -> Open Folder in File Explorer). Then somewhere in your main code, do :

```cpp
#include "LibInit.h"
```

After that, the library is loaded and ready to use.

## Using it in code
After you connected the library, and everything works fine, you should know how to actually use it. As I told you earlier, library is one main class, which contains a lot of subclasses. So let's take subclass **String**, for example. You initialize it like this:
```cpp
Cobalt::String String;
```

After this, you can use all of **String** subclass functions and methods. This is done to improve performance and overall stability, you don't include every single subclass, some of which you may not even use.

# API Documentation
## String
	
```cpp
std::string tolowercase(std::string str);
```
Converts and returns **str**, with every char being lower-cased.

```cpp
std::string touppercase(std::string str);
```
Converts and returns **str**, with every char being upper-cased.

```cpp
std::string tobothcases(std::string str);
```
Converts and returns **str**, with every char being different case.


## Memory

```cpp
void WriteMemory(DWORD address, DWORD buffer, HANDLE handle);
```
Writes **buffer** to **address** in process with **handle**.

```cpp
DWORD ReadMemory(DWORD address, HANDLE handle);
```
Reads and returns memory from **address** in process with **handle**.

```cpp
DWORD GetModuleBaseAddress32b(std::string moduleName, DWORD PID);
```
Gets Module Base Address with name **moduleName** in a 32-bit process with process **PID**.

```cpp
uintptr_t GetModuleBaseAddress64b(std::string moduleName, DWORD PID);
````
Gets Module Base Address with name **moduleName** in a 64-bit process with process **PID**.




## Process
	
   ```cpp
   HANDLE AttachPID(DWORD access, DWORD PID);
   ```
   Returns process **HANDLE** by using **PID**, with specific access **access**. 
   
   ```cpp
   HANDLE AttachName(DWORD access, std::string windowName);
   ```
Returns process **HANDLE** by using **windowName**, with specific access **access**.	


## Window

```cpp
HWND GetWindow(std::string procName);
```
Returns window **HWND** by using **procName**.

```cpp
HWND GetHWNDFromHandle(HANDLE handle);
```
Returns window **HWND** with process **handle**

```cpp
HANDLE GetHandleFromHWND(DWORD access, HWND hwnd);
```
Returns process **HANDLE** with window **hwnd** with specific access **access**.

```cpp
DWORD GetPidFromHWND(HWND hwnd);
```
Returns window PID by using window **hwnd**.

```cpp
std::string GetNameFromHWND(HWND hwnd);
```
Returns window name by using window **hwnd**.


## Misc

```cpp
std::string getclipboardtext();
```
Reads and returns your clipboard text.

```cpp
bool iskeydown(DWORD key);
```
Returns true if the **key** is pressed, false otherwise.

```cpp
void keypress(DWORD key, DWORD type_);
```
Presses **key** in keyboard/mouse, depending on **type_**

```cpp
void toclipboard(const std::string& str);
```
Copies **str** to your clipboard.

```cpp
int rand(int min, int max);
```
Returns random number in-between **min** and **max**.

## Console

```cpp
void gotoaxis(int x, int y);
```
Sets console cursor to position with **x** and **y**, you can then print text at that specific coordinates.

```cpp
void axiscout(int x, int y, std::string text);
```
Sets console cursor to position with **x** and **y** and then prints **text**.

```cpp
void setcolor(DWORD color);
```
Sets console color to **color**, you can then print text with that color. You can find every color in **Colors** preprocessor.

```cpp
void colorcout(DWORD color, std::string text);
```
Sets console color to **color** and prints text. You can find every color in **Colors** preprocessor.

```cpp
void removescrollbar();
```
Removes console scrollbars.

```cpp
void showconsole(DWORD setting);
```
Sets console visibility to **setting**. You can find every setting in **Window Flags** preprocessor.

	
# Custom Preprocessor
There is a custom preprocessor installed in this library, you can use it in some of it's functions, here are they:

##  Access
```cpp
#define READ PROCESS_VM_READ
#define WRITE PROCESS_VM_WRITE
#define OPERATION PROCESS_VM_OPERATION
#define ALL PROCESS_ALL_ACCESS
#define TERMINATE PROCESS_TERMINATE
```
	
## Colors

```cpp
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
```
  
   ## Window Flags
  


   
```cpp
#define SHOW SW_SHOW
#define HIDE SW_HIDE
#define MINIMIZE SW_MINIMIZE
```

 ## Input Types
 
```cpp
#define MOUSE INPUT_MOUSE
#define KEYBOARD INPUT_KEYBOARD
```

 ## Mouse Input Keys
 
```cpp
#define MOUSELEFTDOWN MOUSEEVENTF_LEFTDOWN
#define MOUSELEFTUP MOUSEEVENTF_LEFTUP
#define MOUSERIGHTDOWN MOUSEEVENTF_RIGHTDOWN
#define MOUSERIGHTUP MOUSEEVENTF_RIGHTUP
#define MOUSEMIDDLEDOWN MOUSEEVENTF_MIDDLEDOWN
#define MOUSEMIDDLEUP MOUSEEVENTF_MIDDLEUP
```
