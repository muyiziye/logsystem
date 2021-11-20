#include "logSystem.hpp"
#include <cstdarg>
#include <iostream>
#include <memory>

using std::lock_guard;
using std::mutex;

namespace LOG{

SysLog *SysLog::m_instance = NULL;
std::mutex SysLog::m_mutex;

SysLog* SysLog::getInstance()
{
    if (NULL == m_instance)
    {
        const std::lock_guard<std::mutex> lock(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new SysLog();
        }
    }
    return m_instance;
}

SysLog::SysLog()
    : m_logLevel(INFO)
{
    m_out_file = fopen("log.txt", "w");
}

SysLog::~SysLog()
{
    if (NULL != m_out_file)
    {
        fclose(m_out_file);
        m_out_file = NULL;
    }
}

void SysLog::log_print(int loglevel, const char *format, ...)
{
    va_list v_list;

    va_start(v_list, format);

    if ((loglevel <= m_logLevel) && (NULL != m_out_file))
    {
        vfprintf(m_out_file, format, v_list);
    }

    if (loglevel == TRACE)
    {
        vprintf(format, v_list);
    }

    va_end(v_list);

    return;
}

} // namespace LOG
