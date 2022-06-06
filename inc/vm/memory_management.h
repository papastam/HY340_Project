#ifndef CS340_PROJECT_MEMORY_MANAGEMENT
#define CS340_PROJECT_MEMORY_MANAGEMENT

enum avm_memcell_t {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
};

//TODO implement tables
struct avm_table;

struct avm_memcell{
    avm_memcell_t type;
    union {
        double              numVal;
        char*               strVal;
        unsigned char       boolVal;
        struct avm_table*   tableVal;
        unsigned            funcVal;
        char*               libfuncVal;
    } data;
    
};

//=============== MEMORY CLEANING ===============

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))

typedef (*memclear_func_t)(struct avm_memcell*);
memclear_func_t memclearFuncs[]={
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
}

void avm_memcellclear(struct avm_memcell* input);
void memclear_string(struct avm_memcell* input);
void memclear_table(struct avm_memcell* input);

//=============== TABLES ===============

void avm_tabledecrefcounter(struct avm_table* input);
void avm_tableincrefcounter(struct avm_table* input);


#endif