#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <execinfo.h>
#include <time.h>
#include <log.h>

static char* prefix = NULL;
static char prefix_buffer[PREFIX_BUFFER_SIZE] = {0};
static char log_file_name[LOG_FILE_BUFFER_SIZE] = {0};
static char time_buffer[TIME_BUFFER_SIZE] = {0};
static int current_log_level = MSG_LEVEL_INFO;
static int output_type = LOG_OUTPUT_TYPE_DEBUG;
static int full_file_name = 0;

void
set_msg_prefix(
               char* msg_prefix
               )
{
    size_t new_prefix_len = 0;

	do {

	    if (!msg_prefix) break;

	    new_prefix_len = strlen(msg_prefix);

	    if (new_prefix_len > (PREFIX_BUFFER_SIZE - 1)) break;

	    strcpy(prefix_buffer, msg_prefix);

	    prefix = prefix_buffer;

	} while (false);

}

void
set_log_file_name(
                  char* lfn
                  )
{
    size_t new_lfn_len = 0;

	do {

	    if (!lfn) break;

	    new_lfn_len = strlen(lfn);

	    if (new_lfn_len > (LOG_FILE_BUFFER_SIZE - 1)) break;

        strcpy(log_file_name, lfn);

	} while (false);

}

void
set_log_level(
              int log_level
              )
{
	do {

	    if (log_level > MSG_LEVEL_MAX) break;

	    current_log_level = log_level;

	} while (false);

}

void
set_log_output(
               int log_output
               )
{
	do {

	    output_type = log_output;

	} while (false);

}

static
char*
get_msg_level_str(
                  int msg_level
                  )
{
	char *msg_level_str = "UNKNOWN";

	do {

        switch(msg_level){

            case MSG_LEVEL_ERROR:

                msg_level_str = "ERROR";

            break;

            case MSG_LEVEL_WARN:

                msg_level_str = "WARN";

            break;

            case MSG_LEVEL_INFO:

                msg_level_str = "INFO";

            break;

            case MSG_LEVEL_DEBUG:

                msg_level_str = "DEBUG";

            break;

        }


	} while (false);

	return msg_level_str;
}

bool
log_to_console(
               const char* text
               )
{
	bool r = false;
	uint32_t len = 0;

	do {

	    if (!text) break;

	    len = strlen(text);

	    fwrite(text, 1, len, stdout);

		r = true;

	} while (false);

	return r;
}

bool
log_to_file(
            const char* text
            )
{
	bool r = false;
	FILE* fd = NULL;
	uint32_t len = 0;

	do {

	    if (!text) break;

	    fd = fopen(log_file_name, "a+");

	    len = strlen(text);

	    fwrite(text, 1, len, fd);

		r = true;

	} while (false);

	if (fd) fclose(fd);

	return r;
}

void
output_log_str(
               const char *str
               )
{
	do {

	    if (output_type & LOG_OUTPUT_TYPE_DEBUG){

	        // void for now

	    }

	    if (output_type & LOG_OUTPUT_TYPE_CONSOLE){

	        log_to_console(str);

	    }

	    if (output_type & LOG_OUTPUT_TYPE_FILE){

	        log_to_file(str);

	    }

	} while (false);

}

void
log_msg(
        int msg_level,
        char* file_name,
        char* func_name,
        int line_num,
        char* msg,
        ...
        )
{
    char out_buffer[LOG_MSG_BUFFER_SIZE];
    char line_func_buffer[LINEFUNC_BUFFER_SIZE];
    size_t prefix_len = 0;
    size_t lf_buf_len = 0;
    size_t file_name_len = 0;
    char* p = file_name;
    bool va_started = false;
    time_t now;
    struct tm* ts;

    va_list args;

	do {

	    if (msg_level > current_log_level) break;

	    va_start(args, msg);

	    va_started = true;

      out_buffer[0] = 0;

	    if (!full_file_name){

	        file_name_len = strlen(file_name);

	        p += file_name_len;

	        while (file_name_len-- && *p != '/') p--;

	        p++;

	    }

	    if (prefix){

	        // Get prefix length.

	        prefix_len = strlen(prefix);

	        if (prefix_len){

	            strcpy(out_buffer, prefix);

	        }

	    }

	    time(&now);

	    ts = localtime(&now);

	    memset(&time_buffer, 0, sizeof(time_buffer));

	    strftime(time_buffer, sizeof(time_buffer), "%a %Y-%m-%d %H:%M:%S %Z", ts);

	    if (!sprintf(line_func_buffer, "%s %s %s: %s:%d ", time_buffer, p, get_msg_level_str(msg_level), func_name, line_num)) break;

        lf_buf_len = strlen(line_func_buffer);

        if (!lf_buf_len) break;

        strcat(out_buffer, line_func_buffer);

        prefix_len += lf_buf_len;

        vsprintf(&out_buffer[prefix_len], msg, args);

        strcat(out_buffer, "\n");

        output_log_str(out_buffer);

	} while (false);

	if (va_started) va_end(args);

}

void
log_backtrace(void)
{
    FILE* fd = NULL;
    size_t size = 0;
    void* bt[10] = {0};

	do {

        fd = fopen(log_file_name, "a+");

        size = backtrace(bt, sizeof(bt) / sizeof(void*));

        backtrace_symbols_fd(bt, size, fileno(fd));

	} while (false);

	if (fd) fclose(fd);

}
