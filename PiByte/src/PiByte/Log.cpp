#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace pibyte
{
	std::shared_ptr<spdlog::logger> Log::logger;

	spdlog::level::level_enum GetLevel(LogLevel loglevel)
	{
		switch (loglevel)
		{
		case 0:
			return spdlog::level::info;
			break;
		case 1:
			return spdlog::level::warn;
			break;
		case 2:
			return spdlog::level::err;
		}
	}

	void Log::init_console_log(LogLevel t_level)
	{
		spdlog::set_pattern("%^[%d-%m-%C %T] [%n] [%l] %v%$");


		logger = spdlog::stdout_color_st("ConsoleLog");
		logger->set_level(GetLevel(t_level));
	}
}