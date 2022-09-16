#include "LoggingSystem.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace EngineS {

static LoggingSystem* s_SharedInstance;

LoggingSystem* LoggingSystem::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) LoggingSystem;
		assert(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

LoggingSystem::LoggingSystem() {
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::trace);
	consoleSink->set_pattern("[%^%l%$] %v");

	const spdlog::sinks_init_list sinkList = {consoleSink};

	spdlog::init_thread_pool(8192, 1);

	_logger = std::make_shared<spdlog::async_logger>("muggle_logger",
													 sinkList.begin(),
													 sinkList.end(),
													 spdlog::thread_pool(),
													 spdlog::async_overflow_policy::block);
	_logger->set_level(spdlog::level::trace);
	spdlog::register_logger(_logger);
}

LoggingSystem::~LoggingSystem() {
	_logger->flush();
	spdlog::drop_all();
}

} // namespace EngineS