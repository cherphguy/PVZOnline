#pragma once
// FROM luna/IO/Logger, thx to vb and uniqua
enum class LogLevel { none, info, warn, error };

namespace Logger {
    class ConsoleLogger {
    public:
        ConsoleLogger();

        void log(LogLevel level, const char* message, ...);
    };
}