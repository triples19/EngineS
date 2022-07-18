#pragma once

#include "Function/Global/Global.hpp"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

#include <cstdint>
#include <memory>

namespace EngineS {

class LoggingSystem {
  public:
	enum class LogLevel : uint8_t { Debug, Info, Warn, Error, Fatal };

  public:
	LoggingSystem();
	~LoggingSystem();

	template<class... Ts>
	void Debug(Ts&&... args) {
		_logger->debug(std::forward<Ts>(args)...);
	}

	template<class... Ts>
	void Info(Ts&&... args) {
		_logger->info(std::forward<Ts>(args)...);
	}

	template<class... Ts>
	void Warn(Ts&&... args) {
		_logger->warn(std::forward<Ts>(args)...);
	}

	template<class... Ts>
	void Error(Ts&&... args) {
		_logger->error(std::forward<Ts>(args)...);
	}

	template<class... Ts>
	void Fatal(Ts&&... args) {
		_logger->critical(std::forward<Ts>(args)...);
		const std::string formatStr = fmt::format(std::forward<Ts>(args)...);
		throw std::runtime_error(formatStr);
	}

	auto GetLogger() { return _logger; }

  private:
	std::shared_ptr<spdlog::logger> _logger;
};

#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_PREFIX fmt::format("[{0}:{1}] {2} > ", FILENAME, __LINE__, __FUNCTION__)

#define LOG_DEBUG(...) Global::Instance()->loggingSystem->Debug(LOG_PREFIX + __VA_ARGS__)
#define LOG_INFO(...) Global::Instance()->loggingSystem->Info(LOG_PREFIX + __VA_ARGS__)
#define LOG_WARN(...) Global::Instance()->loggingSystem->Warn(LOG_PREFIX + __VA_ARGS__)
#define LOG_ERROR(...) Global::Instance()->loggingSystem->Error(LOG_PREFIX + __VA_ARGS__)
#define LOG_FATAL(...) Global::Instance()->loggingSystem->Fatal(LOG_PREFIX + __VA_ARGS__)

} // namespace EngineS
