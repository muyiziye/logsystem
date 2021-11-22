#ifndef __LIB_LOGSYSTEM_HPP__
#define __LIB_LOGSYSTEM_HPP__

#include <mutex>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#include <string>
#include <iostream>

#define TRACE 0
#define ERR 1
#define WARN 2
#define INFO 3
#define DEBUG 4


#define FILE(x) strrchr(x, '/') ? strrchr(x, '/')+1 : x

#define FORMAT_STR(format) \
    "[" + std::string(__DATE__) + "-" + __TIME__ + "]" + "[" + std::to_string(pthread_self()) + "]" +\
    "[" + std::string(FILE(__FILE__)) + " " + __func__ + ":" + std::to_string(__LINE__) + "]" + format

#define LOG_TRACE(format, ...) \
    do{ \
        LOG::SysLog::getInstance()->log_print(0, format, ##__VA_ARGS__); \
    } while(0);

#define LOG_ERR(format, ...) \
    do{ \
        std::string format_str = std::string("[ERROR]") + FORMAT_STR(format) ; \
        LOG::SysLog::getInstance()->log_print(1, format_str.c_str(), __VA_ARGS__); \
    } while(0);

#define LOG_WARN(format, ...) \
    do{ \
        std::string format_str = std::string("[WARN ]") + FORMAT_STR(format); \
        LOG::SysLog::getInstance()->log_print(2, format_str.c_str(), __VA_ARGS__); \
    } while(0);

#define LOG_INFO(format, ...) \
    do{ \
        std::string format_str = std::string("[INFO ]") + FORMAT_STR(format); \
        LOG::SysLog::getInstance()->log_print(3, format_str.c_str(), __VA_ARGS__); \
    } while(0);

#define LOG_DEBUG(format, ...) \
    do{ \
        std::string format_str = std::string("[DEBUG]") + FORMAT_STR(format); \
        LOG::SysLog::getInstance()->log_print(4, format_str.c_str(), __VA_ARGS__); \
    } while(0);


namespace LOG{

class SysLog{
public:
	~SysLog();
	static SysLog* getInstance();

	void log_print(int loglevel, const char* format, ...);

private:
	SysLog();

    static SysLog* m_instance;
    static std::mutex m_mutex;
    int m_logLevel;
    FILE *m_out_file;
    std::mutex m_mutex_file;
};

} // namespace LOG

#endif // __LIB_LOGSYSTEM_HPP__

