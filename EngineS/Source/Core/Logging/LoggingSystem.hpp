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

} // namespace EngineS
