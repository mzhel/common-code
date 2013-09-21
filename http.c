#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <http.h>
#include <mem.h>
#include <log.h>

uint32_t
http_create(
            HTTP** http_ptr
            )
{
	uint32_t r = 0;
	HTTP* http = NULL;

	do {

	    http = (HTTP*)mem_alloc(sizeof(HTTP));

	    if (!http){

	        LOG_ERROR("Failed to allocate memory for http.");

	        break;

	    }

	    http->hdrs_ptr = http->raw_hdrs;

	    http->more_data = true;

	    *http_ptr = http;

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_destroy(
             HTTP* http
             )
{
	uint32_t r = 0;

	do {

	    if (!http) break;

	    if (http->cntnt) mem_free(http->cntnt);

	    mem_free(http);

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_parse(
           HTTP* http,
           char* buf,
           uint32_t buf_len
           )
{
	uint32_t r = 0;
	uint32_t rem_len = 0;
	uint32_t copy_len = 0;
	char* p = NULL;

	do {

	    if (!http || !buf || !buf_len) break;

	    p = buf;

	    while (http->more_data && buf_len) {

            if (!http->hdrs_rcvd) {

                rem_len = sizeof(http->raw_hdrs) - (http->hdrs_ptr - http->raw_hdrs);

                copy_len = (rem_len > buf_len)?buf_len:rem_len;

                memcpy(http->hdrs_ptr, p, copy_len);

                // Move current buffer pointer to amount of copied bytes.

                http->hdrs_ptr += copy_len;

                // Check if all headers received,
                // for now no content handling just headers.

                if (strstr(http->raw_hdrs, "\x0d\x0a\x0d\x0a")){

                    http->hdrs_rcvd = true;

                    sscanf(http->raw_hdrs, "Content-length: %d", &http->cntnt_len);

                    if (http->cntnt_len) {

                        // Need to receive content.

                        http->cntnt = (char*)mem_alloc(http->cntnt_len);

                        if (!http->cntnt){

                            LOG_ERROR("Failed to allocate memeory for content.");

                            break;

                        }

                        http->cntnt_rcvd = 0;

                    } else {

                        // No content attached.

                        http->more_data = false;

                    }

                }

            } else {

                if (http->cntnt_len){

                    copy_len = http->cntnt_len - http->cntnt_rcvd;

                    copy_len = (buf_len > copy_len)?copy_len:buf_len;

                    if (copy_len){

                        memcpy(http->cntnt, p, copy_len);

                    }

                    http->cntnt_rcvd += copy_len;

                    if (!http->cntnt_rcvd) http->more_data = false;

                }

            }

            buf_len -= copy_len;

            p += copy_len;

	    }

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_more_data(
               HTTP* http
               )
{
	uint32_t r = 0;

	do {

	    if (!http) break;

	    if (!http->more_data) break;

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_emit_get_request(
                      char* location,
                      char* buf,
                      uint32_t* buf_len_ptr
                      )
{
	uint32_t r = 0;
	uint32_t buf_len = 0;
	uint32_t req_len = 0;
	static char get[] = "GET ";
	static char http[] = " HTTP/1.1\r\n\r\n";

	do {

	    if (!location || !buf_len_ptr) break;

	    req_len = strlen(get) + strlen(location) + strlen(http);

	    buf_len = *buf_len_ptr;

	    if (buf_len < req_len){

	        *buf_len_ptr = req_len + 1;

	        LOG_DEBUG("Buffer for request not big enough.");

	        break;

	    }

	    strcpy(buf, get);

	    strcat(buf, location);

	    strcat(buf, http);

	    *buf_len_ptr = req_len;

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_get_content(
                 HTTP* http,
                 char** cntnt_ptr,
                 uint32_t* cntnt_len_ptr
                 )
{
	uint32_t r = 0;

	do {

	    if (!http || !http->cntnt_len) break;

	    *cntnt_ptr = http->cntnt;

	    *cntnt_len_ptr = http->cntnt_len;

		r = 1;

	} while (false);

	return r;
}

uint32_t
http_get_raw_headers(
                     HTTP* http,
                     char** raw_hdrs_ptr,
                     uint32_t* raw_hdrs_len
                     )
{
	uint32_t r = 0;

	do {

	    if (!http || !http->hdrs_rcvd) break;

	    *raw_hdrs_ptr = http->raw_hdrs;

	    *raw_hdrs_len = strlen(http->raw_hdrs);

		r = 1;

	} while (false);

	return r;
}
