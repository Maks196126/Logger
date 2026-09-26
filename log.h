#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <syncstream>

namespace logger {

enum class LogLevel { INFO, DEBUG, WARNING, ERROR };

class LogMessage
{
public:
    LogMessage(LogLevel level, const std::string &prefix);
    LogMessage(LogMessage &&) = default;
    ~LogMessage();

    template<typename T>
    LogMessage &operator<<(const T &value)
    {
        m_stream << value;
        return *this;
    }

private:
    std::osyncstream m_stream;
};

class Logger
{
public:
    explicit Logger(std::string prefix = "");

    LogMessage operator()(LogLevel level) const;

    template<typename T>
    LogMessage operator<<(const T &value) const
    {
        LogMessage msg(LogLevel::INFO, m_prefix);
        msg << value;
        return msg;
    }

private:
    std::string m_prefix;
};

Logger getLogger(const std::string &prefix = "");

} // namespace logger

using logger::getLogger;
using logger::Logger;
using enum logger::LogLevel;

#endif // LOGGER_H
