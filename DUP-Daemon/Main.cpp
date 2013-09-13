//NOTES
//if someone wants to add mac support they're free to but right now I don't plan on doing it myself
//priorities go: linux, windows scavenging, linux scavenging, bsd, bsd scavenging
//	from greatest to least
//

#if defined(_WIN32)
#define CYCLE_SCAVENGING
#endif

#include "Logic.h"

#if defined(_WIN32) //we're supporting win32
#include "W32.h"
#include <Windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	if(OpenMutex(MUTEX_ALL_ACCESS, 0, "gskConcensus"))
		return ERROR_BUSY;
	HANDLE hMutex = CreateMutex(0, 0, "gskConsensus");
	Logic::scavenge_initialize();
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