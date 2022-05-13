#pragma once

#include <iostream>

class Log
{
public:
	enum Level : unsigned char
	{
		LevelError, LevelWarning, LevelInfo
	};
private:
	Level m_LogLevel = LevelInfo;
public:
	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}

	template <class T>
	void Error(T message)
	{
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR] " << message << std::endl;
	}

	template <class T>
	void Warning(T message)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WAENING] " << message << std::endl;
	}

	template <class T>
	void Info(T message)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO] " << message << std::endl;
	}
};