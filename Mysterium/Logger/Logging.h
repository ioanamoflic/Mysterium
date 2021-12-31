#pragma once
#include <iostream>

#ifdef LOGGERDLL_EXPORTS
#define LOGGING_API __declspec(dllexport)
#else
#define LOGGING_API __declspec(dllimport)
#endif

class LOGGING_API Logging
{
public:
	enum class Level
	{
		INFO,
		WARNING,
		ERROR
	};

	Logging(std::ostream&, Level = Level::INFO);
	void Log(const char*, Level = Level::INFO);
	void Log(const std::string&, Level = Level::INFO);
private:
	std::ostream& m_out;
	Level m_minimumLevel;
};

std::string LoggerLevelToString(Logging::Level);