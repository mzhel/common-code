#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_DEFAULT_ELEMENTS_COUNT 1024

typedef struct _queue {

    uint32_t head;
    uint32_t tail;
    uint32_t length;
    uint32_t els_per_entry;
    uint32_t entries_count;
    void* q_lst;
} QUEUE;

uint32_t
queue_create(
             uint32_t elements_count,
             QUEUE** queue_ptr
             );

uint32_t
queue_enq(
          QUEUE* queue,
          void* elmnt
          );

uint32_t
queue_deq(
          QUEUE* queue,
          void** elmnt_ptr
          );

uint32_t
queue_destroy(
              QUEUE* queue
              );

#endif // _QUEUE_H_
