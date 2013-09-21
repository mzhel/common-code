#ifndef _HTTP_H_
#define _HTTP_H_

typedef struct _http {
    bool more_data;
    bool hdrs_rcvd;
    char* hdrs_ptr;
    uint32_t cntnt_len;
    uint32_t cntnt_rcvd;
    char* cntnt;
    char raw_hdrs[1024];
} HTTP;

uint32_t
http_create(
            HTTP** http_ptr
            );

uint32_t
http_destroy(
             HTTP* http
             );

uint32_t
http_parse(
           HTTP* http,
           char* buf,
           uint32_t buf_len
           );

uint32_t
http_more_data(
               HTTP* http
               );

uint32_t
http_emit_get_request(
                      char* location,
                      char* buf,
                      uint32_t* buf_len_ptr
                      );

uint32_t
http_get_content(
                 HTTP* http,
                 char** cntnt_ptr,
                 uint32_t* cntnt_len_ptr
                 );

uint32_t
http_get_raw_headers(
                     HTTP* http,
                     char** raw_hdrs_ptr,
                     uint32_t* raw_hdrs_len
                     );

#endif // _HTTP_H_
