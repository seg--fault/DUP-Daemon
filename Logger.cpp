#include "Logger.h"

CLog::CLog()
{
	logFile.open(NLOGFILE,std::ofstream::out);
}
CLog::~CLog()
{
	logFile << logBuffer.str();
	logFile.close();
}

std::stringstream& CLog::get(logLevel level)
{
	logBuffer << "-> "<< logLevel_str[level] << " " /*<<NowTime()<<ToString(level)*/;
	return logBuffer;
}
