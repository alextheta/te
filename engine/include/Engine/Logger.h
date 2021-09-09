#pragma once

#include <memory>
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

        Logger(std::ostream *stream, bool printSeverity, bool printTime);

        void SetOutputStream(std::ostream *stream);
        void SetSeverityPrinting(bool state);
        void SetTimePrinting(bool state);

        static void Message(std::string message, Severity severityLevel = Info);

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
        //Logger();

        inline static std::unique_ptr<TE::Logger> _loggerInstance;

        bool _printSeverityLevel;
        bool _printTime;
        std::ostream *_osStream;
        std::deque<std::string> _logHistory;

        void PushMessage(std::string message, Severity severityLevel = Info);
    };
}