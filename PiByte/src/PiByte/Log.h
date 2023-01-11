#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include <memory>
#include <string>


namespace pibyte
{

	PIBYTE_API static enum LogLevel
	{
		info, warn, error
	};

	static spdlog::level::level_enum GetLevel(LogLevel loglevel);


	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> logger;
	public:
		PIBYTE_API inline static std::shared_ptr<spdlog::logger>& get_logger() { return Log::logger; }
		PIBYTE_API static void init_console_log(LogLevel t_level);
	};

}

#define PB_LOGINFO(...) pibyte::Log::get_logger()->info(__VA_ARGS__)
#define PB_LOGWARN(...) pibyte::Log::get_logger()->warn(__VA_ARGS__)
#define PB_LOGERROR(...) pibyte::Log::get_logger()->error(__VA_ARGS__)