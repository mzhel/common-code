#ifndef _MEM_H_
#define _MEM_H_

void*
mem_alloc(
          size_t len
          );

void
mem_free(
         void* m
         );

#endif // _MEM_H_
