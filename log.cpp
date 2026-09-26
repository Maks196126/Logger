#include "log.h"

#include <chrono>
#include <format>
#include <iostream>
#include <thread>

namespace logger {

namespace {
const char *toString(LogLevel level)
{
    switch (level) {
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    }
    return "";
}
} // namespace

LogMessage::LogMessage(LogLevel level, const std::string &prefix)
    : m_stream(std::cout)
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    m_stream << std::format("{:%d.%m.%Y %H:%M:%S}", now) << "; " << toString(level) << "; "
             << prefix << '(' << std::this_thread::get_id() << "): ";
}

LogMessage::~LogMessage()
{
    m_stream << '\n';
}

Logger::Logger(std::string prefix)
    : m_prefix(std::move(prefix))
{}

LogMessage Logger::operator()(LogLevel level) const
{
    return LogMessage(level, m_prefix);
}

Logger getLogger(const std::string &prefix)
{
    return Logger(prefix);
}

} // namespace logger
