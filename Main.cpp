#define LOGLEVEL 0;	//0 = fatal errors, 1 = errors and fatal errors, 2 = warnings, errors, and fatal errors


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

#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include "Linux.h"
#include "Logger.h"

#define PIDFILE "/var/run/gskConsensus.pid"	//pid file location

void initialize()
{
	if(access(PIDFILE,F_OK) != -1)					//if another process is running
	{
		std::cout<<"FATAL ERROR -> Daemen already running.\n";	//report it
		exit(EXIT_FAILURE);					//exit and report failure
	}

	if(access(OLOGFILE, F_OK) != -1)				//if old log exists
		std::remove(OLOGFILE);					//delete it
	if(access(NLOGFILE, F_OK) != -1)					 //if new log file exists
		std::rename(NLOGFILE,OLOGFILE);				//make it old log file

	CLog().get(Info) << "gskConsensus V0.1 (9-2-13) courtesy of the WPI Distributed Systems Group.";
}

void quit(bool success)
{
	std::remove(PIDFILE);						//get rid of the PID file
	if(success)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_SUCCESS);
}

void timeout_call_back(union sigval)
{
	quit(true);
}

int main()
{
	pid_t pid;							//process ID
	pid_t sid;							//session ID

	std::ofstream pidFile;

	initialize();


	
	pid = fork();							//fork off a child prcess
	if(pid == 0)
	{
		//parent stuff
	}
	else 
	{
		std::cout << pid << "\n";
	}

	if(pid<0)							//if there was an error
		quit(false);						//exit and report an error
	if(pid>0)							//otherwise
		quit(false);						//kill the parent process
	
	umask(0);							//we want to edit files

	pidFile.open(PIDFILE);
	pidFile << pid;
	pidFile.close();

	sid  = setsid();						//create a new session ID
	if(sid<0)							//if that failed
	{
		CLog().get(FatalError) << "Unable to assign SID";
		quit(false);						//exit and report failure
	}

	if(chdir("/")<0)						//change to root directory
	{								//and test for failure
		CLog().get(FatalError) << "Unable to change directories";
		quit(false);						//exit and report failure
	}

	close(STDIN_FILENO);						//close stdin,
	close(STDOUT_FILENO);						//stdout and
	close(STDERR_FILENO);						//stderr

	/******************DAEMON INITIALIZATION CODE HERE*************/

	sigevent sev;
	timer_t timerID;
	itimerspec its;

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_value.sival_ptr = &timerID; /* sigev_value is passed to our callback */
	sev.sigev_notify_function = &timeout_call_back;
	sev.sigev_notify_attributes = NULL;

	its.it_value.tv_sec = 10;
	its.it_interval.tv_sec = its.it_value.tv_sec;

	if(timer_create(CLOCK_REALTIME, &sev, &timerID) == -1)
	{
		CLog().get(FatalError) << "Timer could not be created";
		quit(false);
	}
	if (timer_settime(timerID, 0, &its, NULL) == -1)
	{
		CLog().get(FatalError) << "Timer couldn't be set";
	}

	while(true)
	{
		/**************DAEMON CODE HERE*****************/
	}

	quit(true);
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
