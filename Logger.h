#ifndef __LOGGER__
#define __LOGGER__

#include <sstream>
#include <fstream>
#include <string>

#define NLOGFILE "/var/log/gskConsensus.log.new"
#define OLOGFILE "/var/log/gskConsensus.log.old"

enum logLevel {Info, FatalError, Error, Warning, Debug};
const std::string logLevel_str[5]={ "Info","Fatal Error","Error", "Warning", "Debug" };

#define LOG(level) \
if (level > Log::maxLevel) ; \
else Log().Get(level)

class CLog
{
	public:
	CLog();
	~CLog();
	
	std::stringstream& get(logLevel level);
	static logLevel& maxLevel;

	private:
	std::ofstream logFile;
	std::stringstream logBuffer;
};

#endif
