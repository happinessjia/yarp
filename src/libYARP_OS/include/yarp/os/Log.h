/*
 * Copyright (C) 2012-2014  iCub Facility, Istituto Italiano di Tecnologia
 * Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *          Marco Randazzo          <marco.randazzo@iit.it>
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef _YARP2_LOG_
#define _YARP2_LOG_

#include <yarp/os/api.h>
#include <iosfwd>

#ifndef YARP_NO_DEPRECATED
# include <cstdio>
# include <cstdlib>
# include <yarp/os/ConstString.h>
#endif

#if defined (__GNUC__)
# define __YFUNCTION__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
# define __YFUNCTION__ __FUNCSIG__
#elif (__cplusplus <= 199711)
# define __YFUNCTION__ __func__
#else
# define __YFUNCTION__ "(unknown function)"
#endif // __GNUC__

// check arguments of the c-style debug functions to make sure that the
// arguments supplied have types appropriate to the format string
// specified, and that the conversions specified in the format string
// make sense. On gcc the warning is enabled by -Wformat.
#if defined(__GNUC__)
# define YARP_ATTRIBUTE_FORMAT(style, fmt, args) __attribute__((format(printf, (fmt), (args))))
#else
# define YARP_ATTRIBUTE_FORMAT(style, fmt, args)
#endif


namespace yarp { namespace os { class LogStream; }}
namespace yarp { namespace os { namespace impl { class LogImpl; }}}


namespace yarp {
namespace os {

class YARP_OS_API Log
{
public:

    Log(const char *file,
        const unsigned int line,
        const char *func);
    Log();
    virtual ~Log();

    enum LogType {
        TraceType,
        DebugType,
        InfoType,
        WarningType,
        ErrorType,
        FatalType
    };

    void trace(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void debug(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void info(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void warning(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void error(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void fatal(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);

    void nofw_trace(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void nofw_debug(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void nofw_info(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void nofw_warning(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void nofw_error(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);
    void nofw_fatal(const char *msg, ...) const YARP_ATTRIBUTE_FORMAT(printf, 2, 3);

    LogStream trace() const;
    LogStream debug() const;
    LogStream info() const;
    LogStream warning() const;
    LogStream error() const;
    LogStream fatal() const;

    LogStream nofw_trace() const;
    LogStream nofw_debug() const;
    LogStream nofw_info() const;
    LogStream nofw_warning() const;
    LogStream nofw_error() const;
    LogStream nofw_fatal() const;

#ifndef YARP_NO_DEPRECATED
    YARP_DEPRECATED virtual void debug(const ConstString& txt) const { debug("%s", txt.c_str()); } ///< \deprecated since YARP 2.3.64
    YARP_DEPRECATED virtual void info(const ConstString& txt) const { info("%s", txt.c_str()); } ///< \deprecated since YARP 2.3.64
    YARP_DEPRECATED virtual void warning(const ConstString& txt) const { warning("%s", txt.c_str()); } ///< \deprecated since YARP 2.3.64
    YARP_DEPRECATED virtual void error(const ConstString& txt) const { error("%s", txt.c_str()); } ///< \deprecated since YARP 2.3.64
    YARP_DEPRECATED virtual void fail(const ConstString& txt) const { fatal("%s", txt.c_str()); } ///< \deprecated since YARP 2.3.64
#endif // YARP_NO_DEPRECATED

    typedef void (*LogCallback)(yarp::os::Log::LogType,
                                const char *,
                                const char *,
                                const unsigned int,
                                const char *);

    static void setLogCallback(LogCallback);

private:
    yarp::os::impl::LogImpl * const mPriv;

    static LogCallback print_callback;
    static LogCallback forward_callback;

    friend class LogStream;
}; // class Log

} // namespace os
} // namespace yarp


#define yTrace   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).trace
#define yDebug   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).debug
#define yInfo    yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).info
#define yWarning yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).warning
#define yError   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).error
#define yFatal   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).fatal

#define yTraceNoFw   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_trace
#define yDebugNoFw   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_debug
#define yInfoNoFw    yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_info
#define yWarningNoFw yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_warning
#define yErrorNoFw   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_error
#define yFatalNoFw   yarp::os::Log(__FILE__, __LINE__, __YFUNCTION__).nofw_fatal

#define yAssert(x)  if (!(x)) { yFatal("Assertion failure (%s)", #x); }

#define YARP_FIXME_NOTIMPLEMENTED(what) yWarning("FIXME: %s not yet implemented", what);


/**
 * Low level function for printing a stack trace, if implemented (ACE or gcc/Linux).
 */
YARP_OS_API void yarp_print_trace(FILE *out, const char *file, int line);


#ifndef YARP_NO_DEPRECATED

YARP_OS_API YARP_DEPRECATED inline void __yarp_debug(const yarp::os::ConstString& str) { yDebug("%s", str.c_str()); } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline void __yarp_info(const yarp::os::ConstString& str) { yInfo("%s", str.c_str()); } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline void __yarp_warn(const yarp::os::ConstString& str) { yWarning("%s", str.c_str()); } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline void __yarp_error(const yarp::os::ConstString& str) { yError("%s", str.c_str()); } ///< \deprecated since YARP 2.3.64

YARP_OS_API YARP_DEPRECATED inline bool yarp_show_error() { return true; } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline bool yarp_show_warn() { return true; } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline bool yarp_show_info() { return true; } ///< \deprecated since YARP 2.3.64
YARP_OS_API YARP_DEPRECATED inline bool yarp_show_debug() { return true; } ///< \deprecated since YARP 2.3.64

/**
 * \deprecated since YARP 2.3.64
 */
#define YARP_LOG_ERROR(x) __yarp_error(x)

/**
 * \deprecated since YARP 2.3.64
 */
#define YARP_LOG_WARN(x) __yarp_warn(x)

/**
 * \deprecated since YARP 2.3.64
 */
#define YARP_LOG_INFO(x) __yarp_info(x)

/**
 * \deprecated since YARP 2.3.64
 */
#define YARP_LOG_DEBUG(x) __yarp_debug(x)

/**
 * Very basic assertion macro.
 *
 * \deprecated since YARP 2.3.64
 */
#define YARP_ASSERT(x) yAssert(x)

#endif // YARP_NO_DEPRECATED

#endif // _YARP2_LOG_
