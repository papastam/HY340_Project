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

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))




#endif