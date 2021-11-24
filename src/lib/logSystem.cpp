#include "logSystem.hpp"

#include <cstdarg>
#include <memory>
#include <ctime>

#include <iostream>
#include <sstream>

using std::lock_guard;
using std::mutex;

namespace LOG{

SysLog *SysLog::m_instance = nullptr;
std::mutex SysLog::m_mutex;

SysLog* SysLog::getInstance()
{
    if (nullptr == m_instance)
    {
        const std::lock_guard<std::mutex> lock(m_mutex);
        if (nullptr == m_instance)
        {
            m_instance = new SysLog();
        }
    }
    return m_instance;
}

SysLog::SysLog()
    : m_log_level(INFO),
      m_out_file(nullptr)
{
}

SysLog::~SysLog()
{
    if (nullptr != m_out_file)
    {
        fclose(m_out_file);
        m_out_file = nullptr;
    }
}

void SysLog::logPrint(int loglevel, const char *format, ...)
{
    va_list v_list;

    if (loglevel <= m_log_level)
    {
        const std::lock_guard<std::mutex> lock(m_file_mutex);
        if (nullptr != m_out_file){
            va_start(v_list, format);
            vfprintf(m_out_file, format, v_list);
            va_end(v_list);
            fflush(m_out_file);
        }else{
            std::string file = getOutputFileName();
            m_out_file = fopen(file.c_str(), "w");
            if (nullptr != m_out_file)
            {
                fprintf(m_out_file, "[Log_Level] [Time] [TheadID] [FileName%sFunction:Line]\n", "|");
                va_start(v_list, format);
                vfprintf(m_out_file, format, v_list);
                va_end(v_list);
                fflush(m_out_file);
            }else{
                printf("[ERROR]: failed in generating log file.\n'");
            }
        }
    }

    if (loglevel == TRACE)
    {
        const std::lock_guard<std::mutex> lock(m_stdout_mutex);
        va_start(v_list, format);
        vprintf(format, v_list);
        va_end(v_list);
        fflush(stdout);
    }

    return;
}


std::string SysLog::getOutputFileName()
{
    std::stringstream strtime;
    std::time_t current_time = std::time(0);
    char time_all[200] = {0};
    std::strftime(time_all, sizeof(time_all), "%Y%m%d%H%M%S", std::localtime(&current_time));
    strtime << time_all;
    std::string file = strtime.str() + ".log";

    return file;
}

} // namespace LOG
