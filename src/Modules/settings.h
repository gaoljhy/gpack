#pragma once
// settings for Module
// TODO - replace with runtime config. libucl?

/* #ifdef - enables debug mode */
//#define Module_ENABLE_DEBUG

/* #ifdef - enables logging */
#define Module_ENABLE_LOGGING

/* #ifdef - enables ssl */
//#define Module_ENABLE_SSL

/* #define - specifies log level */
/*
    Debug       = 0
    Info        = 1
    Warning     = 2
    Error       = 3
    Critical    = 4

    default to INFO
*/
#ifndef Module_LOG_LEVEL
#define Module_LOG_LEVEL 1
#endif


// compiler flags
#if __cplusplus >= 201402L
#define Module_CAN_USE_CPP14
#endif

#if defined(_MSC_VER)
#if _MSC_VER < 1900
#define Module_MSVC_WORKAROUND
#define constexpr const
#define noexcept throw()
#endif
#endif
