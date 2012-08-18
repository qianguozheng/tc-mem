
static int tc_mem_trunk_init(tc_mpool_t *pool);

static tc_slab_conf_t slabs = {
    { 8, 10 },
    { 16, 10 },
    { 32, 10 },
    { 64, 10 },
    { 128, 10 },
    { 256, 10 },
    { 512, 10 },
    { 1024, 10 },
    { 2048, 10 },
    { 3072, 10 },
    { 4096, 10 },
    { 0, 0 }
};

tc_mpool_t *
tc_mem_create()
{

}

int
tc_mem_init(tc_mpool_t *pool)
{
    int        i, n;
    tc_slab_t *p;

    for (i = 0, n = 0; slabs[i].max; i++) {
        n++;
    }

    p = malloc(n * sizeof(tc_slab_t));
    if (p == NULL) {
        return TC_MEM_ERROR;
    }

    for (i = 0; slabs[i].max; i++) {
        p[i].size = slabs[i].max;
        p[i].total = slabs[i].num;
        p[i].free = NULL;
    }

    pool->head = p;
    pool->max = 4096;
    pool->slabs = n;

    if (tc_mem_trunk_init(tc_mpool_t *pool) == TC_MEM_ERROR) {
        return TC_MEM_ERROR;
    }

    return TC_MEM_OK;
}

void *
tc_mem_malloc(tc_mpool_t *pool, size_t size)
{

}

void
tc_mem_free(tc_mpool_t *pool, void *p, size_t size)
{

}

/* TODO need to callocate size */
static int
tc_mem_trunk_init(tc_mpool_t *pool)
{
    int         i, j;
    char       *p;
    tc_slab_t  *slab;
    tc_trunk_t *trunk;

    for (i = 0; i < pool->slabs; i++) {
        slab = pool->head + i;

        p = malloc(slab->total * slab->size);
        if (p == NULL) {
            return TC_MEM_ERROR;
        }

        memset(p, 0, slab->total * slab->size);

        slab->free = p;

        for (j = 0; j < slab->total - 1; j++) {
            trunk = (tc_trunk_t *) p;
            p += slab->size;
            trunk->next = p;
        }
    }

    return TC_MEM_OK;
}

