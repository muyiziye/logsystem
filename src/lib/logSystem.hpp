#ifndef __LIB_LOGSYSTEM_HPP__
#define __LIB_LOGSYSTEM_HPP__

#include <mutex>
#include <cstdio>

#define TRACE 0
#define ERR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

#define LOG_TRACE(format, ...) LOG::SysLog::getInstance()->log_print(0, format, __VA_ARGS__);
#define LOG_ERR(format, ...) LOG::SysLog::getInstance()->log_print(1, "[Error] " format, __VA_ARGS__);
#define LOG_WARN(format, ...) LOG::SysLog::getInstance()->log_print(2, "[Warn] " format, __VA_ARGS__);
#define LOG_INFO(format, ...) LOG::SysLog::getInstance()->log_print(3, "[Info] " format, __VA_ARGS__);
#define LOG_DEBUG(format, ...) LOG::SysLog::getInstance()->log_print(4, "[Debug] " format, __VA_ARGS__);

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

