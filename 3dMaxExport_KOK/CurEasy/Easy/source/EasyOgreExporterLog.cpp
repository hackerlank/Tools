#include "EasyOgreExporterLog.h"

#include <stdio.h>
#ifdef WIN32
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include <iostream>
#include <fstream>

namespace EasyOgreExporter
{
	// The full path to the log file.
	std::string EasyOgreExporterLogFile::_logPath;

	// Sets the full path to the log file.
	void EasyOgreExporterLogFile::SetPath(const std::string& logPath)
	{
		_logPath = logPath;

		// Erase the contents of the log file.
		if (_logPath.size() > 0)
		{
			std::ofstream output(_logPath.c_str());
			EasyOgreExporterLog("Logging to file %s\n", _logPath.c_str());
		}
	}

	// Returns the full path to the log file.
	std::string EasyOgreExporterLogFile::GetPath(void)
	{
		return _logPath;
	}

	// Printf-style log output.
	void EasyOgreExporterLogFile::Log(const char* format, ...)
	{
		va_list	argList;
		//warning for long messages
		char buffer[4096];

		va_start(argList, format);
		vsprintf_s(buffer, 4096, format, argList);
		va_end(argList);

		if (_logPath.size() > 0)
		{
			std::ofstream output(_logPath.c_str(), std::ios_base::app);
			if (output)
			{
				output << buffer;//<< "\r\n";
			}
		}
	}

	void EasyOgreExporterLogFile::operator<<(const char* str)
	{
		Log(str);
	}
} // namespace


