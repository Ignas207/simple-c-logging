#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma clang diagnostic ignored "-Wstring-plus-int"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define LOGS_MAX_LENGHT 512U

/*
    Gets the path RELATIVE to CMakeLists!
    For this to work need to add the following to CMakeLists.txt!
    -------------------------------------------------------------
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
    add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
    -------------------------------------------------------------
*/
#ifndef SOURCE_PATH_SIZE
#warning SOURCE_PATH_SIZE is not defined! You have to set it youself, in "logs.h"!
#define SOURCE_PATH_SIZE 0U
#endif

/**
 * @brief We are using this to get rid of the absolute path of our project.
 *
 */
#define FILENAME__ (__FILE__ + SOURCE_PATH_SIZE)

#define __LOG_WRITE(type, fileName, lineNumber, fmt, ...)                      \
  do {                                                                         \
                                                                               \
    int32_t retSize;                                                           \
    va_list argp;                                                              \
    char logStr[LOGS_MAX_LENGHT] = {0};                                        \
                                                                               \
    /* Writing the starting portion */                                         \
    retSize = snprintf(logStr, LOGS_MAX_LENGHT, "%s (%s:%d): ", type,          \
                       fileName, lineNumber);                                  \
                                                                               \
    /* Writing the VA_ARGS */                                                  \
    va_start(argp, fmt);                                                       \
    vsnprintf(logStr + retSize, LOGS_MAX_LENGHT - retSize, fmt, argp);         \
    va_end(argp);                                                              \
                                                                               \
  } while (0)

#ifdef LOG_ENABLE_EVENT_MSG
/**
 * @brief Writes an 'Event' message to the terminal.
 *
 */
#define LOG_EVENT(fmt, ...)                                                    \
  ((LogWrite("EVENT", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))
#else
#define LOG_EVENT(fmt, ...)                                                    \
  do {                                                                         \
    (void)fmt;                                                                 \
  } while (0)
#endif

#ifdef LOG_ENABLE_INFO_MSG
/**
 * @brief Writes a 'Info' message to the terminal.
 *
 */
#define LOG_INFO(fmt, ...)                                                     \
  ((LogWrite("INFO", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))
#else
#define LOG_INFO(fmt, ...)                                                     \
  do {                                                                         \
    (void)fmt;                                                                 \
  } while (0)
#endif

#ifdef LOG_ENABLE_ERROR_MSG
/**
 * @brief Writes an 'Error' message to the terminal.
 *
 */
#define LOG_ERROR(fmt, ...)                                                    \
  ((__LOG_WRITE("ERROR", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))
#else
#define LOG_ERROR(fmt, ...)                                                    \
  do {                                                                         \
    (void)fmt;                                                                 \
  } while (0)
#endif

/**
 * @brief Log writing function
 * @warning do not use on its own!
 *
 * @param type log type
 * @param fileName name of the .c file
 * @param lineNumber line in the .c file
 * @param fmt
 * @param ...
 */
void LogWrite(const char *type, const char *fileName, const uint16_t lineNumber,
              const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif