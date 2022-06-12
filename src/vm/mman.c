#include "mman.h"
#include "exec.h"
#include "vmutils.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define HASH_MULTIPLIER  65599U

struct avm_memcell stack[AVM_STACKSIZE];

//=============== MEMCLEAR DISPATCHER ===============
memclear_func_t memclearFuncs[]={
    0,  // nunder_m
    memclear_string,  // string_m
    0,  // bool_m
    memclear_table,
    0,  // userfunc_m
    memclear_libfunc,
    0,  //nil_m
    0   //undef_m
};

void avm_memcellclear(struct avm_memcell * mc)
{
    if ( mc->type == undef_m)
    {
        /** TODO: error handling ? */
        return;
    }

    memclear_func_t f = memclearFuncs[mc->type];

    if ( f )
        (*f)(mc);

    mc->type = undef_m;
}

void memclear_string(struct avm_memcell * mc)
{
    free(mc->data.strVal);
}

void memclear_table(struct avm_memcell * mc)
{
    avm_tabledecrefcounter(mc->data.tableVal);
}

void memclear_libfunc(struct avm_memcell * mc){
    free(mc->data.libfuncVal);
}

static uint __hash(const struct avm_memcell * key)
{
    const uint8_t * blob;

    uint hash  = 0U;
    uint index = 0U;


    switch ( key->type )
    {
        case undef_m:

            /** TODO: error handling */

            break;

        case number_m:

            blob = (const uint8_t *)(&key->data);

            for (; index < sizeof( key->data.numVal ); ++index)
                hash = hash * HASH_MULTIPLIER + blob[index];

            break;

        case bool_m:

            blob = (const uint8_t *)(&key->data);

            hash = blob[0];
            break;

        case table_m:

            blob = (const uint8_t *)(key->data.tableVal);

            for (; index < sizeof( *(key->data.tableVal) ); ++index)
                hash = hash * HASH_MULTIPLIER + blob[index];

            break;

        case userfunc_m:

            blob = (const uint8_t *)(&key->data);

            for (; index < sizeof( key->data.funcVal ); ++index)
                hash = hash * HASH_MULTIPLIER + blob[index];

            break;

        case string_m:
        case libfunc_m:

            blob = (const uint8_t *)(key->data.strVal);

            for (; blob[index]; ++index)  // null terminating string
                hash = hash * HASH_MULTIPLIER + blob[index];

            break;

        case nil_m:

            /** TODO: error handling */

            break;
    }


    return hash % AVM_TABLE_HASHSIZE;
}

void avm_initstack(void)
{
    memset(stack, 0, AVM_STACKSIZE * sizeof(*stack));
}

struct avm_table * avm_tablenew(void)
{
    struct avm_table * ret;

    if ( !(ret = malloc(sizeof( *ret ))) )
        return NULL;

    bzero(ret, sizeof( *ret ));


    return ret;
}

void avm_tabledestroy(struct avm_table * t)
{
    struct avm_table_bucket * b;
    struct avm_table_bucket * pb;


    /** TODO: support all arrays */

    for (uint i = 0U; i < AVM_TABLE_HASHSIZE; ++i)
    {
        /** TODO: compact that to one for-loop */

        for (b = t->numIndexed[i]; b;)
        {
            pb = b;
            b = b->next;

            avm_memcellclear(&pb->key);
            avm_memcellclear(&pb->value);

            free(pb);
        }

        t->numIndexed[i] = NULL;

        for (b = t->strIndexed[i]; b;)
        {
            pb = b;
            b = b->next;

            avm_memcellclear(&pb->key);
            avm_memcellclear(&pb->value);

            free(pb);
        }

        t->strIndexed[i] = NULL;
    }

    free(t);
}

void avm_tableincrefcounter(struct avm_table * t)
{
    ++t->refCounter;
}

void avm_tabledecrefcounter(struct avm_table * t)
{
    if( --t->refCounter <= 0 )
        avm_tabledestroy(t);
}

int __cmp_key_string(uint64_t k1, uint64_t k2)
{
    return strcmp((const char * restrict)(k1), (const char * restrict)(k2));
}

int __cmp_key_const(uint64_t k1, uint64_t k2)
{
    return (int)(k1 - k2);
}

