#ifndef __TC_MEM_H__
#define __TC_MEM_H__

#define TC_MEM_ERROR -1
#define TC_MEM_OK     0

typedef struct {
    int max;
    int num;
} tc_slab_conf_t;

typedef struct {
    uint32_t  size;  /* size of a trunk */
    uint32_t  total; /* number of trunks */
    void     *free;
} tc_slab_t;

typedef struct {
    void *next;
} tc_trunk_t;

typedef struct {
    int        slabs; /* number of slabs */
    int        max;
    tc_slab_t *head;   
} tc_mpool_t;

tc_mpool_t *tc_mem_create();
int tc_mem_init(tc_mpool_t *pool);
void *tc_mem_malloc(tc_mpool_t *pool, size_t size);
void tc_mem_free(tc_mpool_t *pool, void *p, size_t size);

#endif /* __TC_MEM_H__ */
