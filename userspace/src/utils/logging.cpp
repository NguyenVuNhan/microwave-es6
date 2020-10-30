#include "logging.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace logging;

Logger* Logger::m_Instance = 0;

const string logFileName = "logging.log";

Logger::Logger()
{
    m_File.open(logFileName.c_str(), ios::out | ios::app);
    m_LogLevel = LOG_LEVEL_TRACE;
    m_LogType  = FILE_LOG;

    int ret = 0;
    ret     = pthread_mutexattr_settype(&m_Attr, PTHREAD_MUTEX_ERRORCHECK_NP);
    if (ret != 0)
    {
        printf("Logger::Logger() -- Mutex attribute not initialize!!\n");
        exit(0);
    }
    ret = pthread_mutex_init(&m_Mutex, &m_Attr);
    if (ret != 0)
    {
        printf("Logger::Logger() -- Mutex not initialize!!\n");
        exit(0);
    }
}

Logger::~Logger()
{
    m_File.close();
    pthread_mutexattr_destroy(&m_Attr);
    pthread_mutex_destroy(&m_Mutex);
}

Logger* Logger::getInstance() throw()
{
    if (m_Instance == 0)
    {
        m_Instance = new Logger();
    }
    return m_Instance;
}

void Logger::lock()
{
    pthread_mutex_lock(&m_Mutex);
}

void Logger::unlock()
{
    pthread_mutex_unlock(&m_Mutex);
}

void Logger::logIntoFile(std::string& data, bool verbose)
{
    lock();
    m_File << (verbose ? getCurrentTime() : "") << "  " << data << endl;
    unlock();
}

void Logger::logOnConsole(std::string& data, bool verbose)
{
    cout << (verbose ? getCurrentTime() : "") << "  " << data << endl;
}

void Logger::log(std::string& data, bool verbose)
{
    switch (m_LogType)
    {
        case FILE_LOG:
            logIntoFile(data, verbose);
            break;
        case CONSOLE:
            logOnConsole(data, verbose);
            break;
        case CONSOLE_AND_FILE:
            logIntoFile(data, verbose);
            logOnConsole(data, verbose);
            break;
        default:
            break;
    }
}

string Logger::getCurrentTime()
{
    string currTime;
    time_t now = time(0);
    currTime.assign(ctime(&now));

    string currentTime = currTime.substr(0, currTime.size() - 1);
    return currentTime;
}

void Logger::error(const char* text) throw()
{
    string data;
    data.append("[ERROR]: ");
    data.append(text);

    log(data);
}

void Logger::error(std::string& text) throw()
{
    error(text.data());
}

void Logger::error(std::ostringstream& stream) throw()
{
    string text = stream.str();
    error(text.data());
}

void Logger::alarm(const char* text) throw()
{
    string data;
    data.append("[ALARM]: ");
    data.append(text);

    log(data);
}

void Logger::alarm(std::string& text) throw()
{
    alarm(text.data());
}

void Logger::alarm(std::ostringstream& stream) throw()
{
    string text = stream.str();
    alarm(text.data());
}

void Logger::always(const char* text) throw()
{
    string data;
    data.append("[ALWAYS]: ");
    data.append(text);

    log(data);
}

void Logger::always(std::string& text) throw()
{
    always(text.data());
}

void Logger::always(std::ostringstream& stream) throw()
{
    string text = stream.str();
    always(text.data());
}

void Logger::buffer(const char* text) throw()
{
    string data;
    data.append(text);

    if (m_LogLevel >= LOG_LEVEL_BUFFER)
    {
        log(data);
    }
}

void Logger::buffer(std::string& text) throw()
{
    buffer(text.data());
}

void Logger::buffer(std::ostringstream& stream) throw()
{
    string text = stream.str();
    buffer(text.data());
}

void Logger::info(const char* text) throw()
{
    string data;
    data.append("[INFO]: ");
    data.append(text);

    if (m_LogLevel >= LOG_LEVEL_INFO)
    {
        log(data);
    }
}

void Logger::info(std::string& text) throw()
{
    info(text.data());
}

void Logger::info(std::ostringstream& stream) throw()
{
    string text = stream.str();
    info(text.data());
}

void Logger::trace(const char* text) throw()
{
    string data;
    data.append("[TRACE]: ");
    data.append(text);

    if (m_LogLevel >= LOG_LEVEL_TRACE)
    {
        log(data);
    }
}

void Logger::trace(std::string& text) throw()
{
    trace(text.data());
}

void Logger::trace(std::ostringstream& stream) throw()
{
    string text = stream.str();
    trace(text.data());
}

void Logger::debug(const char* text) throw()
{
    string data;
    data.append("[DEBUG]: ");
    data.append(text);

    if (m_LogLevel >= LOG_LEVEL_DEBUG)
    {
        log(data);
    }
}

void Logger::debug(std::string& text) throw()
{
    debug(text.data());
}

void Logger::debug(std::ostringstream& stream) throw()
{
    string text = stream.str();
    debug(text.data());
}

void Logger::updateLogLevel(LogLevel logLevel)
{
    m_LogLevel = logLevel;
}

void Logger::updateLogType(LogType logType)
{
    m_LogType = logType;
}
