#include <iostream>
#include <ctime>

#include <Core/Logger.h>

namespace TE
{
    Logger::Logger(std::ostream *stream, bool printSeverity, bool printTime)
    {
        _printSeverityLevel = printSeverity;
        _printTime = printTime;
        _osStream = stream;
        _loggerInstance = std::unique_ptr<Logger>(this);
        Clear();
    }

    void Logger::SetOutputStream(std::ostream *stream)
    {
        _osStream = stream;
    }

    void Logger::SetSeverityPrinting(bool state)
    {
        _printSeverityLevel = state;
    }

    void Logger::SetTimePrinting(bool state)
    {
        _printTime = state;
    }

    void Logger::Message(std::string message, Severity severityLevel)
    {
        _loggerInstance->PushMessage(message, severityLevel);
    }

    void Logger::PushMessage(std::string message, Severity severityLevel)
    {
        std::string sTime = "";
        std::string sSeverity = "";

        if (_printSeverityLevel)
        {
            sSeverity += "[";

            switch (severityLevel)
            {
                case Severity::Info:
                    sSeverity += "Info";
                    break;
                case Severity::Warning:
                    sSeverity += "Warning";
                    break;
                case Severity::Error:
                    sSeverity += "Error";
                    break;
                case Severity::Fatal:
                    sSeverity += "Fatal";
                    break;
            }

            sSeverity += "] ";
        }

        if (_printTime)
        {
            const std::time_t current_time = std::time(nullptr);
            const std::tm calendar_time = *std::localtime(std::addressof(current_time));

            sTime = std::string("[")
                    + (calendar_time.tm_hour < 10 ? "0" : "")
                    + std::to_string(calendar_time.tm_hour) + ":"
                    + (calendar_time.tm_min < 10 ? "0" : "")
                    + std::to_string(calendar_time.tm_min) + ":"
                    + (calendar_time.tm_sec < 10 ? "0" : "")
                    + std::to_string(calendar_time.tm_sec) + "] ";
        }

        std::string sFinalMessage = sTime + sSeverity + message + "\n";

        if (_osStream != nullptr)
        {
            (*_osStream) << sFinalMessage;
        }

        _logHistory.push_back(sFinalMessage);

        if (severityLevel == Severity::Fatal)
        {
            throw std::runtime_error(message.c_str());
        }
    }

    std::string Logger::GetLastMessage()
    {
        size_t iSize = _logHistory.size();
        if (iSize >= 1)
        {
            return _logHistory.back();
        }
        else
        {
            return "\n";
        }
    }
}