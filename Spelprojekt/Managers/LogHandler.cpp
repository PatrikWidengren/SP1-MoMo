#include "LogHandler.h"

/*
Note, this code is from Matti Karjalainen, 
the guy who helped me with a bunch of coding.
I asked him if it was okay to use this and he
said it's okay as long as we put him in special
thanks!
*/

std::string LogHandler::log_file = "log.txt";
sf::Clock LogHandler::igt;

LogHandler::LogHandler()
{
	print = true;
	file.open(LogHandler::log_file);
	if (file.is_open())
		enabled = true;
	else
		enabled = false;
}

void LogHandler::disablePrint()
{
	instance()->print = false;
}

void LogHandler::enablePrint()
{
	instance()->print = true;
}

void LogHandler::setFile(const char* str)
{
	LogHandler::log_file = str;
}

LogHandler* LogHandler::instance()
{
	static LogHandler loghandler;
	return &loghandler;
}

void LogHandler::writeLog(const char *logger,const char *str,int type)
{
	if (enabled)
	{
		char sep = ' ';
		switch (type)
		{
		default:
		case Log:
			sep = ' ';
			break;
		case Notify:
			sep = '-';
			break;
		case Error:
			sep = '*';
			break;
		}

		std::ostringstream output;

		time_t now;
		struct tm timedata;
		time(&now);
		localtime_s(&timedata, &now);

		long long elapsedTime=igt.getElapsedTime().asMilliseconds();
		
		std::ostringstream timestr;
		timestr.fill('0');
		timestr.width(2);
		timestr << timedata.tm_mon + 1 << '/';
		timestr.fill('0');
		timestr.width(2);
		timestr << timedata.tm_mday << '/' << timedata.tm_year + 1900 << sep;
		timestr.fill('0');
		timestr.width(2);
		timestr << timedata.tm_hour << ':';
		timestr.fill('0');
		timestr.width(2);
		timestr << timedata.tm_min << ':';
		timestr.fill('0');
		timestr.width(2);
		timestr << timedata.tm_sec;

		std::ostringstream buffer;
		buffer.fill('0');
		buffer.width(10);
		buffer << elapsedTime;
		output << timestr.str() << sep << buffer.str() << sep;
		if (logger)
		output << '[' << logger << "] ";
		
		switch (type)
		{
		default:
		case Log:
		case Notify:
			output << str;
			break;
		case Error:
			output << "ERROR: " << str;
			break;
		}
		output << '\n';

		if (print)
			std::cout << output.str();
		file << output.str();
	}
}

void LogHandler::log(const char *str)
{
	instance()->writeLog(0, str, Log);
}

void LogHandler::error(const char *str)
{
	instance()->writeLog(0, str, Error);
}

void LogHandler::error(const char* logger,const char *str)
{
	instance()->writeLog(logger, str, Error);
}

void LogHandler::log(const char *logger,const char *str)
{
	instance()->writeLog(logger, str, Log);
}

void LogHandler::notify(const char *str)
{
	instance()->writeLog(0, str, Notify);
}

void LogHandler::notify(const char *logger, const char *str)
{
	instance()->writeLog(logger, str, Notify);
}

LogHandler::~LogHandler()
{
	if (enabled)
		file.close();
}
