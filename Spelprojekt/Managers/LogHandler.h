#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>
#include <SFML\System.hpp>
#include <iomanip>

class LogHandler
{
private:
	void writeLog(const char *logger, const char *str, int type);
	LogHandler();
	std::ofstream file;
	static std::string log_file;
	static sf::Clock igt;
	bool print;
	bool enabled;

public:
	static LogHandler* instance();
	~LogHandler();

	static void enablePrint();
	static void disablePrint();
	static void setFile(const char *str);
	static void log(const char *str);
	static void log(const char *logger, const char *str);
	static void error(const char *str);
	static void error(const char* logger, const char *str);
	static void notify(const char *str);
	static void notify(const char* logger, const char *str);

	enum LogType {Log,Notify,Error};
};

