#include "Logging.h"

Logging::Logging(std::ostream& out, Level minimumLevel) : m_out(out), m_minimumLevel(minimumLevel)
{
	//empty body
}

void Logging::Log(const char* message, Level level)
{
	m_out << "[" << LoggerLevelToString(level) << "]: " << message << "\n";
}

void Logging::Log(const std::string& message, Level level)
{
	Log(message.c_str(), level);
}

std::string LoggerLevelToString(Logging::Level level)
{
	switch (level)
	{
	case Logging::Level::INFO: return "INFO"; break;
	case Logging::Level::WARNING: return "WARNING"; break;
	case Logging::Level::ERROR: return "ERROR"; break;
	default: return "";
	}
}
