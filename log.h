#ifndef _LOG_H_
#define _LOG_H_

#ifdef CONFIG_VERBOSE

#define LOG_LEVEL(log_level)   {set_log_level(log_level);}

#define LOG_PREFIX(prefix) {set_msg_prefix(prefix);}
#define LOG_FILE_NAME(lfn) {set_log_file_name(lfn);}
#define LOG_ERROR(msg, ...) {log_msg(MSG_LEVEL_ERROR,(char*)__FILE__,(char*)__FUNCTION__,__LINE__,msg,##__VA_ARGS__);}
#define LOG_WARN(msg, ...) {log_msg(MSG_LEVEL_WARN,(char*)__FILE__,(char*)__FUNCTION__,__LINE__,msg,##__VA_ARGS__);}
#define LOG_INFO(msg, ...) {log_msg(MSG_LEVEL_INFO,(char*)__FILE__,(char*)__FUNCTION__,__LINE__,msg,##__VA_ARGS__);}
#define LOG_DEBUG(msg, ...) {log_msg(MSG_LEVEL_DEBUG,(char*)__FILE__,(char*)__FUNCTION__,__LINE__,msg,##__VA_ARGS__);}
#define LOG_BACKTRACE       log_backtrace()

#define LOG_LEVEL_ERROR {LOG_LEVEL(MSG_LEVEL_ERROR);}
#define LOG_LEVEL_WARN {LOG_LEVEL(MSG_LEVEL_WARN);}
#define LOG_LEVEL_INFO {LOG_LEVEL(MSG_LEVEL_INFO);}
#define LOG_LEVEL_DEBUG {LOG_LEVEL(MSG_LEVEL_DEBUG);}

#define LOG_OUTPUT_DEBUG set_log_output(LOG_OUTPUT_TYPE_DEBUG)

#define LOG_OUTPUT_CONSOLE set_log_output(LOG_OUTPUT_TYPE_CONSOLE)

#define LOG_OUTPUT_FILE set_log_output(LOG_OUTPUT_TYPE_FILE)

#define LOG_OUTPUT_CONSOLE_AND_FILE set_log_output(LOG_OUTPUT_TYPE_CONSOLE | LOG_OUTPUT_TYPE_FILE)

#else

#define LOG_PREFIX(prefix)
#define LOG_FILE_NAME(lfn)
#define LOG_ERROR(msg, ...)
#define LOG_WARN(msg, ...)
#define LOG_INFO(msg, ...)
#define LOG_DEBUG(msg, ...)
#define LOG_BACKTRACE

#define LOG_LEVEL_ERROR
#define LOG_LEVEL_WARN
#define LOG_LEVEL_INFO
#define LOG_LEVEL_DEBUG

#define LOG_OUTPUT_DEBUG
#define LOG_OUTPUT_CONSOLE
#define LOG_OUTPUT_FILE
#define LOG_OUTPUT_CONSOLE_AND_FILE

#endif // CONFIG_VERBOSE

#define LOG_OUTPUT_TYPE_DEBUG    1
#define LOG_OUTPUT_TYPE_CONSOLE  2
#define LOG_OUTPUT_TYPE_FILE     4

#define MSG_LEVEL_NONE  0
#define MSG_LEVEL_ERROR 1
#define MSG_LEVEL_WARN  2
#define MSG_LEVEL_INFO  3
#define MSG_LEVEL_DEBUG 4
#define MSG_LEVEL_MAX   5

#define PREFIX_BUFFER_SIZE  64
#define LINEFUNC_BUFFER_SIZE  128
#define TIME_BUFFER_SIZE    256
#define LOG_MSG_BUFFER_SIZE 1024
#define LOG_FILE_BUFFER_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif

void log_msg(int msg_level,char* file_name, char* func_name, int line_num, char* msg, ...);
void set_msg_prefix(char *msg_prefix);
void set_log_level(int log_level);
void set_log_output(int log_output);
void set_log_file_name(char *lfn);
void log_backtrace();

#ifdef __cplusplus
}
#endif

#endif // _LOG_H_
