#ifndef _BUILD_SQL_H
#define _BUILD_SQL_H

#include "util/hash.h"
#include "util/list.h"
#include "util/str_array.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum FACT_T {
    QUALITY_T,
    TOPOLOGY_T,
} FACT_T;

typedef enum ACTION_T {
    ADD_T,
    UPDATE_T,
    DELETE_T,
} ACTION_T;

typedef struct networkmodel {
    list* assets;
    list* facts;
} networkmodel;

typedef struct asset_instance {
    size_t id;
    char *sql;
} asset_instance;

typedef struct exploit_instance {
    size_t id;
    char *sql;
} exploit_instance;

typedef struct exploitpattern {
    char *name;
    str_array *params;
    struct list *preconditions;
    struct list *postconditions;
} exploitpattern;

typedef struct statement {
    char *obj;
    char *op;
    char *val;
} statement;

typedef struct fact {
    FACT_T type;
    char *from;
    char *dir;
    char *to;
    statement *st;
} fact;

typedef struct postcondition {
    char *op;
    fact *f;
} postcondition;

asset_instance *make_asset(char *asset);
char *make_quality(size_t assetid, statement *st);
char *make_topology(size_t fromasset, size_t toasset, char *dir, statement *st);

void print_fact(fact *fct);

exploit_instance *make_exploit(exploitpattern *xp);
char *make_precondition(hashtable *exploit_ids, exploitpattern *xp, fact *fct);
char *make_postcondition(hashtable *exploit_ids, exploitpattern *xp,
                         postcondition *pc);

#ifdef __cplusplus
}
#endif

#endif //_BUILD_SQL_H
