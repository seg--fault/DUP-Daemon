#if defined(_WIN32) //we're supporting win32
#include "W32.h"
#include <Windows.h>
#include "Logic.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	for(;;)
	{

	}
    return 0;
}

#elif defined(__linux__) //we're supporting linux
#include "Linux.h"

int main()
{
	for(;;)
	{
	}
	return 0;
}

#else //assume bsd
#include "BSD.h"

int main()
{
	for(;;)
	{
	}
	return 0;
}

#endif