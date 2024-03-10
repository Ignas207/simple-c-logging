/**
 * @file logs.h
 * @author Ignas207 (https://github.com/Ignas207/simple-c-logging)
 * @brief Header only implementation of logging functions.
 * @version 1.1
 * @date 2024-03-10
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 */

#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wstring-plus-int"
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include <assert.h>

// Max lenght of debug message
#define LOGS_MAX_LENGHT 150U

// Enable this to encode message as CRLF
#define LOG_CRLF_ENCODE

// Function to print the message out
#define __LOG_WRITE_FUNC(str, len)((fputs(str, stdout)))

/*
    Gets the path RELATIVE to CMakeLists!
    For this to work need to add the following to CMakeLists.txt!
    -------------------------------------------------------------
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
    add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
    -------------------------------------------------------------
*/
#ifndef SOURCE_PATH_SIZE
#define SOURCE_PATH_SIZE 0U
#endif

#ifdef LOG_CRLF_ENCODE
  #define __SNPRINTF_WRITE(str, len, fmt, ...) ((snprintf(str, len - 3, fmt, ##__VA_ARGS__)))
  #define __LOG_WRITE_NL(str, len){str[len] = '\r'; str[len +1] = '\n'; str[len+2] = '\0';}
  #else
  #define __SNPRINTF_WRITE(str, len, fmt, ...) ((snprintf(str, len - 2, fmt, ##__VA_ARGS__)))
  #define __LOG_WRITE_NL(str, len){str[len] = '\n'; str[len +1] = '\0';}
#endif

// #define __LOG_ASSERT(val)(assert(##val > 0, "Message lenght exceeded the maximum!"))

/**
 * @brief We are using this to get rid of the absolute path of our project.
 *
 */
#define FILENAME__ ((__FILE__) + SOURCE_PATH_SIZE)

#define __LOG_WRITE(type, fileName, lineNumber, fmt, ...)                                         \
  do {                                                                                            \
                                                                                                  \
    int32_t retSize;                                                                              \
    int32_t retSize2;                                                                             \
    char logStr[LOGS_MAX_LENGHT];                                                                 \
                                                                                                  \
    /* Writing the starting portion */                                                            \
    retSize = snprintf(logStr, LOGS_MAX_LENGHT, "%s (%s:%d): ", type,                             \
                       fileName, lineNumber);                                                     \
    /* assert(retSize > 0);      */                                                               \
                                                                                                  \
    /* Writing the VA_ARGS */                                                                     \
    retSize2 = __SNPRINTF_WRITE(logStr + retSize, LOGS_MAX_LENGHT - retSize, fmt, ##__VA_ARGS__); \
    /* assert(retSize2 > 0); */                                                                   \
    retSize += retSize2;                                                                          \
    __LOG_WRITE_NL(logStr, retSize);                                                              \
    __LOG_WRITE_FUNC(logStr, LOGS_MAX_LENGHT);                                                    \
  } while (0)

#ifdef LOG_ENABLE_EVENT_MSG
/**
 * @brief Writes an 'Event' message to the terminal.
 *
 */
#define LOG_EVENT(fmt, ...)                                                    \
  __LOG_WRITE("EVENT", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
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
  __LOG_WRITE("INFO", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
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
  __LOG_WRITE("ERROR", FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
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