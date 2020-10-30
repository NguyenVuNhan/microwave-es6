#ifndef __LOGGING_H
#define __LOGGING_H

#include <errno.h>
#include <pthread.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace logging
{
#define LOG_ERROR(x)     Logger::getInstance()->error(x)
#define LOG_ALARM(x)     Logger::getInstance()->alarm(x)
#define LOG_ALWAYS(x)    Logger::getInstance()->always(x)
#define LOG_INFO(x)      Logger::getInstance()->info(x)
#define LOG_BUFFER(x)    Logger::getInstance()->buffer(x)
#define LOG_TRACE(x)     Logger::getInstance()->trace(x)
#define LOG_DEBUG(x)     Logger::getInstance()->debug(x)
#define LOG_LEVEL(level) Logger::getInstance()->updateLogLevel(level)
#define LOG_TYPE(type)   Logger::getInstance()->updateLogType(type)

    // enum for LOG_LEVEL
    typedef enum LOG_LEVEL
    {
        DISABLE_LOG      = 1,
        LOG_LEVEL_INFO   = 2,
        LOG_LEVEL_BUFFER = 3,
        LOG_LEVEL_TRACE  = 4,
        LOG_LEVEL_DEBUG  = 5,
        ENABLE_LOG       = 6,
    } LogLevel;

    // enum for LOG_TYPE
    typedef enum LOG_TYPE
    {
        NO_LOG           = 1,
        CONSOLE          = 2,
        FILE_LOG         = 3,
        CONSOLE_AND_FILE = 4,
    } LogType;

    class Logger
    {
    public:
        static Logger* getInstance() throw();

        void error(const char* text) throw();
        void error(std::string& text) throw();
        void error(std::ostringstream& stream) throw();

        void alarm(const char* text) throw();
        void alarm(std::string& text) throw();
        void alarm(std::ostringstream& stream) throw();

        void always(const char* text) throw();
        void always(std::string& text) throw();
        void always(std::ostringstream& stream) throw();

        void buffer(const char* text) throw();
        void buffer(std::string& text) throw();
        void buffer(std::ostringstream& stream) throw();

        void info(const char* text) throw();
        void info(std::string& text) throw();
        void info(std::ostringstream& stream) throw();

        void trace(const char* text) throw();
        void trace(std::string& text) throw();
        void trace(std::ostringstream& stream) throw();

        void debug(const char* text) throw();
        void debug(std::string& text) throw();
        void debug(std::ostringstream& stream) throw();

        void updateLogLevel(LogLevel logLevel);
        void updateLogType(LogType logType);

    protected:
        Logger();
        ~Logger();

        void lock();
        void unlock();

        std::string getCurrentTime();

    private:
        void log(std::string& data, bool verbose = true);
        void logIntoFile(std::string& data, bool verbose = true);
        void logOnConsole(std::string& data, bool verbose = true);
        Logger(const Logger& obj) {}
        void operator=(const Logger& obj) {}

    private:
        static Logger* m_Instance;
        std::ofstream  m_File;

        pthread_mutexattr_t m_Attr;
        pthread_mutex_t     m_Mutex;

        LogLevel m_LogLevel;
        LogType  m_LogType;
    };

} // namespace logging

#endif // End of __LOGGING_H
