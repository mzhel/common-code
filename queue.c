#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <list.h>
#include <mem.h>
#include <queue.h>
#include <log.h>

uint32_t
queue_create(
             uint32_t elements_count,
             QUEUE** queue_ptr
             )
{
	uint32_t r = 0;
	QUEUE* queue = NULL;
	void* queue_entry = NULL;
	uint32_t els_per_entry = 0;

	do {

	    if (!queue_ptr) break;

	    queue = (QUEUE*)mem_alloc(sizeof(QUEUE));

	    if (!queue){

	        LOG_ERROR("Failed to allocate memory for queue struct.");

	        break;

	    }

	    els_per_entry = elements_count?elements_count:QUEUE_DEFAULT_ELEMENTS_COUNT;

        queue_entry = mem_alloc(els_per_entry * sizeof(void*));

        if (!queue_entry){

            LOG_ERROR("Failed to allocate memory for queue entries.");

            break;

        }

        if (!list_add_entry((LIST**)&queue->q_lst, queue_entry)){

            LOG_ERROR("Failed to add entry to queue list.");

            break;

        }

        queue->entries_count++;

        queue->head = 0;

        queue->tail = 0;

        queue->length = 0;

        queue->els_per_entry =els_per_entry;

        *queue_ptr = queue;

		r = 1;

	} while (false);

	if (!r){

	    if (queue){

	        list_destroy((LIST*)queue->q_lst, true);

	        mem_free(queue);

	    }

	    if (queue_entry) mem_free(queue_entry);

	}

	return r;
}

uint32_t
queue_enq(
          QUEUE* queue,
          void* elmnt
          )
{
	uint32_t r = 0;
	uint32_t head = 0;
	uint32_t tail = 0;
	uint32_t length = 0;
	uint32_t entry_idx = 0;
	uint32_t idx_in_entry = 0;
	uint32_t per_entry = 0;
	void* entry = NULL;

	do {

	    if (!queue) break;

	    head = queue->head;

	    tail = queue->tail;

	    length = queue->length;

	    per_entry = queue->els_per_entry;

	    entry_idx = tail / per_entry;

	    idx_in_entry = tail % per_entry;

	    // Add element to queue.

	    if (!queue->entries_count || entry_idx > queue->entries_count - 1){

	        // Need new entry.

	        entry = mem_alloc(queue->els_per_entry * sizeof(void*));

	        if (!entry){

	            LOG_ERROR("Failed to allocate memory for new queue entry.");

	            break;

	        }

	        if (!list_add_entry((LIST**)&queue->q_lst, entry)){

	            LOG_ERROR("Failed to add entry to queue entries list.");

	            break;

	        }

	        queue->entries_count++;

	    } else {

	        list_entry_at_idx((LIST*)queue->q_lst, entry_idx, &entry);

	    }

	    if (!entry) break;

        ((void**)entry)[idx_in_entry] = elmnt;

        queue->tail++;

        queue->length++;

		r = 1;

	} while (false);

	return r;
}

uint32_t
queue_deq(
          QUEUE* queue,
          void** elmnt_ptr
          )
{
	uint32_t r = 0;
	void* elmnt = NULL;
	uint32_t head = 0;
	uint32_t tail = 0;
	uint32_t length = 0;
	uint32_t count = 0;
	void* entry = NULL;
	uint32_t idx_in_entry = 0;

	do {

        if (!queue) break;

        head = queue->head;

        tail = queue->tail;

        length = queue->length;

        if (!length) break;

        list_entry_at_idx((LIST*)queue->q_lst, 0, &entry);

        if (!entry){

            LOG_ERROR("Failed to get first entry in queue list.");

            break;

        }

        idx_in_entry = head;

        elmnt = ((void**)entry)[idx_in_entry];

        queue->head++;

        queue->length--;

        // Delete wasted entry if needed.

        if (queue->head == queue->els_per_entry){

            list_remove_first_entry((LIST**)&queue->q_lst, &entry);

            if (entry) mem_free(entry);

            queue->head -= queue->els_per_entry;

            queue->tail -= queue->els_per_entry;

            queue->entries_count--;
        }

		r = 1;

	} while (false);

	if (elmnt_ptr) *elmnt_ptr = elmnt;

	return r;
}

uint32_t
queue_destroy(
              QUEUE* queue
              )
{
	uint32_t r = 0;

	do {

	    list_destroy((LIST*)queue->q_lst, true);

	    mem_free(queue);

		r = 1;

	} while (false);

	return r;
}
