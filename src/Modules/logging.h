#pragma once

#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

#include "Module/settings.h"

namespace Module
{
    enum class LogLevel
    {
#ifndef ERROR
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
#endif

        Debug = 0,
        Info,
        Warning,
        Error,
        Critical,
    };

    class ILogHandler {
        public:
            virtual void log(std::string message, LogLevel level) = 0;
    };

    class CerrLogHandler : public ILogHandler {
        public:
            void log(std::string message, LogLevel /*level*/) override {
                std::cerr << message;
            }
    };

    class logger {

        private:
            //
            static std::string timestamp()
            {
                char date[32];
                time_t t = time(0);

                tm my_tm;

#if defined(_MSC_VER) or defined(__MINGW32__)
                gmtime_s(&my_tm, &t);
#else
                gmtime_r(&t, &my_tm);
#endif

                size_t sz = strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &my_tm);
                return std::string(date, date+sz);
            }

        public:


            logger(std::string prefix, LogLevel level) : level_(level) {
    #ifdef Module_ENABLE_LOGGING
                    stringstream_ << "(" << timestamp() << ") [" << prefix << "] ";
    #endif

            }
            ~logger() {
    #ifdef Module_ENABLE_LOGGING
                if(level_ >= get_current_log_level()) {
                    stringstream_ << std::endl;
                    get_handler_ref()->log(stringstream_.str(), level_);
                }
    #endif
            }

            //
            template <typename T>
            logger& operator<<(T const &value) {

    #ifdef Module_ENABLE_LOGGING
                if(level_ >= get_current_log_level()) {
                    stringstream_ << value;
                }
    #endif
                return *this;
            }

            //
            static void setLogLevel(LogLevel level) {
                get_log_level_ref() = level;
            }

            static void setHandler(ILogHandler* handler) {
                get_handler_ref() = handler;
            }

            static LogLevel get_current_log_level() {
                return get_log_level_ref();
            }

        private:
            //
            static LogLevel& get_log_level_ref()
            {
                static LogLevel current_level = (LogLevel)Module_LOG_LEVEL;
                return current_level;
            }
            static ILogHandler*& get_handler_ref()
            {
                static CerrLogHandler default_handler;
                static ILogHandler* current_handler = &default_handler;
                return current_handler;
            }

            //
            std::ostringstream stringstream_;
            LogLevel level_;
    };
}

#define Module_LOG_CRITICAL   \
        if (Module::logger::get_current_log_level() <= Module::LogLevel::Critical) \
            Module::logger("CRITICAL", Module::LogLevel::Critical)
#define Module_LOG_ERROR      \
        if (Module::logger::get_current_log_level() <= Module::LogLevel::Error) \
            Module::logger("ERROR   ", Module::LogLevel::Error)
#define Module_LOG_WARNING    \
        if (Module::logger::get_current_log_level() <= Module::LogLevel::Warning) \
            Module::logger("WARNING ", Module::LogLevel::Warning)
#define Module_LOG_INFO       \
        if (Module::logger::get_current_log_level() <= Module::LogLevel::Info) \
            Module::logger("INFO    ", Module::LogLevel::Info)
#define Module_LOG_DEBUG      \
        if (Module::logger::get_current_log_level() <= Module::LogLevel::Debug) \
            Module::logger("DEBUG   ", Module::LogLevel::Debug)

