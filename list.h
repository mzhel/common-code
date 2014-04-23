#ifndef _LIST_H_
#define _LIST_H_

typedef struct _list {
    void* next;
    void* data;
} LIST;

#ifdef __cplusplus

extern "C" {

#endif

uint32_t
list_create(
            LIST** list_ptr
            );

uint32_t
list_add_entry(
               LIST** list_ptr,
               void* entry
               );

uint32_t
list_add_first_entry(
                     LIST** list_ptr,
                     void* entry
                     );

uint32_t
list_add_entry_at_idx(
                      LIST** list_ptr,
                      void* entry,
                      uint32_t idx
                      );

uint32_t
list_entry_at_idx(
                  LIST* list,
                  uint32_t idx,
                  void** entry_ptr
                  );

uint32_t
list_entry_by_data(
                   LIST* list,
                   void* data,
                   void** entry_ptr
                   );

uint32_t
list_next_entry(
                LIST* next_from,
                LIST** next_ptr
                );

uint32_t
list_get_entry_data(
                    LIST* list,
                    void** data_ptr
                    );

uint32_t
list_remove_entry(
                  LIST** list_ptr,
                  LIST* entry_to_rem,
                  bool mem_free_data
                  );

uint32_t
list_remove_entry_by_data(
                          LIST** list_ptr,
                          void* data,
                          bool mem_free_data
                          );

uint32_t
list_destroy(
             LIST* list,
             bool mem_free_data
             );

uint32_t
list_entries_count(
                   LIST* list,
                   uint32_t* entries_count_ptr
                   );

uint32_t
list_remove_first_entry(
                        LIST** list_ptr,
                        void** entry_data_ptr
                        );

uint32_t
list_remove_last_entry(
                       LIST** list_ptr,
                       void** entry_data_ptr
                       );

uint32_t
list_duplicate(
               LIST* src_list,
               LIST** dst_list_ptr
               );

#ifdef __cplusplus

}

#endif

#define list_set_entry_data(l, data) l->data = data

#define LIST_EACH_ENTRY_BEGIN(list, e) {\
LIST* #e = NULL;\
#e = list;\
do {\
if (!#e) break

#define LIST_EACH_ENTRY_END(e) } while (list_next_entry(#e, &#e));\
}

#define LIST_EACH_ENTRY_WITH_DATA_BEGIN(list, e, d){\
LIST* e = NULL;\
e = list;\
do {\
if (!e) break;\
\
list_get_entry_data(e, (void**)&d)

#define LIST_EACH_ENTRY_WITH_DATA_END(e) } while (list_next_entry(e, &e));\
}

#endif // _LIST_H_