int __cmp_key_table(const struct avm_table * restrict k1, const struct avm_table * restrict k2)
{
    /** TODO: implement that */

    return 1;
}

void avm_tablesetelem(struct avm_table * restrict t, const struct avm_memcell * restrict key, const struct avm_memcell * restrict val)
{
    int (*compfunc)(uint64_t, uint64_t);
    struct avm_table_bucket ** arr;
    uint hash;


    hash = __hash(key);

    switch ( key->type )
    {
        case undef_m:

            /** TODO: error handling */
            break;

        case number_m:

            arr = t->numIndexed;  // warnings...
            compfunc = __cmp_key_const;

            break;

        case bool_m:

            arr = t->boolIndexed;
            compfunc = __cmp_key_const;

            break;

        case table_m:

            arr = t->tableIndexed;
            break;

        case userfunc_m:

            arr = &t->usrfuIndexed[0];
            compfunc = __cmp_key_const;

            break;

        case string_m:
        case libfunc_m:

            arr = t->libfuIndexed;
            compfunc = __cmp_key_string;

            break;

        case nil_m:

            /** TODO: error handling */
            break;
    }

    if ( !arr[hash] )
    {
        arr[hash] = malloc(sizeof ( **arr ));
        arr[hash]->key = *key;
        arr[hash]->next = NULL;
        arr[hash]->value = *val;

        ++t->total;

        return;
    }

    struct avm_table_bucket * tmp = arr[hash];
    struct avm_table_bucket * prev;


    do {

        prev = tmp;

        if ( !(*compfunc)((uint64_t)(tmp->key.data.strVal), (uint64_t)(key->data.strVal) ) )
        {
            tmp->key = *key;  /** TODO: when memclear() is called ??? */
            tmp->value = *val;
        }

        tmp = tmp->next;

    } while ( tmp );

    prev->next = malloc(sizeof( *tmp ));

    prev->next->next = NULL;
    prev->next->key = *key;
    prev->next->value = *val;
}

struct avm_memcell * avm_tablegetelem(struct avm_table * restrict t, const struct avm_memcell * restrict key)
{
    int (*compfunc)(uint64_t, uint64_t);
    struct avm_table_bucket ** arr;
    uint hash;


    hash = __hash(key);

    switch ( key->type )
    {
        case undef_m:

            /** TODO: error handling */
            break;

        case number_m:

            arr = t->numIndexed;  // warnings...
            compfunc = __cmp_key_const;

            break;

        case bool_m:

            arr = t->boolIndexed;
            compfunc = __cmp_key_const;

            break;

        case table_m:

            arr = t->tableIndexed;
            break;

        case userfunc_m:

            arr = &t->usrfuIndexed[0];
            compfunc = __cmp_key_const;

            break;

        case string_m:
        case libfunc_m:

            arr = t->libfuIndexed;
            compfunc = __cmp_key_string;

            break;

        case nil_m:

            /** TODO: error handling */
            break;
    }

    if ( !arr[hash] )
        return NULL;

    struct avm_table_bucket * tmp = arr[hash];

    do {

        if ( !(*compfunc)((uint64_t)(tmp->key.data.strVal), (uint64_t)(key->data.strVal) ) )
            return &tmp->value;

        tmp = tmp->next;

    } while ( tmp );
    

    return NULL;
}

struct avm_memcell * avm_translate_operand(struct vmarg * arg, struct avm_memcell * reg){
    switch (arg->type)
    {
    case global_a:  return &stack[AVM_STACKSIZE - 1U - arg->val];
    case local_a:   return &stack[topsp - arg->val];
    case formal_a:  return &stack[topsp + AVM_STACKENV_SIZE + 1U + arg->val];

    case retval_a:  return &retval;

    case number_a:{
        reg->type = number_m;
        reg->data.numVal = consts_getnumber(arg->val);
        return reg;
    }
    
    case string_a:{
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstr(arg->val));
        return reg;
    }
    
    case bool_a:
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;

    case nil_a:

        reg->type = nil_m;
        return reg;

    case userfunc_a:
        reg->type = userfunc_m;
        reg->data.funcVal = consts_getuserfuncaddr(arg->val);
        return reg;

    case libfunc_a:{
        reg->type = libfunc_m;
        reg->data.libfuncVal = consts_getlibfunc(arg->val);
        return reg;
    }

    default:
        assert(0);
    }
}

