#ifndef LOG_DEFINES_H
#define LOG_DEFINES_H

enum LogLevel
{
    LOG_LEVEL_DISABLED  = 0,

    LOG_LEVEL_ERROR     ,
    LOG_LEVEL_WARN      ,
    LOG_LEVEL_INFO      ,
    LOG_LEVEL_TRACE     ,
    LOG_LEVEL_DEBUG     ,
    LOG_LEVEL_FATAL     ,

    MAX_LOG_LEVEL,
};

#endif