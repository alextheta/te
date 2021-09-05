#pragma once

#include <deque>
#include <string>

namespace TE
{
    class Logger
    {
    public:
        enum Severity
        {
            Info,
            Warning,
            Error,
            Fatal
        };

        static Logger &Instance()
        {
            static Logger Self;
            return Self;
        }

        void SetOutputStream(std::ostream *stream);
        void SetSeverityPrinting(bool state);
        void SetTimePrinting(bool state);

        void Message(std::string message, Severity severityLevel = Info);

        std::string GetLastMessage();

        inline std::deque<std::string> GetMessages()
        {
            return _logHistory;
        };

        inline void Clear()
        {
            _logHistory.clear();
        };

    private:
        Logger();
        Logger(const Logger &LogObject) = delete;
        Logger &operator=(const Logger &) = delete;

        ~Logger()
        {
        };

        bool _printSeverityLevel;
        bool _printTime;
        std::ostream *_osStream;
        std::deque<std::string> _logHistory;
    };
}