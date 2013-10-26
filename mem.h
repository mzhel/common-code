#ifndef _MEM_H_
#define _MEM_H_

#define MEM_ADJUST_BUFFER(b, s, as) if (s < as) {b = (char*)mem_realloc(b, as); s = as;}

void*
mem_alloc(
          size_t len
          );

void
mem_free(
         void* m
         );

void*
mem_realloc(
            void* ptr,
            size_t len
            );

#endif // _MEM_H_
