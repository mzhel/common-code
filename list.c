#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <list.h>
#include <mem.h>
#include <log.h>

#define ALLOC_LIST (LIST*)mem_alloc(sizeof(LIST))

uint32_t
list_create(
            LIST** list_ptr
           )
{
	uint32_t r = 0;
	LIST* list = NULL;

	do {

        if (!list_ptr) break;

        list = (LIST*)mem_alloc(sizeof(LIST));

        if (!list){

            LOG_ERROR("Failed to allocate memory for list.");

            break;

        }

        *list_ptr = list;

        r = 1;

	}while (false);

	return r;
}

uint32_t
list_add_entry(
               LIST** list_ptr,
               void* entry
               )
{
	uint32_t r = 0;
	LIST* l = NULL;

	do {

	    if (!list_ptr) break;

        l = *list_ptr;

        if (!l){

            if (!list_create(list_ptr)){

                LOG_ERROR("Failed to create list.");

                break;

            }

            l = *list_ptr;

        } else {

            while (l->next) l = (LIST*)l->next;

            l->next = (LIST*)mem_alloc(sizeof(LIST));

            l = (LIST*)l->next;

        }

        l->data = entry;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_add_first_entry(
                     LIST** list_ptr,
                     void* entry
                     )
{
	uint32_t r = 0;
	LIST* l = NULL;
	LIST* nl = NULL;

	do {

	    if (!list_ptr) break;

	    l = *list_ptr;

        if (!l){

            if (!list_create(&l)){

                LOG_ERROR("Failed to create list.");

                break;

            }

        } else {

            nl = ALLOC_LIST;

            if (!nl){

                LOG_ERROR("Failed to allocate new list entry.");

                break;

            }

            nl->next = l;

            l = nl;

        }

        l->data = entry;

        *list_ptr = l;

		r = 1;

	} while (false);

	return r;
}

uint32_t
list_add_entry_at_idx(
                      LIST** list_ptr,
                      void* entry,
                      uint32_t idx
                      )
{
	uint32_t r = 0;
	uint32_t i = 0;
	LIST* l = NULL;
	LIST* nw = NULL;
	LIST* p = NULL;

	do {

	    if (!list_ptr || !entry) break;

	    l = *list_ptr;

	    if (!l){

	        // First list entry, no need to sort.

	        r = list_add_entry(list_ptr, (void*)entry);

	    } else {

	      while (l){

	          if (i == idx){

	              nw = ALLOC_LIST;

	              if (!nw){

	                  LOG_ERROR("Failed to allocate list.");

	                  break;

	              }

	              nw->data = (void*)entry;

	              if (!i){

	                  nw->next = *list_ptr;

	                  *list_ptr = nw;

	              } else {

	                  p->next = nw;

	                  nw->next = l;

	              }

	              r = 1;

	              break;

	          }

	          p = l;

	           list_next_entry(l, &l);

	          i++;

	      }

	    }

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_entry_at_idx(
                  LIST* list,
                  uint32_t idx,
                  void** entry_ptr
                  )
{
	uint32_t r = 0;
	uint32_t i = 0;
	void* entry = NULL;

	do {

        if (!list || !entry_ptr) break;

        do {

            if (!list) break;

            list_get_entry_data( list, &entry);

            if (i == idx) break;

            list_next_entry(list, &list);

            i++;

        } while (true);

        *entry_ptr = entry;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_entry_by_data(
                   LIST* list,
                   void* data,
                   void** entry_ptr
                   )
{
	uint32_t r = 0;
	void* entry = NULL;
	bool found = false;

	do {

        if (!list) break;

        do {

            if (!list) break;

            list_get_entry_data(list, &entry);

            if (entry == data){

                found = true;

                break;

            }

            list_next_entry(list, &list);

        } while (true);

        if (!found) break;

        if (entry_ptr) *entry_ptr = entry;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_next_entry(
                LIST* next_from,
                LIST** next_ptr
                )
{
	uint32_t r = 0;
	LIST* l = NULL;

	do {

	    if (!next_from || !next_ptr) break;

	    l = (LIST*)next_from->next;

	    *next_ptr = l;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_get_entry_data(
                    LIST* list,
                    void** data_ptr
                    )
{
	uint32_t r = 0;
	void* data = NULL;

	do {

        if (!list || !data_ptr) break;

        data = list->data;

        *data_ptr = data;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_remove_entry(
                  LIST** list_ptr,
                  LIST* entry_to_rem,
                  bool mem_free_data
                  )
{
	uint32_t r = 0;
	LIST* l = NULL;
	LIST* pl = NULL;

	do {

	    if (!list_ptr || !entry_to_rem) break;

	    l = *list_ptr;

	    if (!l) break;

	    do {

	        if (l == entry_to_rem) break;

	        pl = l;

	        l = (LIST*)l->next;

	    } while (l);

	    if (!l) break;

	    if (pl) pl->next = l->next; else *list_ptr = (LIST*)l->next;

	    if (mem_free_data && l->data) mem_free(l->data);

	    mem_free(l);

		r = 1;

	} while (false);

	return r;
}

uint32_t
list_remove_entry_by_data(
                          LIST** list_ptr,
                          void* data,
                          bool mem_free_data
                          )
{
	uint32_t r = 0;
	LIST* l = NULL;
	LIST* pl = NULL;

	do {

	    if (!list_ptr || !data) break;

	    l = *list_ptr;

	    if (!l) break;

	    do {

            if (l->data == data) break;

            pl = l;

            l = (LIST*)l->next;

	    } while (l);

	    if (!l) break;

	    if (pl) pl->next = l->next; else *list_ptr = (LIST*)l->next;

	    if (mem_free_data && l->data) mem_free(l->data);

	    mem_free(l);

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_destroy(
             LIST* list,
             bool mem_free_data
             )
{
	uint32_t r = 0;
	LIST* to_mem_free = NULL;
	void* data = NULL;

	do {

	    if (!list) break;

	    do {

	        to_mem_free = list;

	        list = (LIST*)list->next;

	        if (to_mem_free){

	            list_get_entry_data(to_mem_free, &data);

	            if (mem_free_data && data) mem_free(data);

	            mem_free(to_mem_free);

	        }

	    } while (list);

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_entries_count(
                   LIST* list,
                   uint32_t* entries_count_ptr
                   )
{
	uint32_t r = 0;
    uint32_t c = 0;

	do {

	    if (!entries_count_ptr) break;

	    while (list){

	        c++;

	        list = (LIST*)list->next;

	    }

	    *entries_count_ptr = c;

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_remove_first_entry(
                        LIST** list_ptr,
                        void** entry_data_ptr
                        )
{
	uint32_t r = 0;

	do {

	    if (!list_ptr || !entry_data_ptr) break;

	    list_get_entry_data(*list_ptr, entry_data_ptr);

	    list_remove_entry(list_ptr, *list_ptr, false);

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_remove_last_entry(
                       LIST** list_ptr,
                       void** entry_data_ptr
                       )
{
	uint32_t r = 0;
	LIST* list = NULL;

	do {

	    if (!list_ptr) break;

	    list = * list_ptr;

	    if (!list) break;

	    do {

            if (!list->next) break;

            list_next_entry(list, &list);

	    } while (true);

	    list_get_entry_data(list, entry_data_ptr);

	    list_remove_entry(list_ptr, list, false);

		r = 1;

	}while (false);

	return r;
}

uint32_t
list_duplicate(
               LIST* src_list,
               LIST** dst_list_ptr
               )
{
	uint32_t r = 0;
	LIST* dst_list = NULL;
	LIST* src_entry = NULL;
	void* data = NULL;

	do {

	    if (!src_list || !dst_list_ptr) break;

	    src_entry = src_list;

	    do {

	        if (!src_entry) break;

	        list_get_entry_data(src_entry, &data);

	        list_add_entry(&dst_list, data) ;

	    } while (list_next_entry(src_entry, &src_entry));

	    *dst_list_ptr = dst_list;

		r = 1;

	}while (false);

	return r;
}
