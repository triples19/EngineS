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

	template<class T, class... Ts>
	void Debug(T&& prefix, fmt::format_string<Ts...> format, Ts&&... args) {
		auto msg = fmt::format(format, std::forward<Ts>(args)...);
		_logger->debug(prefix + msg);
	}

	template<class T, class... Ts>
	void Info(T&& prefix, fmt::format_string<Ts...> format, Ts&&... args) {
		auto msg = fmt::format(format, std::forward<Ts>(args)...);
		_logger->info(prefix + msg);
	}

	template<class T, class... Ts>
	void Warn(T&& prefix, fmt::format_string<Ts...> format, Ts&&... args) {
		auto msg = fmt::format(format, std::forward<Ts>(args)...);
		_logger->warn(prefix + msg);
	}

	template<class T, class... Ts>
	void Error(T&& prefix, fmt::format_string<Ts...> format, Ts&&... args) {
		auto msg = fmt::format(format, std::forward<Ts>(args)...);
		_logger->error(prefix + msg);
	}

	template<class T, class... Ts>
	void Fatal(T&& prefix, fmt::format_string<Ts...> format, Ts&&... args) {
		auto msg = fmt::format(format, std::forward<Ts>(args)...);
		_logger->error(prefix + msg);
		throw std::runtime_error(msg);
	}

	auto GetLogger() { return _logger; }

  private:
	std::shared_ptr<spdlog::logger> _logger;
};

} // namespace EngineS
